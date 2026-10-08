#include "tensor/tensor.hpp"
#include "base.h"
#include <cstdlib>
#include <cstring>
#include <stddef.h>
#include <stdlib.h>
#include <vector>

namespace momas::brokly::tensor {

Tensor::Tensor(std::vector<unsigned int> size, TensorType type,
               bool requires_grad, TensorAllocMode allocationMode)
    : type(type), requires_grad(requires_grad), dims(size),
      allocationMode(allocationMode), usedCounter(0) {
  // Calculate the total size by multiplying all dimensions
  this->size = 1;
  for (auto dim : dims) {
    this->size *= dim;
  }

  // Initialize data based on tensor type
  switch (type) {
  case TensorType::DENSE:
    this->data = new float32[this->size];
    break;
  case TensorType::ZEROS:
    this->data = new float[1];
    break;
  case TensorType::ONES:
    this->data = new float[1];
    break;
  default:
    this->data = new float32[this->size];
    for (unsigned int i = 0; i < this->size; ++i) {
      this->data[i] = 0.0f;
    }
    break;
  }
}

Tensor::~Tensor() {
  if (this->data != nullptr) {
    delete[] this->data;
    this->data = nullptr;
  }
}

// Static factory methods
Tensor *Tensor::ones(std::vector<unsigned int> size, TensorType tensorType,
                     TensorAllocMode allocMode) {
  if (tensorType == TensorType::ONES)
    return new Tensor(std::vector<unsigned int>{1}, TensorType::ONES, false,
                      allocMode);
  else if (tensorType == TensorType::DENSE) {
    auto t = new Tensor(size, tensorType, false, allocMode);
    assign_value(t->data, 1.0f, t->size);
  }

  // TODO: log a great message that ONE or DENSE type of tensor accepable
  exit(-1);
}

Tensor *Tensor::zeros(std::vector<unsigned int> size, TensorType tensorType,
                      TensorAllocMode allocMode) {
  return new Tensor(size, TensorType::ZEROS, false, allocMode);
}

Tensor *Tensor::rand(std::vector<unsigned int> size,
                     TensorAllocMode allocMode) {
  Tensor *result = new Tensor(std::vector<unsigned int>{1}, TensorType::DENSE,
                              false, allocMode);
  // Initialize with random values - for now just set to 0.5
  result->data[0] =
      0.5f; // In practice you'd want to use a proper random generator
  return result;
}

} // namespace momas::brokly::tensor