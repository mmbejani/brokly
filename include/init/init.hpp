#pragma once
#include "memory/pool.hpp"

#include <cstdint>
namespace momas::brokly {
struct InitConfing {
  uint32_t ncpu;
  uint64_t ephemeralSize;
  uint64_t residentalSize;
};

void initialize(const InitConfing &cfg);

memory::MemoryPool::Ptr getEphemeral();
void makeEphemeralFree();
memory::MemoryPool::Ptr getResidental();

} // namespace momas::brokly