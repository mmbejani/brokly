#include "nn/linear.hpp"
#include "function/linear.hpp"
#include "tensor/tensor.hpp"

namespace momas::brokly::nn {

tensor::Tensor *Linear::forward(tensor::Tensor *input) {
  // Allocate new space for output
  function::linear(input, this->weight, this->bias, output);
  return output;
}
} // namespace momas::brokly::nn