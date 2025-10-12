#pragma once
#include "nn/module.h"
#include "tensor/tensor.h"

typedef struct Linear {
  Module module;
  Tensor *weight, *bias;
} Linear;

typedef struct LinearReLU {
  Module module;
  Tensor *weight, *bias;
} LinearReLU;


