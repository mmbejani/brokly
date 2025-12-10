#pragma once

#include "tensor/tensor.hpp"

namespace momas::brokly::function {
float32 mean_squard_error_loss_forward(tensor::Tensor *input,
                                       tensor::Tensor *target, bool inplace = true);
float32 cross_entropy_loss_forward(tensor::Tensor *input, tensor::Tensor *target);
} // namespace momas::brokly::function