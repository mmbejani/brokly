#pragma once

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
__attribute__((always_inline)) float
linear_vec(float *vec_input, float *vec_weight, float b, const unsigned int n);