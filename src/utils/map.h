#pragma once

#include "tensor/tensor.h"
#include <stddef.h>
#include <stdint.h>

enum TensorName { OP1_NAME, OP2_NAME, OUT_NAME, ACT_BK_NAME };

typedef struct TensorMapEntry {
  int key;
  Tensor *tensor;
  struct TensorMapEntry *next;
} TensorMapEntry;

typedef size_t (*hash_function_t)(const int key);
typedef int (*key_compare_t)(const int key1, const int key2);
typedef void (*key_destroy_t)(int key);
typedef void (*value_destroy_t)(Tensor *tensor);

typedef struct TensorMap {
  TensorMapEntry **buckets;
  size_t size;
  size_t count;
  hash_function_t hash_func;
  key_compare_t key_cmp;
  key_destroy_t key_destroy;
  value_destroy_t value_destroy;
} TensorMap;

typedef struct TensorMapIterator {
  struct TensorMap *map;
  size_t bucket_index;
  TensorMapEntry *entry;
} TensorMapIterator;

TensorMap *map_create(size_t size);
void map_destroy(TensorMap *map);
int map_insert(TensorMap *map, int key, Tensor *tensor);
Tensor *map_get(TensorMap *map, const int key);
int map_remove(TensorMap *map, const int key);
void map_clear(TensorMap *map);
size_t map_size(TensorMap *map);
int map_is_empty(TensorMap *map);

TensorMapIterator map_iterator(TensorMap *map);
int map_iterator_next(TensorMapIterator *iter, int *key, Tensor *tensors);
void map_iterator_destroy(TensorMapIterator *iter);

size_t hash_int(const int key);
int compare_hash_int(const int key1, const int key2);