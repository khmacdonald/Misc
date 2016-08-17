#include <stdio.h>
#include <string.h>

#include "brand.h"
#include "print_macros.h"

int32_t brand_seed_init ( brand_t b )
{
    int32_t ret=0;
    FILE * rfd = fopen("/dev/urandom","r");
    uint32_t seed,rd;

    if ( NULL==rfd )
    {
        ret=1;
        goto END;
    }
    rd = fread(&seed,sizeof(seed),1,rfd);
    fclose(rfd);
    brand_init(b,seed);

END:
    return ret;
}

static void brand_rotate ( brand_t b )
{
    uint32_t t = b->w;

    t ^= t<<11;
    t ^= t>>8;
    b->x = b->y;
    b->y = b->z;
    b->z = b->w;
    b->w ^= (b->w>>19);
    b->w ^= t;
}

void brand_init( brand_t b, uint32_t seed )
{
    int32_t k;

    b->w = 2 ^ seed;
    b->x = 123456789;
    b->y = 362436069;
    b->z = 521288629;

    for ( k=0; k<128; ++k )
    {
        brand_rotate(b);
    }
}

uint32_t brand_next ( brand_t b )
{
    brand_rotate(b);

    return b->w;
}

float brand_next_float ( brand_t b )
{
    uint32_t next = brand_next(b);
    float ret = (float)next/(float)0xffffffff;

    return ret;
}

float brand_next_standard_normal ( brand_t b )
{
    float u1, u2,z;

    u1 = brand_next_float(b);
    u2 = brand_next_float(b);

    z = sqrt(-2.0*log(u1)) * cos(2*3.14159*u2);

    return z;
}

void brand_array ( uint32_t * arr, int32_t len, brand_t b )
{
    int32_t k;

    for ( k=0; k<len; ++k )
    {
        arr[k] = brand_next(b);
    }
}

void brand_byte_array ( uint8_t * arr, int32_t len, brand_t b )
{
    int32_t k;
    uint32_t r;

    for ( ; len>=sizeof(r); len -= sizeof(r) )
    {
        r = brand_next(b);
        memcpy(arr,&r,sizeof(r));
        arr += sizeof(r);
    }

    if ( len )
    {
        r = brand_next(b);
        memcpy(arr,&r,len);
    }
}


void print_array ( uint8_t * a, int32_t len )
{
    int32_t k;

    if ( len<1 )
    {
        goto END;
    }

    printf("%02x",a[0]);
    for ( k=1; k<len; ++k )
    {
        printf(" %02x",a[k]);
    }
END:
    return;
}



















