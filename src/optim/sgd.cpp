#include "optim/sgd.hpp"
#include "optim/base.hpp"
#include "tensor/tensor.hpp"
#include <ranges>
#include <vector>

namespace momas::brokly::optim {

StochaticGradientDescent::StochaticGradientDescent(
    std::vector<tensor::Tensor *> parameters, float32 learning_rate,
    float32 momentum)
    : Optimizer(parameters, learning_rate), momentum(momentum),
      firstStep(true) {
  this->velocities = std::vector<tensor::Tensor *>();
}

void StochaticGradientDescent::zero_grad() noexcept {
  for (auto &parameter : this->parameters) {
    parameter->grad = tensor::Tensor::zeros(tensor::EPHEMERAL);
  }
}

void StochaticGradientDescent::step() noexcept {
  for (auto [parameter, velocity] :
       std::ranges::views::zip(this->parameters, this->velocities)) {
    parameter->grad->mulInplace((firstStep ? 1.0f : (1 - this->momentum)) *
                                learning_rate);
    velocity->mulInplace(momentum);
    velocity->addInplace(parameter->grad);
    parameter->subInplace(velocity);
  }
}
} // namespace momas::brokly::optim