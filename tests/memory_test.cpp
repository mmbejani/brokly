#include "memory/pool.hpp"
#include <cstdlib>
#include <gtest/gtest.h>

using namespace momas::brokly::memory;

TEST(Memory, Allocation) {
    void* ptr = malloc(64ULL * 1024 * 1024);
    MemoryPool::MemoryConfig cfg {
        .buffer_size = 64ULL * 1024 * 1024,
        .buffer_ptr = ptr,
       .type= MemoryType::RESIDENT,
    };

    MemoryPool pool(cfg);
    int* iptr = pool.getMemory<int>(10);
    float* fptr = pool.getMemory(20);

    for(int i = 0;i < 10;i++)
        iptr[i] = i * 2;

    for(int i = 0;i < 20; i++)
        fptr[i] = 3.14f * i;
    
    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(iptr[i], i * 2);
    }

    for (int i = 0; i < 20; i++) {
        ASSERT_EQ(fptr[i], 3.14f * i);
    }
}