#include "backend/plain/vec.h"

void add_fp32(float *v, float *u, float *r, unsigned int n) {
  for (unsigned int i = 0; i < n; i++)
    r[i] = v[i] + u[i];
}

float ipr_fp32(float *v, float *u, unsigned int n) {
  float r = 0;
  for (unsigned int i; i < n; i++) {
    r += v[i] * u[i];
  }
  return r;
}
