#pragma once

__attribute__((always_inline)) void add_vec_inplace(float *v, float *u,
                                                    const unsigned int n);
__attribute__((always_inline)) void sub_vec_inplace(float *v, float *u,
                                                    const unsigned int n);
__attribute__((always_inline)) void pow_2_vec_inplace(float *v,
                                                      const unsigned int n);
__attribute__((always_inline)) float sum_reduce_vec(float *v,
                                                    const unsigned int n);

__attribute__((always_inline)) float
inner_prod_reduce_vec(float *v, float *u, const unsigned int n);