# Memory Allocator

This directory contains a custom memory allocator implementation designed for tensor operations. The allocator manages memory in a single contiguous block and partitions it into different regions for different types of allocations.

## Overview

The memory allocator is implemented as a pool-based system that:
- Requests one contiguous memory block from the OS using `mmap`
- Partitions the block into distinct regions for different allocation strategies
- Provides fixed-size hash tables for efficient ID-to-pointer mapping
- Supports both resident (long-lived) and ephemeral (short-lived) tensor allocations

## Architecture

The allocator divides the memory pool into three main components:

1. **Pool Header**: Contains metadata about the entire memory pool
2. **Hash Tables**: Fixed-size tables for mapping tensor IDs to memory offsets
3. **Allocation Regions**:
   - **Resident Region**: Uses a bump allocator for long-lived tensors
   - **Ephemeral Region**: Uses a free-list allocator for short-lived tensors

## Key Features

### Resident Allocation
- Simple bump allocator strategy
- Suitable for long-lived tensors that persist throughout computation
- Very fast allocation with minimal overhead
- Cannot be freed individually; requires pool reset for cleanup

### Ephemeral Allocation
- Free-list based allocator with first-fit strategy
- Designed for temporary tensors that are frequently allocated and freed
- Supports coalescing of free blocks to reduce fragmentation
- Individual allocations can be freed by ID

### Hash-based Lookup
- Uses linear probing hash tables for O(1) average lookup times
- Separate tables for resident and ephemeral tensors
- Maps user-provided tensor IDs to memory offsets

## API

```c
// Initialize a memory pool of specified size
Pool* pool_init(size_t total_bytes);

// Allocate resident tensor (bump allocator)
void* allocate_resident(Pool* p, uint64_t id, size_t size);

// Allocate ephemeral tensor (free-list allocator)
void* allocate_ephemeral(Pool* p, uint64_t id, size_t size);

// Free ephemeral tensor by ID
int free_ephemeral(Pool* p, uint64_t id);

// Get tensor pointer by ID
void* get_tensor_ptr(Pool* p, uint64_t id);

// Debug information
void pool_debug(Pool* p);
```

## Memory Layout

```
[PoolHeader][resident_table][ephemeral_table][resident_region][ephemeral_region]
```

1. **Pool Header**: Contains pool metadata
2. **Resident Hash Table**: ID mappings for resident tensors
3. **Ephemeral Hash Table**: ID mappings for ephemeral tensors
4. **Resident Region**: Sequentially allocated long-lived tensors
5. **Ephemeral Region**: Free-list managed short-lived tensors

## Design Considerations

- Written in plain C for maximum clarity and minimal dependencies
- Avoids any heap allocations outside the single mmap region
- Uses memory alignment for better performance on modern processors
- Implements simple but effective memory management strategies

## Limitations

- This is an instructive example, not production-ready
- Hash tables have fixed size and can become full
- No thread safety mechanisms
- Simple coalescing strategy may not be optimal for all workloads