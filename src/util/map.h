#pragma once

#include <stddef.h>
#include <stdint.h>
#include "tensor/fp32/tensor.h"

typedef struct MapTensorEntry
{
    int key;
    Tensor *tensor;
    struct MapTensorEntry *next;
} MapTensorEntry;

typedef size_t (*hash_function_t)(const void *key);
typedef int (*key_compare_t)(const void *key1, const void *key2);
typedef void (*key_destroy_t)(void *key);
typedef void (*value_destroy_t)(void *value);

typedef struct MapTensor
{
    struct MapTensorEntry **buckets;
    size_t size;
    size_t count;
    hash_function_t hash_func;
    key_compare_t key_cmp;
    key_destroy_t key_destroy;
    value_destroy_t value_destroy;
} MapTensor;

// Map iterator
typedef struct MapIterator
{
    struct MapTensor *map;
    size_t bucket_index;
    struct MapTensorEntry *entry;
} MapIterator;

// Function prototypes
MapTensor *map_create(size_t size, hash_function_t hash_func, key_compare_t key_cmp);
MapTensor *map_create_str(size_t size); // Convenience function for string keys
void map_destroy(MapTensor *map);
int map_insert(MapTensor *map, int key, Tensor *value);
void *map_get(MapTensor *map, const int key);
int map_remove(MapTensor *map, const int key);
void map_clear(MapTensor *map);
size_t map_size(MapTensor *map);
int map_is_empty(MapTensor *map);

// Iterator functions
MapIterator map_iterator(MapTensor *map);
int map_iterator_next(MapIterator *iter, int *key, Tensor *tensors);
void map_iterator_destroy(MapIterator *iter);

size_t hash_int(const int key);
int compare_int(const int key1, const int key2);