#pragma once
#include "tensor/tensor.hpp"
#include <cstdint>
#include <vector>

namespace momas::brokly::nn {

class Linear {
public:
  Linear(const uint32_t inFeature, const uint32_t outFeature,
         bool hasBias = true);

  tensor::Tensor *forward(tensor::Tensor *input);

  std::vector<tensor::Tensor *> parameters() const;

  tensor::Tensor *weight, *bias;

private:
  tensor::Tensor *output;
};

class LinearFused {
  LinearFused(const uint32_t inFeature, const uint32_t outFeature);

  tensor::Tensor *forward(tensor::Tensor *input);
  std::vector<tensor::Tensor *> parameters() const;
  tensor::Tensor *weight, *bias, *output;
};

class LinearReLUBatchNorm {};

class LinearSequential {};

class LinearSequentialReLULayerNorm {};

} // namespace momas::brokly::nn