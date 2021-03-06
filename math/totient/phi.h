#ifndef TOTIENT_FUNCTION_H
#define TOTIENT_FUNCTION_H

#include <stdint.h>
#include <stdio.h>

#define SQUARE_SZ 1025 /* This can be increased to 65000 */
#define PRIME_SIZE 1048576
#define SMALL_PRIME_SZ 82025 

/*
 * Boolean array declaring a number prime or not
 */
//int32_t prime_array[PRIME_SIZE];
uint8_t prime_array[PRIME_SIZE];

/*
 * An array of the squares of integers
 */
uint32_t square_int[SQUARE_SZ];

/*
 * A list of small primes.  This can be used 
 * quickly determine if a number greater than 
 * 1048576, but less than 1048576**2.
 */
uint32_t small_primes[SMALL_PRIME_SZ];

/*
 * Computes the integer part of the 
 * square root of n.  This can easily
 * be extended to much larger numbers.
 */
uint32_t int_sqrt ( uint32_t n );

/*
 * Computes the greatest common divisor
 * of a and b.
 */
uint32_t gcd ( uint32_t a, uint32_t b );

/*
 * Computes the number of numbers less than n
 * that are relatively prime to n.
 */
uint32_t phi ( uint32_t n );

#endif
