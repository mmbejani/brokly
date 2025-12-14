#include "optim/base.hpp"
#include "tensor/tensor.hpp"
#include <vector>

namespace momas::brokly::optim {
Optimizer::Optimizer(std::vector<tensor::Tensor *> parameters,
                     float32 learning_rate)
    : parameters(parameters), learning_rate(learning_rate) {}
} // namespace momas::brokly::optim