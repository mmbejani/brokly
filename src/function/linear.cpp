#include "function/linear.hpp"
#include "backend/mat.h"
#include "tensor/tensor.hpp"

namespace momas::brokly::function {
void linear(tensor::Tensor *input, tensor::Tensor *weight, tensor::Tensor *bias,
            tensor::Tensor *output) {
  matmul(input->data, weight->data, output->data, input->dims[2],
         weight->dims[2], input->dims[3]);
  addmatvec(output->data, bias->data, output->data, output->dims[2],
            output->dims[3]);
  input->forwardHooks.push_back(output);
  weight->forwardHooks.push_back(output);
  bias->forwardHooks.push_back(output);

  output->backwardHooks.push_back(input);
  output->backwardHooks.push_back(weight);
  output->backwardHooks.push_back(bias);
}
} // namespace momas::brokly::function