#include "backend/act.h"
#include <math.h>

void sigmoid(float *v, float *u, const unsigned int n) {
  for (unsigned int i = 0; i < n; i++) {
    u[i] = 1 / (1 + expf(-v[i]));
  }
}

void relu(float *v, float *u, const unsigned int n) {
  for (unsigned int i = 0; i < n; i++) {
    u[i] = v[i] > 0 ? v[i] : 0;
  }
}