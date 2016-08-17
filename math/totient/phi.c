#include <stdio.h>
#include <stdlib.h>

#include "print_statements.h"
#include "phi.h"

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

/* 
 * May not use.  For small numbers, it's
 * probably just easier to do look ups, 
 * but the factoring done may be just fine.
 */
uint32_t phi_small ( uint32_t x )
{
    uint32_t sum = 0;
    int32_t k;

    /* The most naive way to compute this */
    for ( k=2; k<x; ++k )
    {
        if ( 1==gcd(x,k) )
        {
            sum++;
        }
    }
    
    return sum;
}

uint32_t int_sqrt ( uint32_t n )
{
    int32_t idx = 1024;
    int32_t u=idx,l=0,tmp;
    int32_t ret = 1;
    
    if ( n>idx*idx )
    {
        /* Probably need to increase the size
           of the square array */
        err_print("Too high\n");
        exit(-1);
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

/*
 * if n = p**k, then phi(n) = (p-1)*p**(k-1)
 */
uint32_t phi_power_prime ( uint32_t p, uint32_t k )
{
    int32_t m,ret=1;

    for ( m=0; m<k-1; ++m )
    {
        ret *= p;
    }
    ret *= (p-1);

END:
    return ret;
}

/* 
 * Odd composite number recursive function
 */
uint32_t phi_comp_odd ( uint32_t n, int32_t idx )
{
    uint32_t sq,totnt=1;
    int32_t k,p,q,_p=0,m=n;

    /* Handle primes */
    if ( prime_array[n] )
    {
        totnt = n-1;
        goto END;
    }

    /* Start factoring */
    sq = int_sqrt(n); /* Consider primes less than the square root */
    if ( 1==prime_array[sq] && n==sq*sq )
    {
        totnt = sq*(sq-1);
        goto END;
    }
    
        /* TODO - rewrite this portion.  Don't like this */
    /*
     * idx = find_next_index ( n, idx );
     * k = get_power_of_prime_factor ( &m, n, idx ); /* Where n = m * p**k
     * totnt = phi_power_prime ( small_primes[idx], k );
     * totnt *= phi_comp_odd( m, idx+1 );
     */
    /* Check to see what primes divide n */
    for ( k=idx; small_primes[idx]<sq; ++idx )
    {
        p = small_primes[idx];
        if ( 0==(n%p) )
        {
            while ( 0==(n%p) ) /* Divide out p**k */
            {
                _p++;
                n = n/p;
            }
            totnt = phi_power_prime(p,_p); /* phi of a power of a prime is easy */
            if ( 1==n )
            {
                goto END;
            }
            else
            {
                totnt *= phi_comp_odd(n,idx+1); /* Recurse with the new odd composite */
                goto END;
            }
        }
    }

END:
    return totnt;
}

/*
 * Deals with any composite, including even
 */
uint32_t phi_composite ( uint32_t n )
{
    int32_t _2 = 1;
    uint32_t totnt = 1,tnt;
    uint32_t m = n;

    while ( 0==(n&1) )
    {
        _2  = (_2<<1); /* Divide out powers of 2 */
        n = (n>>1);
    }
    if ( _2>1 )
    {
        totnt = _2>>1; /* phi(2**k) = 2**(k-1) */
    }
    if ( 1==n )
    {
        goto END; /* If a power of 2, then done */
    }
    /* phi(mn) = phi(m)phi(n) when 1==gcd(m,n) */
    tnt = phi_comp_odd(n,0);
    totnt *= tnt;

END:
    return totnt;
}

uint32_t phi ( uint32_t n )
{
    uint32_t totnt = 0;
    uint32_t sq = 0;

    if ( 0==((n-1) & n) )
    {
        totnt = n>>1; /* Power 2's are easy to handle */
        goto END;
    }
    if ( n>=PRIME_SIZE )
    {
        /* TODO This can still be done with the
           current arrays.  The cleverness just
           needs to be discovered. */
        err_print("%u too large\n",n);
    }

    /* Indicates n is a prime */
    if ( prime_array[n] )
    {
        totnt = n-1;
        goto END;
    }

    totnt = phi_composite(n);

END:
    return totnt;
}










