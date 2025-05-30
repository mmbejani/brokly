#pragma once

#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"
namespace momas::brokly::function::matrix {
    tensor::Tensor<tensor::float32> *add(tensor::Tensor<tensor::float32>&, tensor::Tensor<tensor::float32>&);
    tensor::Tensor<tensor::float32> *add_matrix_vector(tensor::Tensor<tensor::float32>&, tensor::Tensor<tensor::float32>&);
    tensor::Tensor<tensor::float32> *sub(tensor::Tensor<tensor::float32>&, tensor::Tensor<tensor::float32>&);
    tensor::Tensor<tensor::float32> *dot(tensor::Tensor<tensor::float32>&, tensor::Tensor<tensor::float32>&);
    tensor::Tensor<tensor::float32> *matmul(tensor::Tensor<tensor::float32>&, tensor::Tensor<tensor::float32>&);
}