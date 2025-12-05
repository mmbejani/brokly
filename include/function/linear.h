#pragma once

#include "nn/linear.h"
#include "tensor/tensor.h"

void linear_forward(Linear* linear_module, Tensor* input, Tensor* output);
void linear_fused_forward(Linear* linear_module, Tensor* input, Tensor* output);