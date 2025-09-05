#pragma once

#include <stddef.h>

// Forward declaration
typedef struct Allocator Allocator;

// Allocator interface vtable
typedef struct {
    void* (*alloc)(Allocator* self, size_t size);
    void (*free)(Allocator* self, void* ptr);
    void (*reset)(Allocator* self);
    size_t (*get_used_memory)(Allocator* self);
    size_t (*get_free_memory)(Allocator* self);
} AllocatorVTable;

// Base allocator structure
struct Allocator {
    AllocatorVTable* vtable;
    void* private_data;
};

// Allocator interface functions
void* allocator_alloc(Allocator* allocator, size_t size);
void allocator_free(Allocator* allocator, void* ptr);
void allocator_reset(Allocator* allocator);
size_t allocator_get_used_memory(Allocator* allocator);
size_t allocator_get_free_memory(Allocator* allocator);

// Specific allocator implementations
Allocator* pool_allocator_create(size_t pool_size, size_t block_size);
Allocator* tlsf_allocator_create(size_t initial_size);  // Two-Level Segregated Fit
Allocator* fallback_allocator_create();  // Uses malloc/free as fallback