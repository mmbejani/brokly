#pragma once
#include "nn/module.hpp"
#include "tensor/tensor.hpp"

namespace momas::brokly::nn {

class Linear : public Module {
public:
  Linear(const unsigned int inFeature, const unsigned int outFeature,
         bool hasBias = true);

  tensor::Tensor *forward(const tensor::Tensor *input) const;

  tensor::Tensor *weight, *bias;
};

class LinearReLU : public Linear {};

class LinearReLUBatchNorm : public Linear {};
} // namespace momas::brokly::nn