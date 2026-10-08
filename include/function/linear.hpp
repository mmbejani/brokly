#pragma once

#include "tensor/tensor.hpp"

namespace momas::brokly::function {
/**
 * @brief compute classic linear function forward
 *
 * @param input
 * @param weight
 * @param bias
 * @param output
 */
__attribute__((always_inline)) void linear(tensor::Tensor *input,
                                           tensor::Tensor *weight,
                                           tensor::Tensor *bias,
                                           tensor::Tensor *output);
__attribute__((always_inline)) void linear_fused(tensor::Tensor *input,
                                                 tensor::Tensor *weight,
                                                 tensor::Tensor *bias,
                                                 tensor::Tensor *output);

__attribute__((always_inline)) void linear_sequential(tensor::Tensor *input,
                                                      tensor::Tensor *weight,
                                                      tensor::Tensor *bias,
                                                      tensor::Tensor *output);
} // namespace momas::brokly::function
