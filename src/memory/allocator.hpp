#include "stddef.h"
#include "stdint.h"
#include "tensor/tensor.hpp"

namespace momas::brokly::alloc {

struct Arena {
  uint8_t *base;
  size_t capacity;
  size_t offset;
};

class TensorAllocator {
public:
  tensor::Tensor *allocateResident(size_t size, int id);
  tensor::Tensor *allocateEphemeral(size_t size, int id);
  void freeEphemeral(int id);
  tensor::Tensor *getTensor(int id);

private:
  void *base;
  size_t capacity;
};

} // namespace momas::brokly::alloc