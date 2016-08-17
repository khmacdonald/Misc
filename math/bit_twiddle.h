#ifndef BIT_TWIDDLE_H
#define BIT_TWIDDLE_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*
 * Reverses the low n bits in x.  If n is greater
 * than 63, reverse all bits.
 */
uint64_t bit_reverse ( uint64_t x, int32_t n );

/*
 * Counts the number of ones in the low n bits
 * in x.
 */
uint64_t bit_count ( uint64_t x, int32_t n );

/*
 * Counts the number of leading zeros in a 64 bit number
 */
int32_t leading_zeros ( uint64_t x );

/*
 * Counts the number of leading zeros in the first n
 * bits in a 64 bit number.
 */
int32_t leading_zeros_n ( uint64_t x, int32_t n );

/*
 * Prints the low n bits in x.
 */
void print_bits ( uint64_t x, int32_t n );

/*
 * Prints x in hex, with a space separating the
 * hi 32 bits from the low 32 bits.
 */
void print_hex ( uint64_t x );

/*
 * Writes x in hex, with a space separating the
 * hi 32 bits from the low 32 bits, to a file.
 */
void print_hex_2_file ( FILE * fd, uint64_t x );

/*
 * Writes x in hex, with a space separating the
 * hi 32 bits from the low 32 bits, to a string.
 */
int32_t print_hex_2_str ( char * str, int32_t slen, uint64_t x );

#endif
