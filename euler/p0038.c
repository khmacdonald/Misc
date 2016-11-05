#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "primes.h"

int32_t     is_pan ( int64_t n );
void        permute ( char * c, int32_t l, int32_t r );
int64_t     str2ll ( char * c, int32_t l );

void test ( int32_t argc, char * argv[] );

/* ---------------------------------------------------------------- */

int32_t main ( int32_t argc, char * argv[] )
{
    test(argc,argv);
    return 0;
}

/* ---------------------------------------------------------------- */
void test ( int32_t argc, char * argv[] )
{
    int64_t x = 123456;

    if ( 2==argc )
    {
        x = str2ll(argv[1],strlen(argv[1]));
    }

    if ( is_pan(x) )
    {
        printf("[%d] %llu is pandigital\n",__LINE__,x);
    }
    else
    {
        printf("[%d] %llu is not pandigital\n",__LINE__,x);
    }

    return;
}
/* ---------------------------------------------------------------- */

int32_t is_pan ( int64_t n )
{
    int32_t ret = 1;
    int64_t d,dig[10] = {1,1,1,1, 1,1,1, 1,1,1};

    while(n)
    {
        d = n % 10;
        if ( 0==dig[d] )
        {
            ret = 0;
            goto END;
        }
        dig[d] = 0;
        n = n /  10;
    }

END:
    return ret;
}

void permute ( char * c, int32_t l, int32_t r )
{
    int32_t k;
    char tmp;

    for ( k=l; k<l; ++k )
    {
        tmp = c[l];
        c[l] = c[k];
        c[k] = tmp;
        permute(c,l+1,r);
        tmp = c[l];
        c[l] = c[k];
        c[k] = tmp;
    }

    return;
}

int64_t str2ll ( char * c, int32_t l )
{
    int32_t sum = 0, k;
    int32_t ch;

    for ( k=0; k<l; ++k )
    {
        if ( c[k]<'0' || c[k]>('0'+10) )
        {
            printf("[%d] ERROR: %c not a valid digit\n",__LINE__,c[k]);
            exit(-1);
        }
        ch = c[k] - '0';
        sum = sum * 10 + ch;
    }

    return sum;
}















