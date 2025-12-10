#include "backend/mat.h"

void matmul(float *input, float *weight, float *output, const unsigned int m,
            const unsigned int n, const unsigned int d) {
  for (unsigned int i = 0; i < m; i++) {
    for (unsigned int j = 0; j < n; j++) {
      for (unsigned int k = 0; k < d; k++) {
        output[i * m + j] += input[i * d + k] * weight[j * d + k];
      }
    }
  }
}

void addmatvec(float *input, float *bias, float *output, const unsigned int m,
               unsigned int n) {
  for (unsigned int i = 0; i < m; i++) {
    for (unsigned int j = 0; j < n; j++) {
      output[i * n + j] = input[i * n + j] + bias[j];
    }
  }
}