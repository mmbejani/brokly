#pragma once

#ifdef __cplusplus
extern "C" {
#endif

extern
    __attribute__((always_inline))
    /**
     * @brief add two vectors `v` and `u` of size `n` and store it on `w`
     *
     * @param v first vector
     * @param u second vector
     * @param w storage memory
     * @param n size of vector
     */
    void
    add_vec(float *v, float *u, float *w, const unsigned int n);

extern
    __attribute__((always_inline))
    /**
     * @brief add two vectors `v` and `u` of size `n` and store the result on
     * `u`
     *
     * @param v first vector
     * @param u second vector
     * @param n size of the vector
     */
    void
    add_vec_inplace(float *v, float *u, const unsigned int n);

extern
    __attribute__((always_inline))
    /**
     * @brief subtract two vectors `v` and `u` of size `n` and store the result
     * on `u`
     *
     * @param v first vector
     * @param u second vector
     * @param n size of the vector
     */
    void
    sub_vec_inplace(float *v, float *u, const unsigned int n);

extern
    __attribute__((always_inline))
    /**
     * @brief compute power of 2 vector `v` and store the result on `v`
     *
     * @param v the input vector
     * @param n size of the vector
     */
    void
    pow_2_vec_inplace(float *v, const unsigned int n);

extern
    __attribute__((always_inline))
    /**
     * @brief sum up the elements of vector `v` of size `n`
     *
     * @param v the input vector
     * @param n size of the vector
     * @return float
     */
    float
    sum_reduce_vec(float *v, const unsigned int n);

extern
    __attribute__((always_inline))
    /**
     * @brief compute inner product of two vectors `v` and `u` of size `n`
     *
     * @param v fisrt input vector
     * @param u second input vector
     * @param n size of both input vectors
     * @return float
     */
    float
    inner_prod_reduce_vec(float *v, float *u, const unsigned int n);

extern
    __attribute__((always_inline))
    /**
     * @brief assign a single `float` variable to all elements of vector `v` of
     * size `n`
     *
     * @param v input vector
     * @param x the target variable
     * @param n size of the vector
     */
    void
    assign_value(float *v, const float x, const unsigned int n);

#ifdef __cplusplus
}
#endif
