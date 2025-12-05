#pragma once

#include "tensor/define.h"

/**
 * @brief compute linear module on single batch data
 *
 *  @param vec_input it is a `float32` array that indicate to single batch with
 * `n` features
 *  @param vec_weight is a `float32` array that indicate to single row of the
 * weight array
 *  @param b is a single `float32` scalar as the corresponding to bias the
 * feature
 *   @param n number of features
 */
__attribute__((always_inline)) float32 linear_vec(float32 *vec_input,
                                                  float32 *vec_weight,
                                                  float32 b, const int n);