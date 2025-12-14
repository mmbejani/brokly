#include "backend/base.h"
#include "tensor/tensor.hpp"
#include <cstring>

namespace momas::brokly::tensor {

// Implementation of member operators
Tensor* Tensor::operator+(Tensor* rhs) const {
    if (!rhs) return nullptr;

    // Create a new tensor with the same dimensions as 'this'
    Tensor* result = new Tensor(this->dims, this->type, this->requires_grad, this->allocationMode);

    // Perform element-wise addition
    for (unsigned int i = 0; i < this->size; ++i) {
        result->data[i] = this->data[i] + rhs->data[i];
    }

    return result;
}

Tensor* Tensor::operator-(Tensor* rhs) const {
    if (!rhs) return nullptr;

    // Create a new tensor with the same dimensions as 'this'
    Tensor* result = new Tensor(this->dims, this->type, this->requires_grad, this->allocationMode);

    // Perform element-wise subtraction
    for (unsigned int i = 0; i < this->size; ++i) {
        result->data[i] = this->data[i] - rhs->data[i];
    }

    return result;
}

Tensor* Tensor::operator*(float32 scalar) const {
    // Create a new tensor with the same dimensions as 'this'
    Tensor* result = new Tensor(this->dims, this->type, this->requires_grad, this->allocationMode);

    // Perform element-wise multiplication by scalar
    for (unsigned int i = 0; i < this->size; ++i) {
        result->data[i] = this->data[i] * scalar;
    }

    return result;
}

// Free-standing operators for pointer arithmetic
Tensor* operator+(const Tensor* lhs, const Tensor* rhs) {
    if (!lhs || !rhs) return nullptr;

    // Create a new tensor with the same dimensions as lhs
    Tensor* result = new Tensor(lhs->dims, lhs->type, lhs->requires_grad, lhs->allocationMode);

    // Perform element-wise addition
    for (unsigned int i = 0; i < lhs->size; ++i) {
        result->data[i] = lhs->data[i] + rhs->data[i];
    }

    return result;
}

Tensor* operator-(const Tensor* lhs, const Tensor* rhs) {
    if (!lhs || !rhs) return nullptr;

    // Create a new tensor with the same dimensions as lhs
    Tensor* result = new Tensor(lhs->dims, lhs->type, lhs->requires_grad, lhs->allocationMode);

    // Perform element-wise subtraction
    for (unsigned int i = 0; i < lhs->size; ++i) {
        result->data[i] = lhs->data[i] - rhs->data[i];
    }

    return result;
}

Tensor* operator*(const Tensor* lhs, float32 scalar) {
    if (!lhs) return nullptr;

    // Create a new tensor with the same dimensions as lhs
    Tensor* result = new Tensor(lhs->dims, lhs->type, lhs->requires_grad, lhs->allocationMode);

    // Perform element-wise multiplication by scalar
    for (unsigned int i = 0; i < lhs->size; ++i) {
        result->data[i] = lhs->data[i] * scalar;
    }

    return result;
}

Tensor* operator*(float32 scalar, const Tensor* rhs) {
    return operator*(rhs, scalar);
}

float32 Tensor::sum() const { return sum_reduce_vec(this->data, this->size); }
float32 Tensor::mean() const { return this->sum() / this->size; }
float32 Tensor::item() const { return this->data[0]; }

} // namespace momas::brokly::tensor