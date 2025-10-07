#pragma once

#include "utils/map.h"

void sigmoidBackward(TensorMap *map, TensorMap *backwardHook);
void siluBackward(TensorMap *map, TensorMap *backwardHook);
