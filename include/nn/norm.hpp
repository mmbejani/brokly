#pragma once

#include "nn/module.hpp"
#include "tensor/tensor.hpp"
namespace momas::brokly::nn {
class BatchNorm : public Module {
public:
  BatchNorm(unsigned int feature_size);

  tensor::Tensor *forward_with_update(const tensor::Tensor *input);
  tensor::Tensor *forward(const tensor::Tensor *input) const;
  tensor::Tensor *mean, *variance;
};

class LayerNorm : public Module {
public:
  LayerNorm();

  tensor::Tensor *forward_with_update(const tensor::Tensor *input);
  tensor::Tensor *forward(const tensor::Tensor *input) const;
  tensor::Tensor *mean, *variance;
};

class RMSNorm : public Module {};
} // namespace momas::brokly::nn