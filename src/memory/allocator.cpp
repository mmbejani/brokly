#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define MAGIC 0x54454E53u
#define MAX_DIM 8
#define HASH_ENTRIES 4096
#define ALIGNMENT 16

static inline size_t align_up(size_t x, size_t a) {
  return (x + (a - 1)) & ~(a - 1);
}

typedef uint32_t off32;

typedef struct BlockHeader {
  uint32_t size;  
  uint8_t free;   /* 1 if free, 0 if allocated */
  uint8_t pad[3]; /* padding -> align to 8 */
  off32 next;     /* offset of next block header in region (0 if none) */
  off32 prev;     /* offset of prev block header in region (0 if none) */
} BlockHeader;

/* Tensor metadata stored in hash table entries */
typedef struct TensorEntry {
  uint64_t id;   /* user-provided tensor id (0 = empty slot) */
  off32 offset;  /* offset from base to tensor data (user pointer) */
  uint32_t size; /* size of allocation in bytes */
} TensorEntry;

/* The pool header is at the start of the mapped block and holds allocator
 * metadata. */
typedef struct PoolHeader {
  uint32_t magic;
  uint32_t total_size;

  /* Resident region (bump) */
  off32 resident_start; /* offset where resident region begins (after header) */
  off32 resident_end; /* first free offset in resident region (bump pointer) */
  uint32_t resident_capacity;

  /* Ephemeral region */
  off32 ephemeral_start;
  off32 ephemeral_capacity; /* bytes reserved for ephemeral region */

  /* Hash tables stored inline (immediately after header):
   * resident_table (HASH_ENTRIES entries)
   * ephemeral_table (HASH_ENTRIES entries)
   */
  /* We don't declare the arrays here because they are variable-positioned in
   * the single block. */
} PoolHeader;

/* Top-level pool descriptor (pointer kept in program, not stored inside pool)
 */
typedef struct Pool {
  uint8_t *base; /* pointer to mmap'd memory */
  PoolHeader *hdr;
  TensorEntry *resident_table; /* pointers into mmap'd region */
  TensorEntry *ephemeral_table;
  off32 pool_size;
} Pool;

/* Helpers to compute positions inside mapped block */
static inline uint8_t *off_to_ptr(Pool *p, off32 o) {
  return (o == 0) ? NULL : p->base + o;
}
static inline off32 ptr_to_off(Pool *p, void *ptr) {
  return (ptr == NULL) ? 0 : (off32)((uint8_t *)ptr - p->base);
}

/* Simple linear-probing insert/find for hash table inside pool. Returns index
 * or -1 on failure. */
static int hash_find_index(TensorEntry *table, uint64_t id) {
  if (id == 0)
    return -1;
  uint32_t mask = HASH_ENTRIES - 1;
  uint32_t h = (uint32_t)(id ^ (id >> 33));
  uint32_t idx = h & mask;
  for (uint32_t probe = 0; probe < HASH_ENTRIES; ++probe) {
    uint32_t i = (idx + probe) & mask;
    if (table[i].id == id)
      return (int)i;
    if (table[i].id == 0)
      return -(int)i - 1; /* empty slot */
  }
  return -1;
}

static int hash_insert(TensorEntry *table, uint64_t id, off32 off,
                       uint32_t size) {
  if (id == 0)
    return -1;
  uint32_t mask = HASH_ENTRIES - 1;
  uint32_t h = (uint32_t)(id ^ (id >> 33));
  uint32_t idx = h & mask;
  for (uint32_t probe = 0; probe < HASH_ENTRIES; ++probe) {
    uint32_t i = (idx + probe) & mask;
    if (table[i].id == 0 || table[i].id == id) {
      table[i].id = id;
      table[i].offset = off;
      table[i].size = size;
      return (int)i;
    }
  }
  return -1; /* table full */
}

static int hash_remove(TensorEntry *table, uint64_t id) {
  int idx = hash_find_index(table, id);
  if (idx >= 0) {
    table[idx].id =
        0; /* tombstone naive strategy: we clear the slot -> this may break
              finds; for simplicity we allow it (not production). */
    table[idx].offset = 0;
    table[idx].size = 0;
    return idx;
  }
  return -1;
}

