#pragma once

#include "optim/base.hpp"
#include "tensor/tensor.hpp"
#include <vector>
namespace momas::brokly::optim {

class StochaticGradientDescent : private Optimizer {
public:
  StochaticGradientDescent(std::vector<tensor::Tensor *> parameters,
                           float32 learning_rate = 0.1f,
                           float32 momentum = 0.9f);
  void zero_grad() noexcept override;
  void step() noexcept override;

private:
  float32 momentum;
  std::vector<tensor::Tensor *> velocities;
  bool firstStep;
};
} // namespace momas::brokly::optim