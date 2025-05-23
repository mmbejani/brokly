#pragma once
#include "function/matrix.hh"
#include "nn/Module.hh"
#include "tensor/Tensor.hh"
#include <vector>

namespace momas::brokly::nn {

template <typename T> class Linear : Module<T> {
public:
  Linear(const unsigned short input_feature, const short output_features)
      : input_features(input_feature), output_features(output_features) {}

  std::vector<tensor::Tensor<T> *>
  forward(std::vector<tensor::Tensor<T> *> inputs) override {
    tensor::Tensor<T> *x = inputs[0];

    static_assert(x->dimension.dz == this->weight->dimension.dz,
                  "The feature dim is not equal to weight dim 1");
    auto y = function::matrix::matmul(*x, *weight);
    y = function::matrix::add(*y, *bias);

    return {y};
  }

  const unsigned input_features, output_features;
  tensor::Tensor<T> *weight, bias;
};

} // namespace momas::brokly::nn