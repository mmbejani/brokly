#ifndef BROKLY_UTIL_HASH_H
#define BROKLY_UTIL_HASH_H

#include <stddef.h>
#include <tensor/fp32/tensor.h>

// Hash table entry structure
typedef struct HashTensorEntry
{
    int key;
    Tensor *value;
    struct HashTensorEntry *next;
} HashTensorEntry;

typedef struct HashTensorTable
{
    HashTensorEntry **buckets;
    size_t size;
    size_t count;
} HashTensorTable;

HashTensorTable *hash_create(size_t size);
void hash_destroy(HashTensorTable *table);
int hash_insert(HashTensorTable *table, int key, void *value);
void *hash_get(HashTensorTable *table, int key);
int hash_remove(HashTensorTable *table, int key);
void hash_clear(HashTensorTable *table);

static inline size_t hash_function(int key, size_t table_size)
{
    return (size_t)((unsigned int)key * 2654435761U) % table_size;
}

#endif // BROKLY_UTIL_HASH_H