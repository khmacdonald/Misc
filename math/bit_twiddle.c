#include <stdint.h>
#include <stdio.h>

#include "bit_twiddle.h"

uint64_t bit_reverse ( uint64_t x, int32_t n )
{
    uint64_t mask, ret=0, bit = 1L,rnib;
    int32_t k;
    uint64_t rev_nibble[16] = { 0x00, 0x08, 0x04, 0x0c, 
                                0x02, 0x0a, 0x06, 0x0e,
                                0x01, 0x09, 0x05, 0x0d,
                                0x03, 0x0b, 0x07, 0x0f };
    uint64_t case_3[8] = { 0x00, 0x04, 0x02, 0x06,
                           0x01, 0x05, 0x03, 0x07 };
    uint64_t case_2[4] = { 0x00, 0x02, 0x01, 0x03 };

    if ( n>63 )
    {
        mask = 0-1;
    }
    else
    {
        mask = (1L<<n)-1;
    }

    /* Reverse a nibble at a time */
    while ( n>=4 )
    {
        rnib = rev_nibble[x&0x0f];
        ret = (ret<<4) | rnib;
        x = (x>>4);
        n -= 4;
    }
    switch(n)
    {
        case 1:
            ret = (ret<<1) | (x&1);
            break;
        case 2:
            ret = (ret<<2) | case_2[x&3];
            break;
        case 3:
            ret = (ret<<3) | case_3[x&7];
            break;
    }

    return ret;
}

uint64_t bit_count ( uint64_t x, int32_t n )
{
    uint64_t mask = (1L<<n)-1;
    uint64_t s1 = 0x5555555555555555L;
    uint64_t s2 = 0x3333333333333333L;
    uint64_t s3 = 0x0f0f0f0f0f0f0f0fL;
    uint64_t s4 = 0x00ff00ff00ff00ffL;
    uint64_t s5 = 0x0000ffff0000ffffL;
    uint64_t s6 = 0x00000000ffffffffL;

    x = x & mask;
    x = (x & s1) + ((x>>1)  & s1);
    x = (x & s2) + ((x>>2)  & s2);
    x = (x & s3) + ((x>>4)  & s3);
    x = (x & s4) + ((x>>8)  & s4);
    x = (x & s5) + ((x>>16) & s5);
    x = (x & s6) + ((x>>32) & s6);

    return x;
}

int32_t leading_zeros ( uint64_t x )
{
    uint64_t one=1L;
    int32_t zeros=0;

    if ( 0==x )
    {
        zeros = 64;
        goto END;
    }

    if ( x<((one<<32)-1) )
    {
        zeros += 32;
        x = (x<<32);
    }

    if ( x<((one<<48)-1) )
    {
        zeros += 16;
        x = (x<<16);
    }
    if ( x<((one<<56)-1) )
    {
        zeros += 8;
        x = (x<<8);
    }
    if ( x<((one<<60)-1) )
    {
        zeros += 4;
        x = (x<<4);
    }
    if ( x<((one<<62)-1) )
    {
        zeros += 2;
        x = (x<<2);
    }
    if ( x<((one<<63)-1) )
    {
        zeros += 1;
        x = (x<<1);
    }

END:
    return zeros;
}

int32_t leading_zeros_n ( uint64_t x, int32_t n )
{
    int32_t cnt = 0;
    uint64_t mask;

    if ( 0==n )
    {
        goto END;
    }
    if ( n>63 )
    {
        cnt = leading_zeros(x);
        goto END;
    }

    mask = (1L<<n) - 1;
    if ( 0==(x & mask) )
    {
        cnt = n;
        goto END;
    }

    x = (x<<(64-n));
    cnt = leading_zeros(x);

END:
    return cnt;
}

void print_bits ( uint64_t x, int32_t n )
{
    uint64_t mask;

    if ( n>63 )
    {
        mask = (1L<<63);
    }
    else
    {
        mask = (1L<<(n-1));
    }

    while ( mask )
    {
        if ( x&mask )
        {
            printf("X");
        }
        else
        {
            printf(".");
        }
        mask = (mask>>1);
    }

    return;
}

void print_hex ( uint64_t x )
{
    print_hex_2_file(stdout,x);
    return;
}

void print_hex_2_file ( FILE * fd, uint64_t x )
{
    char str[128];
    if ( fd )
    {
        memset(str,0,128);
        print_hex_2_str(str,128,x);
        fprintf(fd,"%s",str);
    }
    return;
}

int32_t print_hex_2_str ( char * str, int32_t slen, uint64_t x )
{
    int32_t sz;
    uint64_t hi,lo;

    lo = x & 0xffffffff;
    hi = (x>>32) & 0xffffffff;
    sz = snprintf(str,slen,"%08llx %08llx",hi,lo);

    return sz;
}
