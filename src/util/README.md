# Utility Functions

## Hash Table Implementation

This directory contains a simple hash table implementation that maps integer keys to pointer values.

### Features

- Maps integer keys to generic pointer values
- Handles hash collisions using chaining
- Dynamic memory management
- Simple and efficient API

### API

#### `HashTable* hash_create(size_t size)`
Creates a new hash table with the specified number of buckets.

Parameters:
- `size`: Number of buckets in the hash table

Returns:
- Pointer to the new hash table, or NULL on failure

#### `void hash_destroy(HashTable* table)`
Destroys the hash table and frees all associated memory.

Parameters:
- `table`: Pointer to the hash table to destroy

#### `int hash_insert(HashTable* table, int key, void* value)`
Inserts a key-value pair into the hash table.

Parameters:
- `table`: Pointer to the hash table
- `key`: Integer key
- `value`: Pointer value to store

Returns:
- 0 on success, -1 on failure

#### `void* hash_get(HashTable* table, int key)`
Retrieves a value by key from the hash table.

Parameters:
- `table`: Pointer to the hash table
- `key`: Integer key to look up

Returns:
- Pointer to the value, or NULL if key not found

#### `int hash_remove(HashTable* table, int key)`
Removes a key-value pair from the hash table.

Parameters:
- `table`: Pointer to the hash table
- `key`: Integer key to remove

Returns:
- 0 on success, -1 if key not found

#### `void hash_clear(HashTable* table)`
Removes all entries from the hash table.

Parameters:
- `table`: Pointer to the hash table

### Usage Example

```c
#include "util/hash.h"
#include <stdio.h>
#include <string.h>

int main() {
    // Create a hash table with 16 buckets
    HashTable* table = hash_create(16);
    
    // Insert some values
    char* value1 = "First value";
    char* value2 = "Second value";
    
    hash_insert(table, 1, value1);
    hash_insert(table, 2, value2);
    
    // Retrieve values
    char* result1 = (char*)hash_get(table, 1);
    char* result2 = (char*)hash_get(table, 2);
    
    printf("Value 1: %s
", result1);
    printf("Value 2: %s
", result2);
    
    // Clean up
    hash_destroy(table);
    
    return 0;
}
```

### Implementation Details

- Uses chaining to resolve hash collisions
- Employs a simple modulo hash function with a prime multiplier for better distribution
- Provides O(1) average case performance for insert, get, and remove operations
- Memory efficient implementation with proper cleanup functions

## Generic Map Implementation

This directory also contains a more flexible map implementation that can work with different key types.

### Features

- Generic key-value mapping
- Support for custom hash functions and key comparison
- Convenience functions for common key types (int, string)
- Iterator support for traversing map entries
- Optional memory management for keys and values

### API

#### `Map* map_create(size_t size, hash_function_t hash_func, key_compare_t key_cmp)`
Creates a new map with custom hash and comparison functions.

Parameters:
- `size`: Number of buckets in the map
- `hash_func`: Function to hash keys
- `key_cmp`: Function to compare keys

Returns:
- Pointer to the new map, or NULL on failure

#### `Map* map_create_int(size_t size)`
Creates a new map optimized for integer keys.

Parameters:
- `size`: Number of buckets in the map

Returns:
- Pointer to the new map, or NULL on failure

#### `Map* map_create_str(size_t size)`
Creates a new map optimized for string keys.

Parameters:
- `size`: Number of buckets in the map

Returns:
- Pointer to the new map, or NULL on failure

#### `void map_destroy(Map* map)`
Destroys the map and frees all associated memory.

Parameters:
- `map`: Pointer to the map to destroy

#### `int map_insert(Map* map, void* key, void* value)`
Inserts a key-value pair into the map.

Parameters:
- `map`: Pointer to the map
- `key`: Pointer to the key
- `value`: Pointer to the value

Returns:
- 0 on success, -1 on failure

#### `void* map_get(Map* map, const void* key)`
Retrieves a value by key from the map.

Parameters:
- `map`: Pointer to the map
- `key`: Pointer to the key to look up

Returns:
- Pointer to the value, or NULL if key not found

#### `int map_remove(Map* map, const void* key)`
Removes a key-value pair from the map.

Parameters:
- `map`: Pointer to the map
- `key`: Pointer to the key to remove

Returns:
- 0 on success, -1 if key not found

#### `void map_clear(Map* map)`
Removes all entries from the map.

Parameters:
- `map`: Pointer to the map

#### `size_t map_size(Map* map)`
Returns the number of entries in the map.

Parameters:
- `map`: Pointer to the map

Returns:
- Number of entries in the map

#### `int map_is_empty(Map* map)`
Checks if the map is empty.

Parameters:
- `map`: Pointer to the map

Returns:
- 1 if empty, 0 otherwise

#### `MapIterator map_iterator(Map* map)`
Creates a new iterator for the map.

Parameters:
- `map`: Pointer to the map

Returns:
- Initialized iterator

#### `int map_iterator_next(MapIterator* iter, void** key, void** value)`
Moves to the next entry in the map.

Parameters:
- `iter`: Pointer to the iterator
- `key`: Output parameter for the key
- `value`: Output parameter for the value

Returns:
- 0 on success, -1 if no more entries

#### `void map_iterator_destroy(MapIterator* iter)`
Destroys the iterator.

Parameters:
- `iter`: Pointer to the iterator

### Usage Example

```c
#include "util/map.h"
#include <stdio.h>
#include <string.h>

int main() {
    // Create a map for string keys
    Map* map = map_create_str(16);
    
    // Insert some values
    char* key1 = "first";
    char* key2 = "second";
    char* value1 = "First value";
    char* value2 = "Second value";
    
    map_insert(map, key1, value1);
    map_insert(map, key2, value2);
    
    // Retrieve values
    char* result1 = (char*)map_get(map, "first");
    char* result2 = (char*)map_get(map, "second");
    
    printf("Value 1: %s
", result1);
    printf("Value 2: %s
", result2);
    
    // Iterate through all entries
    MapIterator iter = map_iterator(map);
    void* key;
    void* value;
    
    while (map_iterator_next(&iter, &key, &value) == 0) {
        printf("Key: %s, Value: %s
", (char*)key, (char*)value);
    }
    
    // Clean up
    map_destroy(map);
    
    return 0;
}
```