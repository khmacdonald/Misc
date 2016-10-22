#ifndef PRIMES_H
#define PRIMES_H

#include <stdint.h>
#include <stdio.h>

#define SQUARE_SZ 262143
#define PRIME_SIZE 1048576
#define SMALL_PRIME_SZ 82025 

typedef uint64_t pr_t;

/*
 * Boolean array declaring a number prime or not
 */
//int32_t prime_array[PRIME_SIZE];
uint8_t prime_array[PRIME_SIZE];

/*
 * An array of the squares of integers
 */
pr_t square_int[SQUARE_SZ];

/*
 * A list of small primes.  This can be used 
 * quickly determine if a number greater than 
 * 1048576, but less than 1048576**2.
 */
pr_t small_primes[SMALL_PRIME_SZ];

/*
 * Computes the integer part of the 
 * square root of n.  This can easily
 * be extended to much larger numbers.
 */
pr_t int_sqrt ( pr_t n );

/*
 * Computes the greatest common divisor
 * of a and b.
 */
pr_t gcd ( pr_t a, pr_t b );

/*
 * Computes is x is a prime number
 */
pr_t is_prime ( pr_t x );

#endif
