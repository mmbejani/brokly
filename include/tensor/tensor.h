#pragma once

#include "tensor/define.h"
#include "utils/dag.h"
#include <stdalign.h>
#include <stdbool.h>

typedef enum TensorType {
  DENSE,
  ZEROS,
  ONES,
  DIAG,
  EYE,
  DIAG_BLOCK_EYES,
  BLOCK,
} TensorType;

typedef void (*backward_t)(NodeCG *);

typedef struct __attribute__((aligned(64))) Tensor {
  bool requires_grad;
  TensorType type;
  unsigned int size;
  float32 *data;
  NodeCG *cg_node;
  backward_t backward_fn;
  unsigned int dim[4];
} Tensor;

Tensor *create_tensor(TensorType type, bool requires_grad, unsigned int *dim);
Tensor *create_one_tensor(bool requires_grad);
Tensor *create_zero_tensor(bool requires_grad);
float32 sum(Tensor *tensor, const int dim);
float32 mean(Tensor *tensor, const int dim);
float32 item(Tensor *tensor);
unsigned int *create_dim(unsigned int x, unsigned int y, unsigned int z,
                         unsigned int w);