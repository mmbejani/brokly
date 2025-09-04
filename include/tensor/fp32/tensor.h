#pragma once
#include "tensor/define.h"

typedef struct
{
    unsigned int dim[4];
    float32 *data;
    unsigned int forward_hooks_count;
    bool requires_grad;
    

} tensor;