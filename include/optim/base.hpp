#pragma once

#include "tensor/tensor.hpp"
#include <vector>
namespace momas::brokly::optim {

class Optimizer {
public:
  Optimizer(std::vector<tensor::Tensor *> parameters,
            float32 learning_rate = 0.1f);

  virtual void zero_grad() noexcept;
  virtual void step() noexcept;

protected:
  std::vector<tensor::Tensor *> parameters;
  float32 learning_rate;
};
} // namespace momas::brokly::optim