#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "khm_common.h"

#define base_complex_print(F,L,C) \
    do { \
        fprintf( F, "%s - [%s,%s,%d]: ",L,__FILE__,__FUNCTION__,__LINE__); \
        complex_print_file(F,C);\
        fprintf( F, "\n" ); \
    } while ( 0 )

#define dbg_complex_print(C) base_complex_print(stderr,"DEBUG",C)


/* Data structure defining a complex number */
struct complex_double
{
    double x; /* The real part */
    double y; /* The complex part */
};

typedef struct complex_double complex_t[1];

/*
 * Initialize a complex number
 *
 * a[in,out] - the complex number to be initialized
 * x[in] - the real part to be initialized
 * y[in] - the complex part to be initialized
 */
void complex_init ( complex_t a, double x, double y );

/*
 */
void complex_copy ( complex_t a, complex_t b );

/*
 */
void complex_print_file ( FILE * ofd, complex_t a );

/*
 */
void complex_print ( complex_t a );

/*
 */
void complex_neg ( complex_t n, complex_t a );

/*
 */
void complex_conj ( complex_t c, complex_t a );

/*
 */
double complex_abs_sq ( complex_t a );

/*
 */
double complex_abs( complex_t a );

/*
 */
khm_error_t complex_add ( complex_t sum, complex_t a, complex_t b );

/*
 */
khm_error_t complex_mul ( complex_t mul, complex_t a, complex_t b );

/*
 * The partial sum of the first n summands for exp(z) 
 *
 * exp[in,out] - the resultant 
 * z[in] - the complex number to raise e to
 * n[in] - the first n elements in the partial sum
 */
khm_error_t complex_exp ( complex_t ex, complex_t z, int32_t n );

struct gauss_integer
{
    uint64_t x;
    uint64_t y;
};

typedef struct gauss_integer gauss_t[1];

#endif