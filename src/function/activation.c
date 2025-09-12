#include "function/activation.h"
#include <math.h>
#include <stddef.h>

void sigmoid(const Tensor *input, const float32 lambda, const Tensor *output) {
  for (size_t i = 0; i < input->size; i++) {
    output->data[i] = 1 / (1 + lambda * expf(input->data[i]));
  }
}

