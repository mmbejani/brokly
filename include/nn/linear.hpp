#pragma once
#include "tensor/tensor.hpp"
#include <vector>

namespace momas::brokly::nn {

class Linear {
public:
  Linear(const unsigned int inFeature, const unsigned int outFeature,
         bool hasBias = true);

  tensor::Tensor *forward(tensor::Tensor *input) const;

  std::vector<tensor::Tensor *> parameters() const;

  tensor::Tensor *weight, *bias;
};

class LinearReLUBatchNorm {};

class LinearSequential {};

class LinearSequentialReLULayerNorm {};

} // namespace momas::brokly::nn