#ifndef BROKLY_UTIL_MAP_H
#define BROKLY_UTIL_MAP_H

#include <stddef.h>
#include <stdint.h>

// Map entry structure
typedef struct MapEntry {
    void* key;
    void* value;
    struct MapEntry* next;
} MapEntry;

typedef struct Map Map;

// Function pointer types for custom operations
typedef size_t (*hash_function_t)(const void* key);
typedef int (*key_compare_t)(const void* key1, const void* key2);
typedef void (*key_destroy_t)(void* key);
typedef void (*value_destroy_t)(void* value);

// Map structure
struct Map {
    struct MapEntry** buckets;
    size_t size;
    size_t count;
    hash_function_t hash_func;
    key_compare_t key_cmp;
    key_destroy_t key_destroy;
    value_destroy_t value_destroy;
};

// Map iterator
typedef struct MapIterator {
    Map* map;
    size_t bucket_index;
    struct MapEntry* entry;
} MapIterator;

// Function prototypes
Map* map_create(size_t size, hash_function_t hash_func, key_compare_t key_cmp);
Map* map_create_int(size_t size);  // Convenience function for int keys
Map* map_create_str(size_t size);  // Convenience function for string keys
void map_destroy(Map* map);
int map_insert(Map* map, void* key, void* value);
void* map_get(Map* map, const void* key);
int map_remove(Map* map, const void* key);
void map_clear(Map* map);
size_t map_size(Map* map);
int map_is_empty(Map* map);

// Iterator functions
MapIterator map_iterator(Map* map);
int map_iterator_next(MapIterator* iter, void** key, void** value);
void map_iterator_destroy(MapIterator* iter);

// Default hash functions
size_t hash_int(const void* key);
size_t hash_str(const void* key);

// Default key compare functions
int compare_int(const void* key1, const void* key2);
int compare_str(const void* key1, const void* key2);

#endif // BROKLY_UTIL_MAP_H