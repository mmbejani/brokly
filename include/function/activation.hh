#pragma once

#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"
namespace momas::brokly::function {
    tensor::Tensor<tensor::float32> *sigmoid(tensor::Tensor<tensor::float32>&&);
    tensor::Tensor<tensor::float32> *tanh(tensor::Tensor<tensor::float32>&&);
    tensor::Tensor<tensor::float32> *relu(tensor::Tensor<tensor::float32>&&);
}