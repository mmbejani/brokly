#pragma once

#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"
namespace momas::brokly::function {
    tensor::Tensor<tensor::float32> *add(const tensor::Tensor<tensor::float32>&, tensor::float32);
    tensor::Tensor<tensor::float32> *sub(const tensor::Tensor<tensor::float32>&, tensor::float32);
    tensor::Tensor<tensor::float32> *sub(tensor::float32, const tensor::Tensor<tensor::float32>&);
    tensor::Tensor<tensor::float32> *dot(const tensor::Tensor<tensor::float32>&, tensor::float32);
    tensor::Tensor<tensor::float32> *div(const tensor::Tensor<tensor::float32>&, tensor::float32);
    tensor::Tensor<tensor::float32> *div(tensor::float32, const tensor::Tensor<tensor::float32>&);
}