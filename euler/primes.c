#include <stdio.h>
#include <stdlib.h>

#include "print_statements.h"
#include "primes.h"


uint32_t gcd ( uint32_t a, uint32_t b )
{
    uint32_t c;
    
    /* Euclidean Algorithm */
    while ( b!=0 )
    {
        c = a % b;
        a = b;
        b = c;
    }

    return c;
}

uint32_t lg_int_sqrt ( uint32_t x )
{
    int32_t lz = __builtin_clz(x);
    int32_t sq, sq2;
    int32_t loc = 0, interval = (32-lz)/2;

    sq = (1<<interval);
    sq2 = sq*sq;
    printf("%d -> %d, %d\n",x,sq,sq2);
    printf("%08x -> %08x, %08x\n",x,sq,sq2);

    return sq;
}

uint32_t int_sqrt ( uint32_t n )
{
    int32_t idx = SQUARE_SZ;
    int32_t u=idx,l=0,tmp;
    int32_t ret = 1;
    
    if ( n>idx*idx )
    {
        ret = SQUARE_SZ;
        goto END;
    }

    /*
     * We have a table of squares that is searched
     * to find the floor of the root.
     */
    while ( l<u )
    {
        /* Do a binary search in an array of squares */
        tmp = (u+l)/2;
        if ( n==square_int[tmp] )
        {
            ret = tmp;
            goto END;
        }
        if ( n>square_int[tmp] )
        {
            /* Adjust the lower limit if the
               number is greater than the average */
            l = tmp; 
        }
        else
        {
            /* Adjust the upper limit if the
               number is less than the average */
            u = tmp;
        }
        if ( 1==(u-l) )
        {
            /* A difference of one means we're done, so just
               have to figure out which one it is */
            if ( square_int[l]<=n && square_int[u]>n )
            {
                ret = l;
                goto END;
            }
            else 
            {
                ret = u;
                goto END;
            }
        }
    } /* while */

END:
    return ret;
}

uint32_t is_prime ( uint32_t x )
{
    uint32_t ret = 0;
    uint32_t sq = 0, k, p;

    if ( x<PRIME_SIZE )
    {
        ret = prime_array[x];
        goto END;
    }

    /* Assume prime, then set to 0 if composite */
    ret = 1;
    sq = int_sqrt(x);
    for ( k=0; k<SMALL_PRIME_SZ; ++k )
    {
        p = small_primes[k];
        if ( 0==(x%p) )
        {
            ret = 0;
            goto END;
        }
        if ( p>sq )
        {
            goto END;
        }
    }

END:
    return ret;
}
