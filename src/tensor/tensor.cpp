#include "tensor/tensor.hpp"
#include <stddef.h>
#include <stdlib.h>
#include <vector>
#include <numeric> // for std::accumulate

namespace momas::brokly::tensor {

Tensor::Tensor(std::vector<unsigned int> size, TensorType type,
               bool requires_grad, TensorAllocMode allocationMode)
    : type(type), requires_grad(requires_grad), dims(size),
      allocationMode(allocationMode) {
    // Calculate the total size by multiplying all dimensions
    this->size = 1;
    for (auto dim : dims) {
        this->size *= dim;
    }

    // Allocate memory based on the calculated size
    this->data = new float32[this->size];

    // Initialize data based on tensor type
    switch (type) {
        case DENSE:
            // Data remains uninitialized for DENSE tensors
            break;
        case ZEROS:
            // Initialize all values to 0
            for (unsigned int i = 0; i < this->size; ++i) {
                this->data[i] = 0.0f;
            }
            break;
        case ONES:
            // Initialize all values to 1
            for (unsigned int i = 0; i < this->size; ++i) {
                this->data[i] = 1.0f;
            }
            break;
        default:
            // For other types, initialize to zero as default
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
Tensor* Tensor::ones(TensorAllocMode allocMode) {
    return new Tensor(std::vector<unsigned int>{1}, ONES, false, allocMode);
}

Tensor* Tensor::zeros(TensorAllocMode allocMode) {
    return new Tensor(std::vector<unsigned int>{1}, ZEROS, false, allocMode);
}

Tensor* Tensor::rand(TensorAllocMode allocMode) {
    Tensor* result = new Tensor(std::vector<unsigned int>{1}, DENSE, false, allocMode);
    // Initialize with random values - for now just set to 0.5
    result->data[0] = 0.5f; // In practice you'd want to use a proper random generator
    return result;
}

} // namespace momas::brokly::tensor