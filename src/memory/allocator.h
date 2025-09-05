#pragma once

// Main allocator header that includes all necessary components

#include "pool.h"
#include "allocator_interface.h"
#include "thread_local_allocator.h"

// Public API functions
Allocator* mm_create_allocator(const char* type, size_t size, ...);
void mm_destroy_allocator(Allocator* allocator);
void* mm_alloc(size_t size);
void mm_free(void* ptr);
void mm_reset();
size_t mm_get_used_memory();
size_t mm_get_free_memory();

// Memory tracking and debugging
void mm_enable_tracking();
void mm_disable_tracking();
void mm_print_stats();

