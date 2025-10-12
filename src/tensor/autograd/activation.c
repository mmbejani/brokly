#include "tensor/autograd/activation.h"
#include "tensor/tensor.h"
#include "utils/map.h"
#include <stdbool.h>
#include <stddef.h>

void sigmoidBackward(TensorMap *context, TensorMap *backwardHook) {
  Tensor *out = map_get(context, TN_OUT_NAME);
  unsigned int *grad_dim = create_dim(1, 1, 1, out->dim[3]);
  Tensor *backward = create_tensor(ZEROS, false, grad_dim);
  // TODO: Can be upgrade use SIMD to make more efficient
  for (size_t i = 0; i < out->size; i++) {
    backward->data[i / out->dim[2]] += out->data[i] * (1 - out->data[i]);
  }
  map_insert(backwardHook, TN_BP, backward);
}