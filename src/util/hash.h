#ifndef BROKLY_UTIL_HASH_H
#define BROKLY_UTIL_HASH_H

#include <stddef.h>

// Hash table entry structure
typedef struct HashTensorEntry {
    int key;
    void* value;
    struct HashTensorEntry* next;
} HashEntry;

typedef struct HashTensorTable {
    HashEntry** buckets;
    size_t size;
    size_t count;
} HashTensorTable;

// Function prototypes
HashTensorTable* hash_create(size_t size);
void hash_destroy(HashTensorTable* table);
int hash_insert(HashTensorTable* table, int key, void* value);
void* hash_get(HashTensorTable* table, int key);
int hash_remove(HashTensorTable* table, int key);
void hash_clear(HashTensorTable* table);

// Simple hash function for integer keys
static inline size_t hash_function(int key, size_t table_size) {
    // Using a simple modulo hash with a prime multiplier for better distribution
    return (size_t)((unsigned int)key * 2654435761U) % table_size;
}

#endif // BROKLY_UTIL_HASH_H