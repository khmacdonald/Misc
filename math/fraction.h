#ifndef FRACTION_H
#define FRACTION_H

#include <stdio.h>
#include <stdint.h>

struct _fraction
{
    uint64_t num;
    uint64_t den;
};

typedef struct _fraction frac_t[1];

/*
 * c = a + b
 */
int32_t add_fraction ( frac_t c, frac_t a, frac_t b );

/*
 * c = a - b
 */
int32_t sub_fraction ( frac_t c, frac_t a, frac_t b );

/*
 */
uint64_t fgcd ( uint64_t a, uint32_t b );

/*
 */
uint64_t flcm( uint64_t * gcd, uint64_t a, uint32_t b );

/*
 */
void print_fraction ( frac_t f );

/*
 */
int32_t print_fraction_2_str  ( char * str, int32_t slen, frac_t f );

/*
 */
void print_fraction_2_file  ( FILE * fd,  frac_t f );


#endif
