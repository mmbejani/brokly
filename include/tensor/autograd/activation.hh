#pragma once

#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"
#include "tensor/autograd/common.hh"
#include <map>
namespace momas::brokly::tensor::autograd {
void sigmoidBackward(std::map<NamedTensor, Tensor<float32> *> context);
void tanhBackward(std::map<NamedTensor, Tensor<float32> *> context);
void reluBackward(std::map<NamedTensor, Tensor<float32> *> context);
} // namespace momas::brokly::tensor::autograd