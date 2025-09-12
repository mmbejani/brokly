#pragma once

#include "tensor/define.h"
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

struct Tensor;

typedef void (*backward_t)(struct Tensor *);

typedef struct __attribute__((aligned(64))) Tensor {
  bool requires_grad;
  TensorType type;
  unsigned int forward_hooks_count;
  unsigned int size;
  float32 *data;
  unsigned int dim[4];
  backward_t backward;
} Tensor;

Tensor *create_tensor(TensorType type, bool requires_grad);
Tensor *create_one_tensor(bool requires_grad);
Tensor *create_zero_tensor(bool requires_grad);
float32 sum(Tensor *tensor, const int dim);
float32 mean(Tensor *tensor, const int dim);
float32 item(Tensor *tensor);