#pragma once
#include "utils/list.h"

typedef TensorList *(*forward_function_t)(TensorList *);

typedef struct Module {
  TensorList *reg_params;
  forward_function_t forward;
} Module;