#include "init/init.hpp"
#include <memory>

namespace momas::brokly {
memory::MemoryPool::Ptr epool, rpool;

void initialize(const InitConfing &cfg) {
  memory::MemoryPool::MemoryConfig memCfg{};
  epool = std::make_shared<memory::MemoryPool>(memCfg);
  rpool = std::make_shared<memory::MemoryPool>(memCfg);
}

memory::MemoryPool::Ptr getEphemeral() { return epool; }
void makeEphemeralFree() { epool->free(); }
memory::MemoryPool::Ptr getResidental() { return rpool; }
} // namespace momas::brokly