#include "tensor/tensor.hpp"
#include "base.h"
#include "init/init.hpp"
#include <cstdlib>
#include <cstring>
#include <stddef.h>
#include <stdlib.h>
#include <vector>

namespace momas::brokly::tensor {

Tensor::Tensor(std::vector<unsigned int> dims, TensorType type,
               bool requires_grad, TensorAllocMode allocationMode)
    : type(type), requires_grad(requires_grad), dims(dims),
      allocationMode(allocationMode), usedCounter(0) {
  // Calculate the total size by multiplying all dimensions
  this->size = 1;
  for (auto dim : dims) {
    this->size *= dim;
  }

  // Initialize data based on tensor type
  if (allocationMode == TensorAllocMode::EPHEMERAL)
    switch (type) {
    [[likely]]
    case TensorType::DENSE:
      this->data = getEphemeral()->getMemory<float>(this->size);
      break;
    case TensorType::ZEROS:
    case TensorType::ONES:
      this->data = getEphemeral()->getMemory<float>(1);
      break;
    default:
      break;
    }
  else if (allocationMode == TensorAllocMode::RESIDENT) {
    switch (type) {
    [[likely]]
    case TensorType::DENSE:
      this->data = getResidental()->getMemory<float>(this->size);
      break;
    case TensorType::ZEROS:
    case TensorType::ONES:
      this->data = getResidental()->getMemory<float>(1);
      break;
    default:
      break;
    }
  };
}

// Static factory methods
Tensor *Tensor::ones(std::vector<unsigned int> dims, TensorType tensorType,
                     TensorAllocMode allocMode) {
  if (tensorType == TensorType::ONES)
    return new Tensor(dims, TensorType::ONES, false, allocMode);
  else if (tensorType == TensorType::DENSE) {
    auto t = new Tensor(dims, tensorType, false, allocMode);
    assign_value(t->data, 1.0f, t->size);
  }

  // TODO: log a great message that ONE or DENSE type of tensor accepable
  exit(-1);
}

Tensor *Tensor::zeros(std::vector<unsigned int> dims, TensorType tensorType,
                      TensorAllocMode allocMode) {
  return new Tensor(dims, TensorType::ZEROS, false, allocMode);
}

Tensor *Tensor::rand(std::vector<unsigned int> dims, bool required_grad,
                     TensorAllocMode allocMode) {
  Tensor *result =
      new Tensor(dims, TensorType::DENSE, required_grad, allocMode);

  return result;
}

} // namespace momas::brokly::tensor