#pragma once
#include "tensor/tensor.h"

void sigmoid(const Tensor *input, const float32 lambda, const Tensor *output);
void softmax(const Tensor *input, const Tensor *output);
void relu(const Tensor *input, const Tensor *output);