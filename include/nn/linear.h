#pragma once
#include "tensor/tensor.h"

typedef struct Linear {
  Tensor *weight, *bias;
} Linear;

typedef struct LinearReLU {
  Tensor *weight, *bias;
} LinearReLU;

typedef struct LinearReLUBatchNorm {
  Tensor *weight, *bias;
} LinearReLUBatchNorm;
