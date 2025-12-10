#pragma once
#include "tensor/tensor.hpp"

namespace momas::brokly::function {
void sigmoid(tensor::Tensor *input, const float32 lambda,
             tensor::Tensor *output);
void softmax(tensor::Tensor *input, tensor::Tensor *output);
void relu(tensor::Tensor *input, tensor::Tensor *output);
} // namespace momas::brokly::function