/* Initialize pool: mmap a block of size bytes and carve header + hash tables +
 * regions. Layout plan:
 * [PoolHeader][resident_table][ephemeral_table][resident_region][ephemeral_region]
 */
Pool *pool_init(size_t total_bytes) {
  size_t pagesize = (size_t)sysconf(_SC_PAGESIZE);
  size_t size = align_up(total_bytes, pagesize);
  void *base = mmap(NULL, size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (base == MAP_FAILED) {
    perror("mmap");
    return NULL;
  }

  Pool *p = malloc(
      sizeof(Pool)); /* small heap allocation for descriptor only (allowed). */
  if (!p) {
    munmap(base, size);
    return NULL;
  }
  memset(p, 0, sizeof(Pool));
  p->base = (uint8_t *)base;
  p->pool_size = (off32)size;

  /* Compute positions */
  PoolHeader *hdr = (PoolHeader *)p->base;
  memset(hdr, 0, sizeof(PoolHeader));
  hdr->magic = MAGIC;
  hdr->total_size = (uint32_t)size;

  /* Place resident and ephemeral hash tables directly after header */
  off32 cursor = (off32)align_up(sizeof(PoolHeader), ALIGNMENT);
  p->resident_table = (TensorEntry *)(p->base + cursor);
  memset(p->resident_table, 0, sizeof(TensorEntry) * HASH_ENTRIES);
  cursor += (off32)align_up(sizeof(TensorEntry) * HASH_ENTRIES, ALIGNMENT);

  p->ephemeral_table = (TensorEntry *)(p->base + cursor);
  memset(p->ephemeral_table, 0, sizeof(TensorEntry) * HASH_ENTRIES);
  cursor += (off32)align_up(sizeof(TensorEntry) * HASH_ENTRIES, ALIGNMENT);

  /* Reserve the first N bytes for resident region (e.g., 40% of pool) */
  size_t resident_bytes = (size_t)(size * 0.4);
  hdr->resident_start = cursor;
  hdr->resident_capacity = (uint32_t)resident_bytes;
  hdr->resident_end =
      hdr->resident_start; /* bump pointer initially equals start */
  cursor += (off32)align_up((off32)resident_bytes, ALIGNMENT);

  hdr->ephemeral_start = cursor;
  hdr->ephemeral_capacity = (uint32_t)(size - cursor);


  BlockHeader *first = (BlockHeader *)(p->base + hdr->ephemeral_start);
  first->size = hdr->ephemeral_capacity -
                (uint32_t)align_up((uint32_t)sizeof(BlockHeader), ALIGNMENT);
  first->free = 1;
  first->next = 0;
  first->prev = 0;

  p->hdr = hdr;
  return p;
}

void *allocate_resident(Pool *p, uint64_t id, size_t size) {
  if (!p || id == 0)
    return NULL;
  size_t aligned = align_up(size, ALIGNMENT);
  off32 start = p->hdr->resident_end;
  off32 limit = p->hdr->resident_start + p->hdr->resident_capacity;
  if ((uint64_t)start + aligned > limit)
    return NULL; /* out of resident space */
  void *ptr = p->base + start;
  p->hdr->resident_end = (off32)(start + (off32)aligned);
  if (hash_insert(p->resident_table, id, ptr_to_off(p, ptr),
                  (uint32_t)aligned) < 0) {
    return NULL; /* table full */
  }
  return ptr;
}

void *allocate_ephemeral(Pool *p, uint64_t id, size_t size) {
  if (!p || id == 0)
    return NULL;
  size_t aligned = align_up(size, ALIGNMENT);
  off32 cur_off = p->hdr->ephemeral_start;
  while (cur_off != 0) {
    BlockHeader *bh = (BlockHeader *)(p->base + cur_off);
    if (bh->free && bh->size >= aligned) {
      /* possibly split block */
      uint32_t remaining = bh->size - (uint32_t)aligned;
      bh->free = 0;
      bh->size = (uint32_t)aligned;
      /* if remaining space large enough to hold a new block header + min
       * payload, split */
      uint32_t min_split =
          (uint32_t)align_up((uint32_t)sizeof(BlockHeader) + 16, ALIGNMENT);
      if (remaining > min_split) {
        off32 new_off =
            cur_off +
            (off32)align_up((uint32_t)sizeof(BlockHeader), ALIGNMENT) +
            bh->size;
        BlockHeader *nh = (BlockHeader *)(p->base + new_off);
        nh->free = 1;
        nh->size = remaining -
                   (uint32_t)align_up((uint32_t)sizeof(BlockHeader), ALIGNMENT);
        nh->next = bh->next;
        nh->prev = cur_off;
        bh->next = new_off;
        if (nh->next) {
          BlockHeader *nx = (BlockHeader *)(p->base + nh->next);
          nx->prev = new_off;
        }
      }
      void *data_ptr =
          (uint8_t *)bh + align_up((uint32_t)sizeof(BlockHeader), ALIGNMENT);
      if (hash_insert(p->ephemeral_table, id, ptr_to_off(p, data_ptr),
                      (uint32_t)aligned) < 0) {
        /* rollback: mark free and return NULL */
        bh->free = 1;
        return NULL;
      }
      return data_ptr;
    }
    cur_off = bh->next;
  }
  return NULL; /* no fit */
}

static void try_coalesce(Pool *p, BlockHeader *bh, off32 bh_off) {
  /* coalesce next if free */
  if (bh->next) {
    BlockHeader *nx = (BlockHeader *)(p->base + bh->next);
    if (nx->free) {
      bh->size += (uint32_t)align_up((uint32_t)sizeof(BlockHeader), ALIGNMENT) +
                  nx->size;
      bh->next = nx->next;
      if (nx->next) {
        BlockHeader *nx2 = (BlockHeader *)(p->base + nx->next);
        nx2->prev = bh_off;
      }
    }
  }
  /* coalesce prev if free */
  if (bh->prev) {
    BlockHeader *pr = (BlockHeader *)(p->base + bh->prev);
    if (pr->free) {
      pr->size += (uint32_t)align_up((uint32_t)sizeof(BlockHeader), ALIGNMENT) +
                  bh->size;
      pr->next = bh->next;
      if (bh->next) {
        BlockHeader *nx = (BlockHeader *)(p->base + bh->next);
        nx->prev = bh->prev;
      }
    }
  }
}

int free_ephemeral(Pool *p, uint64_t id) {
  if (!p || id == 0)
    return -1;
  int idx = hash_find_index(p->ephemeral_table, id);
  if (idx < 0)
    return -1;
  off32 off = p->ephemeral_table[idx].offset;
  if (off == 0)
    return -1;
  BlockHeader *bh =
      (BlockHeader *)(p->base + (off - align_up((uint32_t)sizeof(BlockHeader),
                                                ALIGNMENT)));
  bh->free = 1;
  /* coalesce neighbors */
  off32 bh_off = (off32)((uint8_t *)bh - p->base);
  try_coalesce(p, bh, bh_off);
  hash_remove(p->ephemeral_table, id);
  return 0;
}

void *get_tensor_ptr(Pool *p, uint64_t id) {
  if (!p || id == 0)
    return NULL;
  int idx = hash_find_index(p->resident_table, id);
  if (idx >= 0)
    return off_to_ptr(p, p->resident_table[idx].offset);
  idx = hash_find_index(p->ephemeral_table, id);
  if (idx >= 0)
    return off_to_ptr(p, p->ephemeral_table[idx].offset);
  return NULL;
}

void pool_debug(Pool *p) {
  printf("Pool total=%u resident_start=%u resident_end=%u resident_capacity=%u "
         "ephemeral_start=%u ephemeral_capacity=%u\n",
         p->hdr->total_size, p->hdr->resident_start, p->hdr->resident_end,
         p->hdr->resident_capacity, p->hdr->ephemeral_start,
         p->hdr->ephemeral_capacity);
}