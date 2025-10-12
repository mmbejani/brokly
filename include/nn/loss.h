#pragma once
#include "nn/module.h"

typedef struct MSE {
  Module module;
} MSE;

typedef struct CrossEntropyLoss {
  Module module;
} CrossEntropyLoss;