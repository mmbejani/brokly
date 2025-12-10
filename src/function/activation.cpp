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

void silu(tensor::Tensor *input, tensor::Tensor *output) {
  for (size_t i = 0; i < input->size; i++) {
    output->data[i] = input->data[i] * (1 / (1 + expf(input->data[i])));
  }
}

} // namespace momas::brokly::function