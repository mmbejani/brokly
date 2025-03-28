#pragma once
#include "tensor/Tensor.hh"
#include "tensor/Dtype.hh"

namespace momas::brokly::function
{
    tensor::Tensor<tensor::float32>* constant(tensor::dim4 dimension, float c);
    tensor::Tensor<tensor::float32>* zeros(tensor::dim4 dimension);
    tensor::Tensor<tensor::float32>* ones(tensor::dim4 dimension);
    tensor::Tensor<tensor::float32>* rand(tensor::dim4 dimension, bool requires_grad = false);
} // namespace momas::brokly::function
