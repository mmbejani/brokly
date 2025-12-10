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
__attribute__((always_inline)) void matmul(float *input, float *weight,
                                           float *output, const unsigned int m,
                                           const unsigned int n,
                                           const unsigned int d);

__attribute__((always_inline)) void addmatvec(float *input, float *bias,
                                              float *output,
                                              const unsigned int m,
                                              unsigned int n);