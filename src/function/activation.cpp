#include "function/activation.hpp"
#include "backend/act.h"
#include "tensor/tensor.hpp"
#include <math.h>
#include <stddef.h>

namespace momas::brokly::function {
void sigmoid(tensor::Tensor *input, const float32 lambda,
             tensor::Tensor *output) {
  ::sigmoid(input->data, output->data, input->size);
}

__attribute__((always_inline)) void relu(tensor::Tensor *input,
                                         tensor::Tensor *output) {
  ::relu(input->data, output->data, input->size);
}

} // namespace momas::brokly::function