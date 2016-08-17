#ifndef _KHM_COMMON_H
#define _KHM_COMMON_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define base_print(F,L,...) \
    do { \
        fprintf( F, "%s - [%s,%s,%d]: ",L,__FILE__,__FUNCTION__,__LINE__); \
        fprintf( F, __VA_ARGS__ ); \
        fprintf( F, "\n" ); \
    } while ( 0 )

#define info_print(...) base_print(stdout,"INFO",__VA_ARGS__)
#define err_print(...) base_print(stdout,"ERROR",__VA_ARGS__)
#define dbg_print(...) base_print(stdout,"DEBUG",__VA_ARGS__)

/* Error types */
typedef enum {
    khm_success=0,      /* Success */
    khm_failure,        /* Generic Failure */
    khm_badargs,        /* Invalid Arguments */
    khm_nomemory,       /* Memory Allocation Failure */
    khm_null,           /* Cannot dereference a NULL pointer */

                /*** MUST ADD NEW ERROR CODES BEFORE khm_end ***/

    khm_end             /* If adding to this list, make sure this is the last one */
} khm_error_t;

/* Size indication types size in bits */
typedef enum { _sz8, _sz16, _sz32, _sz64 } sz_t;

/**
 * @brief Gets human readable string for an error.
 *
 * @param err[in] - the error message to check
 * 
 * @return pointer to a character string
 */
char * khm_err_msg ( khm_error_t err );

/**
 * @brief Gets a random array
 *
 * @param arr[in,out] - the array to be filled with random bytes
 * @param len[in] - the length of the array 
 *
 * @return khm_success - upon success
 * @return khm_null - the pointer to arr is NULL
 * @return khm_badargs - the length is invalid
 */
khm_error_t get_random_array( uint8_t * arr, int32_t len );

/**
 * @brief print hexdump of a binary array to a string
 *
 * @param str[in,out] - the string to hold the hexdump
 * @param slen[in] - the max length of the character string
 * @param arr[in] - the array to be printed out
 * @param alen[in] - the length of the binary array
 */
void khm_print_arr_2_str ( char * str, int32_t slen, uint8_t * arr, int32_t alen );

/**
 * @brief print the bits of x as a string in str
 *
 * @param str[in,out] - the string to hold the hexdump
 * @param slen[in] - the max length of the character string
 * @param x[in] - the element from which to print the bits
 * @param sz[in] - the size of x
 */
void khm_print_int_bin_2_str ( char * str, int32_t slen, uint32_t x, sz_t sz );

#endif





















