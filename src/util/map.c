#include "util/map.h"
#include "util/hash.h"
#include <stdlib.h>
#include <string.h>

// Create a new map with custom hash and compare functions
Map* map_create(size_t size, hash_function_t hash_func, key_compare_t key_cmp) {
    Map* map = (Map*)malloc(sizeof(Map));
    if (!map) return NULL;
    
    map->buckets = (MapEntry**)calloc(size, sizeof(MapEntry*));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    
    map->size = size;
    map->count = 0;
    map->hash_func = hash_func;
    map->key_cmp = key_cmp;
    map->key_destroy = NULL;
    map->value_destroy = NULL;
    
    return map;
}

MapTensor* map_create_int(size_t size) {
    return map_create(size, hash_int, compare_int);
}

// Convenience function for creating a map with string keys
MapTensor* map_create_str(size_t size) {
    return map_create(size, hash_str, compare_str);
}

// Destroy the map and free all memory
void map_destroy(MapTensor* map) {
    if (!map) return;
    
    map_clear(map);
    free(map->buckets);
    free(map);
}

// Insert a key-value pair into the map
int map_insert(MapTensor* map, int key, Tensor* tensor) {
    if (!map || !key) return -1;
    
    size_t index = map->hash_func(key) % map->size;
    
    // Check if key already exists
    MapTensorEntry* entry = map->buckets[index];
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
    MapTensorEntry* new_entry = (MapTensorEntry*)malloc(sizeof(MapTensorEntry));
    if (!new_entry) return -1;
    
    new_entry->key = key;
    new_entry->tensor = tensor;
    new_entry->next = map->buckets[index];
    map->buckets[index] = new_entry;
    map->count++;
    
    return 0;
}

// Get a value by key from the map
void* map_get(MapTensor* map, const int key) {
    if (!map || !key) return NULL;
    
    size_t index = map->hash_func(key) % map->size;
    MapTensorEntry* entry = map->buckets[index];
    
    while (entry) {
        if (map->key_cmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    
    return NULL;  // Key not found
}

// Remove a key-value pair from the map
int map_remove(MapTensor* map, const void* key) {
    if (!map || !key) return -1;
    
    size_t index = map->hash_func(key) % map->size;
    MapTensorEntry* entry = map->buckets[index];
    MapTensorEntry* prev = NULL;
    
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
            if (map->value_destroy && entry->value) {
                map->value_destroy(entry->value);
            }
            
            free(entry);
            map->count--;
            return 0;
        }
        prev = entry;
        entry = entry->next;
    }
    
    return -1;  // Key not found
}

// Clear all entries from the map
void map_clear(Map* map) {
    if (!map) return;
    
    for (size_t i = 0; i < map->size; i++) {
        MapEntry* entry = map->buckets[i];
        while (entry) {
            MapEntry* next = entry->next;
            
            // Clean up key and value if destroy functions are provided
            if (map->key_destroy && entry->key) {
                map->key_destroy(entry->key);
            }
            if (map->value_destroy && entry->value) {
                map->value_destroy(entry->value);
            }
            
            free(entry);
            entry = next;
        }
        map->buckets[i] = NULL;
    }
    map->count = 0;
}

// Get the number of entries in the map
size_t map_size(Map* map) {
    return map ? map->count : 0;
}

// Check if the map is empty
int map_is_empty(Map* map) {
    return map ? (map->count == 0) : 1;
}

// Create a new iterator for the map
MapIterator map_iterator(Map* map) {
    MapIterator iter = {0};
    if (!map) return iter;
    
    iter.map = map;
    iter.bucket_index = 0;
    iter.entry = NULL;
    return iter;
}

int map_iterator_next(MapIterator* iter, int* keys, Tensor* tensors) {
    if (!iter || !iter->map || !keys || !tensors) return -1;
    
    if (iter->entry) {
        iter->entry = iter->entry->next;
    }
    
    // If we don't have an entry, find the next non-empty bucket
    while (!iter->entry && iter->bucket_index < iter->map->size) {
        iter->entry = iter->map->buckets[iter->bucket_index];
        if (!iter->entry) {
            iter->bucket_index++;
        }
    }
    
    // If we found an entry, return its key and value
    if (iter->entry) {
        *key = iter->entry->key;
        *value = iter->entry->value;
        return 0;
    }
    
    // No more entries
    return -1;
}

// Destroy the iterator (currently a no-op but included for API completeness)
void map_iterator_destroy(MapIterator* iter) {
    // Nothing to do for this implementation
    (void)iter;
}

// Default hash function for integer keys
size_t hash_int(const void* key) {
    int k = *(const int*)key;
    return (size_t)((unsigned int)k * 2654435761U);
}

// Default key compare function for integer keys
int compare_int(const void* key1, const void* key2) {
    int k1 = *(const int*)key1;
    int k2 = *(const int*)key2;
    return (k1 > k2) - (k1 < k2);
}

// Default key compare function for string keys
int compare_str(const void* key1, const void* key2) {
    return strcmp((const char*)key1, (const char*)key2);
}