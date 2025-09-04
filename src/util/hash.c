#include "util/hash.h"
#include "tensor/fp32/tensor.h"
#include <stdlib.h>

HashTensorTable *hash_create(size_t size)
{
    HashTensorTable *table = (HashTensorTable *)malloc(sizeof(HashTensorTable));
    if (!table)
        return NULL;

    table->buckets = (HashTensorEntry **)calloc(size, sizeof(HashTensorEntry *));
    if (!table->buckets)
    {
        free(table);
        return NULL;
    }

    table->size = size;
    table->count = 0;
    return table;
}

void hash_destroy(HashTensorTable *table)
{
    if (!table)
        return;

    hash_clear(table);
    free(table->buckets);
    free(table);
}

int hash_insert(HashTensorTable *table, int key, Tensor *tensor)
{
    if (!table)
        return -1;

    size_t index = hash_function(key, table->size);

    HashTensorEntry *entry = table->buckets[index];
    while (entry)
    {
        if (entry->key == key)
        {
            entry->value = tensor;
            return 0;
        }
        entry = entry->next;
    }

    HashTensorEntry *new_entry = (HashTensorEntry *)malloc(sizeof(HashTensorEntry));
    if (!new_entry)
        return -1;

    new_entry->key = key;
    new_entry->value = tensor;
    new_entry->next = table->buckets[index];
    table->buckets[index] = new_entry;
    table->count++;

    return 0;
}

void *hash_get(HashTensorTable *table, int key)
{
    if (!table)
        return NULL;

    size_t index = hash_function(key, table->size);
    HashTensorEntry *entry = table->buckets[index];

    while (entry)
    {
        if (entry->key == key)
        {
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL; // Key not found
}

// Remove a key-value pair from the hash table
int hash_remove(HashTensorTable *table, int key)
{
    if (!table)
        return -1;

    size_t index = hash_function(key, table->size);
    HashTensorEntry *entry = table->buckets[index];
    HashTensorEntry *prev = NULL;

    while (entry)
    {
        if (entry->key == key)
        {
            if (prev)
            {
                prev->next = entry->next;
            }
            else
            {
                table->buckets[index] = entry->next;
            }
            free(entry);
            table->count--;
            return 0;
        }
        prev = entry;
        entry = entry->next;
    }

    return -1; // Key not found
}

// Clear all entries from the hash table
void hash_clear(HashTensorTable *table)
{
    if (!table)
        return;

    for (size_t i = 0; i < table->size; i++)
    {
        HashTensorEntry *entry = table->buckets[i];
        while (entry)
        {
            HashTensorEntry *next = entry->next;
            free(entry);
            entry = next;
        }
        table->buckets[i] = NULL;
    }
    table->count = 0;
}