#pragma once

#include <stddef.h>
#include <stdbool.h>

// Forward declarations
typedef struct MemoryPool MemoryPool;
typedef struct MemoryBlock MemoryBlock;

// Memory block structure
struct MemoryBlock {
    size_t size;
    bool is_free;
    MemoryBlock* next;
    MemoryBlock* prev;
};

// Memory pool structure
struct MemoryPool {
    void* memory_start;
    size_t pool_size;
    size_t block_size;
    size_t used_memory;
    size_t free_memory;
    MemoryBlock* free_list;
    MemoryBlock* allocated_list;
    MemoryPool* next_pool;  // For pool chaining
};

// Function prototypes
MemoryPool* pool_create(size_t pool_size, size_t block_size);
void pool_destroy(MemoryPool* pool);
void* pool_alloc(MemoryPool* pool);
void pool_free(MemoryPool* pool, void* ptr);
bool pool_expand(MemoryPool* pool, size_t additional_size);
void pool_reset(MemoryPool* pool);
size_t pool_get_used_memory(MemoryPool* pool);
size_t pool_get_free_memory(MemoryPool* pool);
bool pool_is_full(MemoryPool* pool);