#include <stdlib.h>

#include "util/map.h"

TensorMap *map_create(size_t size) {
  TensorMap *map = (TensorMap *)malloc(sizeof(TensorMap));
  if (!map)
    return NULL;

  map->buckets = (TensorMapEntry **)calloc(size, sizeof(TensorMapEntry *));
  if (!map->buckets) {
    free(map);
    return NULL;
  }

  map->size = size;
  map->count = 0;
  map->hash_func = hash_int;
  map->key_cmp = compare_hash_int;
  map->key_destroy = NULL;
  map->value_destroy = NULL;

  return map;
}

// Destroy the map and free all memory
void map_destroy(TensorMap *map) {
  if (!map)
    return;

  map_clear(map);
  free(map->buckets);
  free(map);
}

int map_insert(TensorMap *map, int key, Tensor *tensor) {
  if (!map || !key)
    return -1;

  size_t index = map->hash_func(key) % map->size;

  // Check if key already exists
  TensorMapEntry *entry = map->buckets[index];
  while (entry) {
    if (map->key_cmp(entry->key, key) == 0) {
      // Key exists, update value
      if (map->value_destroy && entry->tensor) {
        map->value_destroy(entry->tensor);
      }
      entry->tensor = tensor;
      return 0;
    }
    entry = entry->next;
  }

  // Create new entry
  TensorMapEntry *new_entry = (TensorMapEntry *)malloc(sizeof(TensorMapEntry));
  if (!new_entry)
    return -1;

  new_entry->key = key;
  new_entry->tensor = tensor;
  new_entry->next = map->buckets[index];
  map->buckets[index] = new_entry;
  map->count++;

  return 0;
}

// Get a value by key from the map
Tensor *map_get(TensorMap *map, const int key) {
  if (!map || !key)
    return NULL;

  size_t index = map->hash_func(key) % map->size;
  TensorMapEntry *entry = map->buckets[index];

  while (entry) {
    if (map->key_cmp(entry->key, key) == 0) {
      return entry->tensor;
    }
    entry = entry->next;
  }

  return NULL; // Key not found
}

// Remove a key-value pair from the map
int map_remove(TensorMap *map, const int key) {
  if (!map || !key)
    return -1;

  size_t index = map->hash_func(key) % map->size;
  TensorMapEntry *entry = map->buckets[index];
  TensorMapEntry *prev = NULL;

  while (entry) {
    if (map->key_cmp(entry->key, key) == 0) {
      if (prev) {
        prev->next = entry->next;
      } else {
        map->buckets[index] = entry->next;
      }

      // Clean up key and value if destroy functions are provided
      if (map->key_destroy && entry->key) {
        map->key_destroy(entry->key);
      }
      if (map->value_destroy && entry->tensor) {
        map->value_destroy(entry->tensor);
      }

      free(entry);
      map->count--;
      return 0;
    }
    prev = entry;
    entry = entry->next;
  }

  return -1; // Key not found
}

// Clear all entries from the map
void map_clear(TensorMap *map) {
  if (!map)
    return;

  for (size_t i = 0; i < map->size; i++) {
    TensorMapEntry *entry = map->buckets[i];
    while (entry) {
      TensorMapEntry *next = entry->next;

      // Clean up key and value if destroy functions are provided
      if (map->key_destroy && entry->key) {
        map->key_destroy(entry->key);
      }
      if (map->value_destroy && entry->tensor) {
        map->value_destroy(entry->tensor);
      }

      free(entry);
      entry = next;
    }
    map->buckets[i] = NULL;
  }
  map->count = 0;
}

size_t map_size(TensorMap *map) { return map ? map->count : 0; }

int map_is_empty(TensorMap *map) { return map ? (map->count == 0) : 1; }

TensorMapIterator map_iterator(TensorMap *map) {
  TensorMapIterator iter = {0};
  if (!map)
    return iter;

  iter.map = map;
  iter.bucket_index = 0;
  iter.entry = NULL;
  return iter;
}

int map_iterator_next(TensorMapIterator *iter, int *key, Tensor *tensor) {
  if (!iter || !iter->map || !key || !tensor)
    return -1;

  if (iter->entry) {
    iter->entry = iter->entry->next;
  }

  while (!iter->entry && iter->bucket_index < iter->map->size) {
    iter->entry = iter->map->buckets[iter->bucket_index];
    if (!iter->entry) {
      iter->bucket_index++;
    }
  }

  if (iter->entry) {
    *key = iter->entry->key;
    tensor = iter->entry->tensor;
    return 0;
  }

  return -1;
}

void map_iterator_destroy(TensorMapIterator *iter) { (void)iter; }

size_t hash_int(const int key) {
  return (size_t)((unsigned int)key * 2654435761U);
}

int compare_hash_int(const int key1, const int key2) {
  return (key1 > key2) - (key1 < key2);
}