#ifndef B_RAND_H
#define B_RAND_H

#include <math.h>
#include <stdint.h>

struct brand_ctx
{
    uint32_t w;
    uint32_t x;
    uint32_t y;
    uint32_t z;
};

typedef struct brand_ctx brand_t[1];

/*
 * Seeds and initializes a brand_t context data structure
 */
int32_t brand_seed_init ( brand_t b );

/*
 * Initializes a seeded brand_t context data structure
 */
void brand_init ( brand_t b, uint32_t seed );

/*
 * Get the next random 4 byte number
 */
uint32_t brand_next ( brand_t b );

/*
 * Returns a random floating point number
 */
float brand_next_float ( brand_t b );

/*
 */
float brand_next_standard_normal ( brand_t b );


/*
 */
void brand_array ( uint32_t * arr, int32_t len, brand_t b );

/*
 */
void brand_byte_array ( uint8_t * arr, int32_t len, brand_t b );


/*
 */
void print_array ( uint8_t * a, int32_t len );

#endif
