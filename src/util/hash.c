#include "util/hash.h"
#include <stdlib.h>

// Create a new hash table
HashTable* hash_create(size_t size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) return NULL;
    
    table->buckets = (HashEntry**)calloc(size, sizeof(HashEntry*));
    if (!table->buckets) {
        free(table);
        return NULL;
    }
    
    table->size = size;
    table->count = 0;
    return table;
}

// Destroy the hash table and free all memory
void hash_destroy(HashTable* table) {
    if (!table) return;
    
    hash_clear(table);
    free(table->buckets);
    free(table);
}

// Insert a key-value pair into the hash table
int hash_insert(HashTable* table, int key, void* value) {
    if (!table) return -1;
    
    size_t index = hash_function(key, table->size);
    
    // Check if key already exists
    HashEntry* entry = table->buckets[index];
    while (entry) {
        if (entry->key == key) {
            entry->value = value;  // Update existing value
            return 0;
        }
        entry = entry->next;
    }
    
    // Create new entry
    HashEntry* new_entry = (HashEntry*)malloc(sizeof(HashEntry));
    if (!new_entry) return -1;
    
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = table->buckets[index];
    table->buckets[index] = new_entry;
    table->count++;
    
    return 0;
}

// Get a value by key from the hash table
void* hash_get(HashTable* table, int key) {
    if (!table) return NULL;
    
    size_t index = hash_function(key, table->size);
    HashEntry* entry = table->buckets[index];
    
    while (entry) {
        if (entry->key == key) {
            return entry->value;
        }
        entry = entry->next;
    }
    
    return NULL;  // Key not found
}

// Remove a key-value pair from the hash table
int hash_remove(HashTable* table, int key) {
    if (!table) return -1;
    
    size_t index = hash_function(key, table->size);
    HashEntry* entry = table->buckets[index];
    HashEntry* prev = NULL;
    
    while (entry) {
        if (entry->key == key) {
            if (prev) {
                prev->next = entry->next;
            } else {
                table->buckets[index] = entry->next;
            }
            free(entry);
            table->count--;
            return 0;
        }
        prev = entry;
        entry = entry->next;
    }
    
    return -1;  // Key not found
}

// Clear all entries from the hash table
void hash_clear(HashTable* table) {
    if (!table) return;
    
    for (size_t i = 0; i < table->size; i++) {
        HashEntry* entry = table->buckets[i];
        while (entry) {
            HashEntry* next = entry->next;
            free(entry);
            entry = next;
        }
        table->buckets[i] = NULL;
    }
    table->count = 0;
}