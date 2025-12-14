#include "nn/linear.hpp"
#include "function/linear.hpp"
#include "tensor/tensor.hpp"

namespace momas::brokly::nn {

tensor::Tensor *Linear::forward(const tensor::Tensor *input) const {
  auto output = tensor::Tensor::zeros(tensor::EPHEMERAL);
  function::linear(input, this->weight, this->bias, output);
  return output;
}
} // namespace momas::brokly::nn