#include "mm/pool.h"
#include "mm/config.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

MemoryPool* pool_create(size_t pool_size, size_t block_size) {
    // Ensure block size is at least the minimum and properly aligned
    if (block_size < MM_MIN_BLOCK_SIZE) {
        block_size = MM_MIN_BLOCK_SIZE;
    }
    
    // Align block size to MM_ALIGNMENT
    block_size = (block_size + MM_ALIGNMENT - 1) & ~(MM_ALIGNMENT - 1);
    
    // Allocate memory for the pool structure and the actual memory pool
    MemoryPool* pool = (MemoryPool*)malloc(sizeof(MemoryPool));
    if (!pool) {
        return NULL;
    }
    
    // Allocate the actual memory pool with extra space for alignment
    void* raw_memory = malloc(pool_size + MM_ALIGNMENT - 1);
    if (!raw_memory) {
        free(pool);
        return NULL;
    }
    
    // Align the memory to MM_ALIGNMENT boundary
    uintptr_t aligned_addr = ((uintptr_t)raw_memory + MM_ALIGNMENT - 1) & ~(MM_ALIGNMENT - 1);
    pool->memory_start = (void*)aligned_addr;
    
    pool->pool_size = pool_size;
    pool->block_size = block_size;
    pool->used_memory = 0;
    pool->free_memory = pool_size;
    pool->free_list = NULL;
    pool->allocated_list = NULL;
    pool->next_pool = NULL;
    
    // Initialize the free list with all blocks
    size_t num_blocks = pool_size / block_size;
    for (size_t i = 0; i < num_blocks; i++) {
        MemoryBlock* block = (MemoryBlock*)((char*)pool->memory_start + i * block_size);
        block->size = block_size;
        block->is_free = true;
        block->next = pool->free_list;
        block->prev = NULL;
        if (pool->free_list) {
            pool->free_list->prev = block;
        }
        pool->free_list = block;
    }
    
    return pool;
}

void pool_destroy(MemoryPool* pool) {
    if (!pool) {
        return;
    }
    
    // Free the raw memory (the aligned memory_start is within this)
    free((char*)pool->memory_start - ((uintptr_t)pool->memory_start % MM_ALIGNMENT));
    free(pool);
}

void* pool_alloc(MemoryPool* pool) {
    if (!pool || !pool->free_list) {
        return NULL;
    }
    
    // Take the first block from the free list
    MemoryBlock* block = pool->free_list;
    pool->free_list = block->next;
    
    // Add to allocated list
    block->next = pool->allocated_list;
    block->prev = NULL;
    if (pool->allocated_list) {
        pool->allocated_list->prev = block;
    }
    pool->allocated_list = block;
    
    block->is_free = false;
    pool->used_memory += block->size;
    pool->free_memory -= block->size;
    
    // Return pointer to the memory after the block header
    return (void*)((char*)block + sizeof(MemoryBlock));
}

void pool_free(MemoryPool* pool, void* ptr) {
    if (!pool || !ptr) {
        return;
    }
    
    // Get the block header from the pointer
    MemoryBlock* block = (MemoryBlock*)((char*)ptr - sizeof(MemoryBlock));
    
    // Remove from allocated list
    if (block->prev) {
        block->prev->next = block->next;
    } else {
        pool->allocated_list = block->next;
    }
    
    if (block->next) {
        block->next->prev = block->prev;
    }
    
    // Add to free list
    block->next = pool->free_list;
    block->prev = NULL;
    if (pool->free_list) {
        pool->free_list->prev = block;
    }
    pool->free_list = block;
    
    block->is_free = true;
    pool->used_memory -= block->size;
    pool->free_memory += block->size;
}

bool pool_expand(MemoryPool* pool, size_t additional_size) {
    // This is a simplified implementation
    // A full implementation would need to handle expanding the pool
    // For now, we'll just return false to indicate expansion is not supported
    return false;
}

void pool_reset(MemoryPool* pool) {
    if (!pool) {
        return;
    }
    
    // Move all allocated blocks back to the free list
    MemoryBlock* block = pool->allocated_list;
    while (block) {
        MemoryBlock* next = block->next;
        
        // Reset block
        block->is_free = true;
        block->next = pool->free_list;
        block->prev = NULL;
        
        // Add to free list
        if (pool->free_list) {
            pool->free_list->prev = block;
        }
        pool->free_list = block;
        
        block = next;
    }
    
    // Clear allocated list
    pool->allocated_list = NULL;
    
    // Reset memory counters
    pool->used_memory = 0;
    pool->free_memory = pool->pool_size;
}

size_t pool_get_used_memory(MemoryPool* pool) {
    return pool ? pool->used_memory : 0;
}

size_t pool_get_free_memory(MemoryPool* pool) {
    return pool ? pool->free_memory : 0;
}

bool pool_is_full(MemoryPool* pool) {
    return pool ? (pool->free_list == NULL) : true;
}