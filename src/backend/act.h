#pragma once

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((always_inline)) void sigmoid(float *v, float *u,
                                            const unsigned int n);
__attribute__((always_inline)) void relu(float *v, float *u,
                                         const unsigned int n);

#ifdef __cplusplus
}
#endif