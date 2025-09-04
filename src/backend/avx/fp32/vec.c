#include "backend/avx/fp32/vec.h"
#include <immintrin.h>

#define CHECK_POW2(n) !(n) && (n) == 0

void add_fp32_avx(float *v, float *u, float *r, unsigned int n)
{

  if (!(CHECK_POW2(n)))
    exit(-1);
  for (unsigned int i = 0; i + 7 < n; i += 8)
  {
    __m256 vec_v = _mm256_loadu_ps(v + i);
    __m256 vec_u = _mm256_loadu_ps(u + i);
    __m256 vec_r = _mm256_add_ps(vec_v, vec_u);
    _mm256_storeu_ps(r + i, vec_r);
  }
}

float ipr_fp32_avx(float *v, float *u, unsigned int n)
{
  if (!(CHECK_POW2(n)))
    exit(-1);
  __m256 sum_vec = _mm256_setzero_ps();

  for (unsigned int i = 0; i + 7 < n; i += 8)
  {
    __m256 vec_v = _mm256_loadu_ps(v + i);
    __m256 vec_u = _mm256_loadu_ps(u + i);
    __m256 prod = _mm256_mul_ps(vec_v, vec_u);
    sum_vec = _mm256_add_ps(sum_vec, prod);
  }

  __m128 sum_high = _mm256_extractf128_ps(sum_vec, 1);
  __m128 sum_low = _mm256_castps256_ps128(sum_vec);
  __m128 sum_128 = _mm_add_ps(sum_high, sum_low);
  __m128 sum_64 = _mm_hadd_ps(sum_128, sum_128);
  __m128 sum_32 = _mm_hadd_ps(sum_64, sum_64);
  float sum = _mm_cvtss_f32(sum_32);
  return sum;
}