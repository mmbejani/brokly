#include "tensor/tensor.h"
#include <stddef.h>
#include <stdlib.h>

Tensor *create_tensor(TensorType type, bool requires_grad, unsigned int *dims) {
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

unsigned int *create_dim(unsigned int x, unsigned int y, unsigned int z,
                         unsigned int w) {
  unsigned int *dim = (unsigned int *)malloc(sizeof(unsigned int) * 4);
  dim[0] = x;
  dim[1] = y;
  dim[2] = z;
  dim[3] = w;
  return dim;
}
