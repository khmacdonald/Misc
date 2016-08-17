#ifndef FOURIER_H
#define FOURIER_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "print_statements.h"

typedef double fr_t;

struct _fourier
{
    fr_t x;
    fr_t y;
};

typedef struct _fourier fourier_t[1];

/*
 * Given a signal x, compute the N DFT coefficients X[k]
 * This is not an optimized Fourier transform, performing
 * all n**2 multiplications and sums.
 *
 * X[in,out] - the computed Fourier coefficients.  If non-NULL 
 *             assumed to be of length at least n
 * x[in] - the signal to be transformed
 * n[in] - the length of the signal
 */
c_error_t basic_dft ( fourier_t * X, fourier_t * x, int32_t n );

/*
 * Add two complex numbers such that s = a+b
 *
 * s[in,out] - resultant sum
 * a[in] - summand
 * b[in] - summand
 */
void complex_add ( fourier_t s, fourier_t a, fourier_t b );

/*
 * Multiply two complex numbers  m = a*b
 *
 * m[in,out] - the resultant product
 * a[in] - multiplicand
 * b[in] - multiplicand
 */
void complex_multiply ( fourier_t m, fourier_t a, fourier_t b );

/*
 */
void copy_fourier ( fourier_t a, fourier_t b );

/*
 */
int32_t get_unity_index ( int32_t k, int32_t n, int32_t N );

/*
 * Set a complex number with with real part re and 
 * complex part co.
 */
void set_fourier ( fourier_t f, fr_t re, fr_t co );

/*
 */
c_error_t set_fourier_index_n_N ( int32_t * index, int32_t n, int32_t N );

/*
 * Sets a complex number to the nth root of unity.
 */
void unity_n ( fourier_t f, int32_t n );

/*
 *
 */
c_error_t unity_n_array ( fourier_t * f, int32_t n );

/*
 */
void zero_fourier ( fourier_t f );

#endif
