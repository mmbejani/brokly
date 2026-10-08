#pragma once

#include <vector>

namespace momas::brokly::tensor {
class Tensor;
}

namespace momas::brokly::cg {
struct Node {
  std::vector<tensor::Tensor *> incomings;
  std::vector<tensor::Tensor *> outcomings;
};

class ComputationGraph {};
} // namespace momas::brokly::cg