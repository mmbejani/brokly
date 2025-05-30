#pragma once
#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"
#include "tensor/autograd/common.hh"
#include <map>


namespace momas::brokly::tensor::autograd {
    void matmulBackward(std::map<NamedTensor, Tensor<float32> *> context);
    void addVecBackward(std::map<NamedTensor, Tensor<float32> *> context);
}