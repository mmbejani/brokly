#include "mm/allocator.h"
#include "mm/pool.h"
#include "mm/allocator_interface.h"
#include "mm/thread_local_allocator.h"
#include "mm/config.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

// Global allocator instance
static Allocator* g_allocator = NULL;

// Initialize the memory management system
static void mm_init() {
    if (g_allocator == NULL) {
        g_allocator = thread_local_allocator_create(MM_DEFAULT_POOL_SIZE, MM_DEFAULT_BLOCK_SIZE);
    }
}

Allocator* mm_create_allocator(const char* type, size_t size) {
    return tlsf_allocator_create(size);
}

void mm_destroy_allocator(Allocator* allocator) {
    if (allocator && allocator->vtable && allocator->vtable->reset) {
        allocator->vtable->reset(allocator);
    }
}

void* mm_alloc(size_t size) {
    if (g_allocator == NULL) {
        mm_init();
    }
    
    if (size == 0) {
        return NULL;
    }
    void* ptr = allocator_alloc(g_allocator, size);    
    return ptr;
}

void mm_free(void* ptr) {
    if (g_allocator == NULL || ptr == NULL) {
        return;
    }
    allocator_free(g_allocator, ptr);
}

void mm_reset() {
    if (g_allocator) {
        allocator_reset(g_allocator);
        stats_reset();
    }
}

size_t mm_get_used_memory() {
    if (g_allocator) {
        return allocator_get_used_memory(g_allocator);
    }
    return 0;
}

size_t mm_get_free_memory() {
    if (g_allocator) {
        return allocator_get_free_memory(g_allocator);
    }
    return 0;
}

void mm_enable_tracking() {
    // Implementation would enable detailed tracking
}

void mm_disable_tracking() {
    // Implementation would disable detailed tracking
}

void mm_print_stats() {
    #if MM_ENABLE_TRACKING
    stats_print();
    #endif
}