#include "function/linear.hpp"
#include "backend/mat.h"

namespace momas::brokly::function {
void linear(tensor::Tensor *input, tensor::Tensor *weight, tensor::Tensor *bias,
            tensor::Tensor *output) {
  matmul(input->data, weight->data, output->data, input->dims[2],
         weight->dims[2], input->dims[3]);
  addmatvec(output->data, bias->data, output->data, output->dims[2],
            output->dims[3]);

  // Add track to CG
}
} // namespace momas::brokly::function