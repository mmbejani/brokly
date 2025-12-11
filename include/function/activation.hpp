#pragma once
#include "tensor/tensor.hpp"

namespace momas::brokly::function {
__attribute__((always_inline)) void
sigmoid(tensor::Tensor *input, const float32 lambda, tensor::Tensor *output);
__attribute__((always_inline)) void relu(tensor::Tensor *input,
                                         tensor::Tensor *output);
} // namespace momas::brokly::function