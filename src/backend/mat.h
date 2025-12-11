#pragma once

__attribute__((always_inline)) void matmul(float *input, float *weight,
                                           float *output, const unsigned int m,
                                           const unsigned int n,
                                           const unsigned int d);

__attribute__((always_inline)) void addmatvec(float *input, float *bias,
                                              float *output,
                                              const unsigned int m,
                                              unsigned int n);