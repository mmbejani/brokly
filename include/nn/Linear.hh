#pragma once
#include "function/matrix.hh"
#include "nn/Module.hh"
#include "tensor/Tensor.hh"
#include <vector>

namespace momas::brokly::nn {

template <typename T> class Linear : Module<T> {
public:
  // Standart `Linear` module (may known as `Dense`), it computes affine transformation
  // on input. The affine transformation change the dimensions of the vectors from `input_feature`
  // to `output_features`.
  Linear(const unsigned short input_feature, const short output_features)
      : input_features(input_feature), output_features(output_features) {}

  // The forward computation of linear module that compute y = Wx + b
  // This method calls `forward` method in this class
  // Consider that inputs vector contains a single tensor::Tensor<T> named as
  // `x`. The output also contains a vector with single tensor::Tensor<T> named
  // as `y`.
  // 
  // The shape of `W` is `[1,1, output_feature, input_feature]`

  // The shape of `x` is `[1,1, batch_size, input_feature]
  // TODO: currently it does not support sequence, but it will!
  inline std::vector<tensor::Tensor<T> *>
  operator()(std::vector<tensor::Tensor<T> *> inputs) const {
    return this->forward(inputs);
  }

  const unsigned input_features, output_features;
  tensor::Tensor<T> *weight, bias;

private:
  std::vector<tensor::Tensor<T> *>
  forward(std::vector<tensor::Tensor<T> *> inputs) override {
    tensor::Tensor<T> *x = inputs[0];

    static_assert(x->dimension.dz == this->weight->dimension.dz,
                  "The feature dim is not equal to weight dim 1");
    auto y = function::matrix::matmul(*x, *weight);
    y = function::matrix::add_matrix_vector(*y, *bias);
    return {y};
  }
};

} // namespace momas::brokly::nn