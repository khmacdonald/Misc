
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "primes.h"
#include "print_statements.h"

uint32_t rtrunk ( uint32_t x );
uint32_t ltrunk ( uint32_t x );

void p37 ( void );

void test01 ( int32_t argc, char * argv[] );

/* ---------------------------------------------------------------- */


int32_t main ( int32_t argc, char * argv[] )
{
    int32_t n;

    //test01(argc,argv);
    p37();

END:
    return 0;
}


/* ---------------------------------------------------------------- */

uint32_t rtrunk ( uint32_t x )
{
    return x/10;
}

uint32_t ltrunk ( uint32_t x )
{
    uint32_t y = 10;

    while ( y<x )
    {
        y *= 10;
    }
    y /= 10;

    return x % y;
}

void test01 ( int32_t argc, char * argv[] )
{
    uint32_t x = 3797,y,cnt=0,sum=0;

    if ( 2==argc )
    {
        x = strtol(argv[1],NULL,10);
    }
    
    info_print("    Left truncate:");
    y = x;
    while ( y )
    {
        info_print("%d",y);
        y = ltrunk(y);
    }
    
    info_print("    Right truncate:");
    y = x;
    while ( y )
    {
        info_print("%d",y);
        y = rtrunk(y);
    }

}

int32_t is_truncatable_prime ( uint32_t x )
{
    int32_t ret = 1;
    uint32_t y = x;

    while(x)
    {
        if ( !is_prime(x) )
        {
            ret = 0;
            goto END;
        }
        x = ltrunk(x);
    }
    x = y;
    while(x)
    {
        if ( !is_prime(x) )
        {
            ret = 0;
            goto END;
        }
        x = rtrunk(x);
    }

END:
    return ret;
}

void p37 ( void )
{
    uint32_t k,pr;
    int32_t cnt = 0;
    uint32_t sum = 0;

    for ( k=4; k<SMALL_PRIME_SZ; ++k )
    {
        pr = small_primes[k];
        if ( is_truncatable_prime(pr) )
        {
            cnt++;
            sum += pr;
            info_print("[%2d] %d",cnt,pr);
            if ( 11==cnt )
            {
                goto END;
            }
        }
    }

END:
    info_print("Sum = %d",sum);
    return;
}












