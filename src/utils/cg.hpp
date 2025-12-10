#pragma once

#include "tensor/tensor.hpp"
#include <vector>
namespace momas::brokly::cg {
struct Node {
  std::vector<tensor::Tensor *> incomings;
  std::vector<tensor::Tensor *> outcomings;
};

class ComputationGraph {};
} // namespace momas::brokly::cg