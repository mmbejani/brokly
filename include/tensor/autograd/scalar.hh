#pragma once

#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"
#include "tensor/autograd/Common.hh"
#include <map>
namespace momas::brokly::tensor::autograd {
std::map<NamedTensor, tensor::Tensor<float32> *>
addScalarBackward(std::map<NamedTensor, tensor::Tensor<float32> *> context);
std::map<NamedTensor, tensor::Tensor<float32> *>
subScalarBackward(std::map<NamedTensor, tensor::Tensor<float32> *> context);
std::map<NamedTensor, tensor::Tensor<float32> *>
mulScalarBackward(std::map<NamedTensor, tensor::Tensor<float32> *> context);
} // namespace momas::brokly::tensor::autograd