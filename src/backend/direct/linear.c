#include "backend/linear.h"

float linear_vec(float *vec_input, float *vec_weight, float b,
                 const unsigned int n) {
  float r = b;
  for (int i = 0; i < n; i++) {
    r += vec_input[i] * vec_weight[i];
  }

  return r;
}