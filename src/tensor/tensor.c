#include "tensor/tensor.h"
#include <stddef.h>

Tensor *create_tensor(TensorType type, bool requires_grad) {
  switch (type) {
  case ZEROS:
    create_zero_tensor(requires_grad);
    break;
  case ONES:
    create_one_tensor(requires_grad);
    break;
  default:
    return NULL;
    break;
  }
  return NULL;
}
