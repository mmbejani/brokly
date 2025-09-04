#include "mm/allocator_interface.h"
#include "mm/pool.h"
#include <stdlib.h>

// Pool allocator implementation
typedef struct {
    Allocator base;
    MemoryPool* pool;
} PoolAllocator;

// Pool allocator vtable functions
static void* pool_allocator_alloc(Allocator* self, size_t size) {
    PoolAllocator* pool_alloc = (PoolAllocator*)self;
    if (size <= pool_alloc->pool->block_size) {
        return pool_alloc(pool_alloc->pool);
    }
    // For sizes larger than block size, fall back to malloc
    return malloc(size);
}

static void pool_allocator_free(Allocator* self, void* ptr) {
    PoolAllocator* pool_alloc = (PoolAllocator*)self;
    // In a real implementation, we would need to determine if the pointer
    // belongs to our pool or was allocated with malloc
    // For now, we'll just free it with free (which handles malloc'd pointers)
    free(ptr);
}

static void pool_allocator_reset(Allocator* self) {
    PoolAllocator* pool_alloc = (PoolAllocator*)self;
    pool_reset(pool_alloc->pool);
}

static size_t pool_allocator_get_used_memory(Allocator* self) {
    PoolAllocator* pool_alloc = (PoolAllocator*)self;
    return pool_get_used_memory(pool_alloc->pool);
}

static size_t pool_allocator_get_free_memory(Allocator* self) {
    PoolAllocator* pool_alloc = (PoolAllocator*)self;
    return pool_get_free_memory(pool_alloc->pool);
}

// Pool allocator vtable
static AllocatorVTable pool_allocator_vtable = {
    .alloc = pool_allocator_alloc,
    .free = pool_allocator_free,
    .reset = pool_allocator_reset,
    .get_used_memory = pool_allocator_get_used_memory,
    .get_free_memory = pool_allocator_get_free_memory
};

Allocator* pool_allocator_create(size_t pool_size, size_t block_size) {
    PoolAllocator* pool_alloc = (PoolAllocator*)malloc(sizeof(PoolAllocator));
    if (!pool_alloc) {
        return NULL;
    }
    
    pool_alloc->base.vtable = &pool_allocator_vtable;
    pool_alloc->base.private_data = NULL;
    pool_alloc->pool = pool_create(pool_size, block_size);
    
    if (!pool_alloc->pool) {
        free(pool_alloc);
        return NULL;
    }
    
    return (Allocator*)pool_alloc;
}

// Fallback allocator implementation (uses malloc/free)
typedef struct {
    Allocator base;
    size_t used_memory;
} FallbackAllocator;

// Fallback allocator vtable functions
static void* fallback_allocator_alloc(Allocator* self, size_t size) {
    FallbackAllocator* fallback = (FallbackAllocator*)self;
    void* ptr = malloc(size);
    if (ptr) {
        fallback->used_memory += size;
    }
    return ptr;
}

static void fallback_allocator_free(Allocator* self, void* ptr) {
    // We don't track the size of freed memory in this simple implementation
    free(ptr);
}

static void fallback_allocator_reset(Allocator* self) {
    // Nothing to do for fallback allocator
}

static size_t fallback_allocator_get_used_memory(Allocator* self) {
    FallbackAllocator* fallback = (FallbackAllocator*)self;
    return fallback->used_memory;
}

static size_t fallback_allocator_get_free_memory(Allocator* self) {
    // Return a large value since we're using the heap
    return SIZE_MAX;
}

// Fallback allocator vtable
static AllocatorVTable fallback_allocator_vtable = {
    .alloc = fallback_allocator_alloc,
    .free = fallback_allocator_free,
    .reset = fallback_allocator_reset,
    .get_used_memory = fallback_allocator_get_used_memory,
    .get_free_memory = fallback_allocator_get_free_memory
};

Allocator* fallback_allocator_create() {
    FallbackAllocator* fallback = (FallbackAllocator*)malloc(sizeof(FallbackAllocator));
    if (!fallback) {
        return NULL;
    }
    
    fallback->base.vtable = &fallback_allocator_vtable;
    fallback->base.private_data = NULL;
    fallback->used_memory = 0;
    
    return (Allocator*)fallback;
}

// Allocator interface functions
void* allocator_alloc(Allocator* allocator, size_t size) {
    if (!allocator || !allocator->vtable || !allocator->vtable->alloc) {
        return NULL;
    }
    return allocator->vtable->alloc(allocator, size);
}

void allocator_free(Allocator* allocator, void* ptr) {
    if (!allocator || !allocator->vtable || !allocator->vtable->free) {
        free(ptr);  // Fallback to standard free
        return;
    }
    allocator->vtable->free(allocator, ptr);
}

void allocator_reset(Allocator* allocator) {
    if (!allocator || !allocator->vtable || !allocator->vtable->reset) {
        return;
    }
    allocator->vtable->reset(allocator);
}

size_t allocator_get_used_memory(Allocator* allocator) {
    if (!allocator || !allocator->vtable || !allocator->vtable->get_used_memory) {
        return 0;
    }
    return allocator->vtable->get_used_memory(allocator);
}

size_t allocator_get_free_memory(Allocator* allocator) {
    if (!allocator || !allocator->vtable || !allocator->vtable->get_free_memory) {
        return 0;
    }
    return allocator->vtable->get_free_memory(allocator);
}