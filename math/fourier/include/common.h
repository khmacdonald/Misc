#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define SET_FREE(X) if ( X ) { free(X); (X) = NULL; };

/* Error types */
typedef enum {
    c_success=0,      /* Success */
    c_failure,        /* Generic Failure */
    c_badargs,        /* Invalid Arguments */
    c_nomemory,       /* Memory Allocation Failure */
    c_null,           /* Cannot dereference a NULL pointer */

                /*** MUST ADD NEW ERROR CODES BEFORE c_end ***/

    c_end             /* If adding to this list, make sure this is the last one */
} c_error_t;

/* Size indication types size in bits */
typedef enum { _sz8, _sz16, _sz32, _sz64 } sz_t;

/**
 * @brief Gets human readable string for an error.
 *
 * @param err[in] - the error message to check
 * 
 * @return pointer to a character string
 */
char * c_err_msg ( c_error_t err );

/**
 * @brief Gets a random array
 *
 * @param arr[in,out] - the array to be filled with random bytes
 * @param len[in] - the length of the array 
 *
 * @return c_success - upon success
 * @return c_null - the pointer to arr is NULL
 * @return c_badargs - the length is invalid
 */
c_error_t c_get_random_array( uint8_t * arr, int32_t len );

/**
 * @brief print hexdump of a binary array to a string
 *
 * @param str[in,out] - the string to hold the hexdump
 * @param slen[in] - the max length of the character string
 * @param arr[in] - the array to be printed out
 * @param alen[in] - the length of the binary array
 */
void c_print_arr_2_str ( char * str, int32_t slen, uint8_t * arr, int32_t alen );

/**
 * @brief print the bits of x as a string in str
 *
 * @param str[in,out] - the string to hold the hexdump
 * @param slen[in] - the max length of the character string
 * @param x[in] - the element from which to print the bits
 * @param sz[in] - the size of x
 */
void c_print_int_bin_2_str ( char * str, int32_t slen, uint32_t x, sz_t sz );

#endif





















