#pragma once

#include "tensor/tensor.hpp"
#include <vector>
namespace momas::brokly::cg {
struct Node {
  std::vector<tensor::TensorPtr> incomings;
  std::vector<tensor::TensorPtr> outcomings;
};

class ComputationGraph {};
} // namespace momas::brokly::cg