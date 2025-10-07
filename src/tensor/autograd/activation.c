#include "tensor/autograd/activation.h"
#include "tensor/tensor.h"
#include "utils/map.h"
#include <stdbool.h>
#include <stddef.h>

void sigmoidBackward(TensorMap *context, TensorMap *backwardHook) {
  Tensor *out = map_get(context, OUT_NAME);
  Tensor *backward = create_tensor(DENSE, false, out->dim);
  for (size_t i = 0; i < out->size; i++) {
    backward->data[i] = out->data[i] * (1 - out->data[i]);
  }
  map_insert(backwardHook, ACT_BK_NAME, backward);
}