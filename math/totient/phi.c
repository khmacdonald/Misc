#include <stdio.h>
#include <stdlib.h>

#include "print_statements.h"
#include "phi.h"

uint32_t gcd ( uint32_t a, uint32_t b )
{
    uint32_t c;
    
    while ( b!=0 )
    {
        c = a % b;
        a = b;
        b = c;
    }

    return c;
}

uint32_t phi_small ( uint32_t x )
{
    uint32_t sum = 0;
    int32_t k;

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
        err_print("Too high\n");
        exit(-1);
    }

    while ( l<u )
    {
        tmp = (u+l)/2;
        if ( n==square_int[tmp] )
        {
            ret = tmp;
            goto END;
        }
        if ( n>square_int[tmp] )
        {
            l = tmp;
        }
        else
        {
            u = tmp;
        }
        if ( 1==(u-l) )
        {
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
    }

END:
    return ret;
}

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

uint32_t phi_comp_odd ( uint32_t n, int32_t idx )
{
    uint32_t sq,totnt=1;
    int32_t k,p,q,_p=0,m=n;

    if ( prime_array[n] )
    {
        totnt = n-1;
        goto END;
    }

    /* Start factoring */
    sq = int_sqrt(n);
    if ( 1==prime_array[sq] && n==sq*sq )
    {
        totnt = sq*(sq-1);
        goto END;
    }
    for ( k=idx; small_primes[idx]<sq; ++idx )
    {
        p = small_primes[idx];
        if ( 0==(n%p) )
        {
            while ( 0==(n%p) )
            {
                _p++;
                n = n/p;
            }
            totnt = phi_power_prime(p,_p);
            if ( 1==n )
            {
                goto END;
            }
            else
            {
                totnt *= phi_comp_odd(n,idx+1);
                goto END;
            }
        }
    }

END:
    return totnt;
}

uint32_t phi_composite ( uint32_t n )
{
    int32_t _2 = 1;
    uint32_t totnt = 1,tnt;
    uint32_t m = n;

    while ( 0==(n&1) )
    {
        _2  = (_2<<1);
        n = (n>>1);
    }
    if ( _2>1 )
    {
        totnt = _2>>1; /* divide by 2 */
    }
    if ( 1==n )
    {
        goto END;
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
        totnt = n>>1;
        goto END;
    }
    if ( n>=PRIME_SIZE )
    {
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










