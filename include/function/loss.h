#pragma once

#include "tensor/tensor.h"

void mean_squard_error_loss_forward(Tensor *input, Tensor *target);
void cross_entropy_loss_forward(Tensor *input, Tensor *target);