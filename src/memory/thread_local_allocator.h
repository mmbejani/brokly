#pragma once

#include "allocator_interface.h"
#include <pthread.h>

// Thread-local allocator structure
typedef struct {
    Allocator base;
    pthread_key_t tls_key;
    size_t pool_size;
    size_t block_size;
} ThreadLocalAllocator;

// Function prototypes
Allocator* thread_local_allocator_create(size_t pool_size, size_t block_size);
void thread_local_allocator_destroy(Allocator* allocator);
void* thread_local_alloc(size_t size);
void thread_local_free(void* ptr);
void thread_local_allocator_reset();
void thread_local_allocator_cleanup(void* ptr);