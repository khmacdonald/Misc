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
 * Copy contents of b into a.
 */
void complex_copy ( complex_t a, complex_t b );

/*
 * Print the complex number into file ofd.
 */
void complex_print_file ( FILE * ofd, complex_t a );
void complex_print_label_file ( FILE * ofd, complex_t a, char * lbl, int nline );

/*
 * Print the complex number to the screen.
 */
void complex_print ( complex_t a );
void complex_print_label ( complex_t a, char * lbl, int nline );

/*
 * Negate complex number of a and put it into n.
 */
void complex_neg ( complex_t n, complex_t a );

/*
 * Put complex conjugate a into c.
 */
void complex_conj ( complex_t c, complex_t a );

/*
 * Put complex inverse a into c.
 */
khm_error_t complex_inv ( complex_t c, complex_t a );

/*
 * Return the modulus squared of a.
 */
double complex_abs_sq ( complex_t a );

/*
 * Return the modulus of a.
 */
double complex_abs( complex_t a );

/*
 * Add a and b and place sum in to sum.
 */
khm_error_t complex_add ( complex_t sum, complex_t a, complex_t b );

/*
 * Multiply a and b and place product into mul.
 */
khm_error_t complex_mul ( complex_t mul, complex_t a, complex_t b );

/*
 * Divide a and b and place result into mul, d = a / b.
 */
khm_error_t complex_div ( complex_t d, complex_t a, complex_t b );

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

/*          UNIT TEST       */
void unit_test_complex_print ( int32_t argc, char * argv[] ) ;
void unit_test_complex_copy ( int32_t argc, char * argv[] ) ;
void unit_test_complex_negate ( int32_t argc, char * argv[] ) ;
void unit_test_complex_conjugate ( int32_t argc, char * argv[] ) ;
void unit_test_complex_inverse ( int32_t argc, char * argv[] ) ;
void unit_test_complex_modulus ( int32_t argc, char * argv[] ) ;


#endif
