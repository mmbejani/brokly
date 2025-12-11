#include "tensor/tensor.hpp"
#include <stddef.h>
#include <stdlib.h>
#include <vector>

namespace momas::brokly::tensor {

Tensor::Tensor(std::vector<unsigned int> size, TensorType type,
               bool requires_grad, TensorAllocMode allocationMode)
    : type(type), requires_grad(requires_grad), dims(size),
      allocationMode(allocationMode) {}
} // namespace momas::brokly::tensor