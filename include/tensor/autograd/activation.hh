#pragma once

#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"
#include "tensor/autograd/Common.hh"
#include <map>
namespace momas::brokly::tensor::autograd {
std::map<NamedTensor, Tensor<float32> *>
sigmoidBackward(std::map<NamedTensor, Tensor<float32> *> context);
std::map<NamedTensor, Tensor<float32> *>
tanhBackward(std::map<NamedTensor, Tensor<float32> *> context);
std::map<NamedTensor, Tensor<float32> *>
reluBackward(std::map<NamedTensor, Tensor<float32> *> context);
} // namespace momas::brokly::tensor::brokly::autograd