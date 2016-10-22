#include <stdio.h>
#include <stdlib.h>

#include "print_statements.h"
#include "primes.h"


pr_t gcd ( pr_t a, pr_t b )
{
    pr_t c;
    
    /* Euclidean Algorithm */
    while ( b!=0 )
    {
        c = a % b;
        a = b;
        b = c;
    }

    return c;
}

pr_t int_sqrt ( pr_t n )
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

pr_t is_prime ( pr_t x )
{
    pr_t ret = 0;
    pr_t sq = 0, k, p;

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
