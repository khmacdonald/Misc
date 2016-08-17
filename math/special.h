#ifndef SPECIAL_H
#define SPECIAL_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "print_statements.h"

#define N_ONES(N) ((1L<<(N))-1)

struct _double
{
    int64_t sgn;    /* Sign of the double */
    int64_t exp;    /* Exponent */
    uint64_t man;   /* Mantissa */
};

typedef struct _double    DOUBLE;
typedef struct _double * pDOUBLE;

/* 
 * Computes e**x
 */
double exponential ( double x );

/*
 * Compute the gamma function - incomplete
 */
double gamma ( double x );

/*
 */
uint32_t gcd ( uint32_t a, uint32_t b );

/* 
 * Computes base**exp for non-integral exponents
 * using the identity:
 *    x**y = exp(y*ln(x))
 */
double my_pow_f ( double base, double exp );

/* 
 * If x = e**y, then ln(x) = y
 */
double natural_log ( double x );

/*
 */
uint64_t n_ones ( int64_t n );

/* 
 * Breaks down a double into its sign, exponent, and 
 * mantissa parts.
 */
void process_double ( pDOUBLE dbl,  double x );

/* 
 */
double compute_double ( pDOUBLE dbl );

/*
 */
uint32_t totient ( uint32_t n );

#endif
