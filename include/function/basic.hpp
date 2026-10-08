#pragma once

#include "tensor/tensor.hpp"

namespace momas::brokly::function {
__attribute__((always_inline)) void
add(tensor::Tensor *input, tensor::Tensor *base, tensor::Tensor *output);

__attribute__((always_inline)) void
sub(tensor::Tensor *input, tensor::Tensor *base, tensor::Tensor *output);
} // namespace momas::brokly::function