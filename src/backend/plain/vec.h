#pragma once

__attribute__((always_inline)) void add_fp32(float *v, float *u, float *r,
                                             unsigned int n);
__attribute__((always_inline)) float ipr_fp32(float *v, float *u,
                                              unsigned int n);