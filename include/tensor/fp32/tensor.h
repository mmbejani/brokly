#pragma once
#include "tensor/define.h"

typedef struct Tensor
{
    char requires_grad;
    unsigned int forward_hooks_count;
    float32 *data;
    unsigned int dim[4];
} Tensor;