#pragma once

#include "tensor/tensor.hpp"

namespace momas::brokly::function {
__attribute__((always_inline)) void linear(const tensor::Tensor *input,
                                           const tensor::Tensor *weight,
                                           const tensor::Tensor *bias,
                                           tensor::Tensor *output);
__attribute__((always_inline)) void linear_fused(const tensor::Tensor *input,
                                                 const tensor::Tensor *weight,
                                                 const tensor::Tensor *bias,
                                                 tensor::Tensor *output);
} // namespace momas::brokly::function
