#include "backend/plain/linear_vec.h"

__attribute__((always_inline)) float32 linear_vec(float32 *vec_input,
                                                  float32 *vec_weight,
                                                  float32 b, const int n) {
  float32 r = b;
#ifdef AVX
#else
  for (int i = 0; i < n; i++) {
    r += vec_input[i] * vec_weight[i];
  }

  return r;
#endif
}