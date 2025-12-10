#include "backend/base.h"

void add_vec_inplace(float *v, float *u, const unsigned int n) {
  for (unsigned int i = 0; i < n; i++)
    u[i] += v[i];
}

__attribute__((always_inline)) void sub_vec_inplace(float *v, float *u,
                                                    const unsigned int n) {
  for (unsigned int i = 0; i < n; i++)
    u[i] -= v[i];
}
__attribute__((always_inline)) void pow_2_vec_inplace(float *v,
                                                      const unsigned int n) {
  for (unsigned int i = 0; i < n; i++)
    v[i] *= v[i];
}

float sum_reduce_vec(float *v, const unsigned int n) {
  float r = 0;
  for (unsigned int i = 0; i < n; i++) {
    r += v[i];
  }
  return r;
}

float inner_prod_reduce_vec(float *v, float *u, const unsigned int n) {
  float r = 0;
  for (unsigned int i; i < n; i++) {
    r += v[i] * u[i];
  }
  return r;
}
