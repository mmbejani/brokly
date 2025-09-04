#include "mm/thread_local_allocator.h"
#include "mm/pool.h"
#include "mm/config.h"
#include <stdlib.h>
#include <pthread.h>

// Thread-local storage key
static pthread_key_t tls_key;
static pthread_once_t tls_key_once = PTHREAD_ONCE_INIT;

// Thread-local allocator data
typedef struct {
    MemoryPool* pool;
    size_t used_memory;
} ThreadLocalData;

// Create the TLS key
static void make_tls_key() {
    pthread_key_create(&tls_key, NULL);
}

// Get thread-local data
static ThreadLocalData* get_tls_data() {
    pthread_once(&tls_key_once, make_tls_key);
    ThreadLocalData* data = (ThreadLocalData*)pthread_getspecific(tls_key);
    if (!data) {
        data = (ThreadLocalData*)calloc(1, sizeof(ThreadLocalData));
        if (data) {
            data->pool = pool_create(MM_DEFAULT_POOL_SIZE, MM_DEFAULT_BLOCK_SIZE);
            pthread_setspecific(tls_key, data);
        }
    }
    return data;
}

// Thread-local allocator vtable functions
static void* thread_local_alloc(Allocator* self, size_t size) {
    ThreadLocalData* data = get_tls_data();
    if (!data || !data->pool) {
        return malloc(size);
    }
    
    if (size <= data->pool->block_size) {
        void* ptr = pool_alloc(data->pool);
        if (ptr) {
            data->used_memory += data->pool->block_size;
            return ptr;
        }
    }
    
    // Fall back to malloc for large allocations
    void* ptr = malloc(size);
    if (ptr) {
        data->used_memory += size;
    }
    return ptr;
}

static void thread_local_free(Allocator* self, void* ptr) {
    // In a real implementation, we would need to determine if the pointer
    // belongs to our thread-local pool or was allocated with malloc
    // For now, we'll just free it with free (which handles malloc'd pointers)
    free(ptr);
}

static void thread_local_reset(Allocator* self) {
    ThreadLocalData* data = get_tls_data();
    if (data && data->pool) {
        pool_reset(data->pool);
        data->used_memory = 0;
    }
}

static size_t thread_local_get_used_memory(Allocator* self) {
    ThreadLocalData* data = get_tls_data();
    return data ? data->used_memory : 0;
}

static size_t thread_local_get_free_memory(Allocator* self) {
    ThreadLocalData* data = get_tls_data();
    if (data && data->pool) {
        return pool_get_free_memory(data->pool);
    }
    return 0;
}

// Thread-local allocator vtable
static AllocatorVTable thread_local_vtable = {
    .alloc = thread_local_alloc,
    .free = thread_local_free,
    .reset = thread_local_reset,
    .get_used_memory = thread_local_get_used_memory,
    .get_free_memory = thread_local_get_free_memory
};

Allocator* thread_local_allocator_create(size_t pool_size, size_t block_size) {
    // Create a thread-local allocator
    ThreadLocalAllocator* tls_alloc = (ThreadLocalAllocator*)malloc(sizeof(ThreadLocalAllocator));
    if (!tls_alloc) {
        return NULL;
    }
    
    tls_alloc->base.vtable = &thread_local_vtable;
    tls_alloc->base.private_data = NULL;
    tls_alloc->pool_size = pool_size;
    tls_alloc->block_size = block_size;
    
    // Initialize TLS key if not already done
    pthread_once(&tls_key_once, make_tls_key);
    
    return (Allocator*)tls_alloc;
}

void thread_local_allocator_destroy(Allocator* allocator) {
    if (allocator) {
        free(allocator);
    }
}

void thread_local_allocator_reset() {
    ThreadLocalData* data = get_tls_data();
    if (data && data->pool) {
        pool_reset(data->pool);
        data->used_memory = 0;
    }
}

void thread_local_allocator_cleanup(void* ptr) {
    ThreadLocalData* data = (ThreadLocalData*)ptr;
    if (data) {
        if (data->pool) {
            pool_destroy(data->pool);
        }
        free(data);
    }
}