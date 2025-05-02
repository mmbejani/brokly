#pragma once
#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"

namespace momas::brokly::function::base {
template <typename T>
tensor::Tensor<T> *constant(tensor::dim4 dimension, float c) {
  static_assert(
      false, "There is no generic implementation for create constant Tensor");
}

template <typename T>
tensor::Tensor<T> *zeros(tensor::dim4 dimension, float c) {
  static_assert(false,
                "There is no generic implementation for create zero Tensor");
}

template <typename T> tensor::Tensor<T> *ones(tensor::dim4 dimension, float c) {
  static_assert(false,
                "There is no generic implementation for create ones Tensor");
}

template <typename T> tensor::Tensor<T> *rand(tensor::dim4 dimension, float c) {
  static_assert(false,
                "There is no generic implementation for create random Tensor");
}
tensor::Tensor<tensor::float32> *constant(tensor::dim4 dimension, float c);
tensor::Tensor<tensor::float32> *zeros(tensor::dim4 dimension);
tensor::Tensor<tensor::float32> *ones(tensor::dim4 dimension);
tensor::Tensor<tensor::float32> *rand(tensor::dim4 dimension,
                                      bool requires_grad = false);
} // namespace momas::brokly::function::base
