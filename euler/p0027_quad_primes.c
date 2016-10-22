#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "primes.h"

void test_01 ( int32_t argc, char * argv[] );
void test_02 ( int32_t argc, char * argv[] );

void proj27 ( int32_t argc, char * argv[] );

/* ---------------------------------------------------------------- */


int32_t main ( int32_t argc, char * argv[] )
{

    proj27(argc,argv);

END:
    return 0;
}


/* ---------------------------------------------------------------- */

void test_01 ( int32_t argc, char * argv[] )
{
    uint32_t n,x,lz;

    if ( 2!=argc )
    {
        printf("USAGE: %s <integer>\n",argv[0]);
        printf("    Determines if inputted number is prime or not\n");
        goto END;
    }

    n = strtol(argv[1],NULL,10);
    x = is_prime(n);
    printf("%d is ",n);
    if ( x )
        printf("prime\n");
    else
        printf("not prime\n");


END:
    return;
}

void test_02 ( int32_t argc, char * argv[] )
{
END:
    return;
}

void proj27 ( int32_t argc, char * argv[] )
{
    int32_t n,a,b,pidx,y;
    int32_t mxa,mxb,mxcnt=0,pcnt=0;
    int32_t amin = -999, amax = 1000, nmax = 1000; 
    /* int32_t amin = 1, amax = 4, nmax = 100; */

    for ( pidx = 0; pidx<SMALL_PRIME_SZ; ++pidx ) 
    /* for ( pidx = 0; pidx<24; ++pidx ) */
    {
        b = small_primes[pidx];
        if ( b>1000 )
        {
            goto END;
        }

        for ( a = amin; a<amax; a++ )
        {
            pcnt = 0;
            for ( n=0; n<nmax; ++n )
            {
                y = n*(n+a) + b;
                if ( is_prime(y) )
                {
                    pcnt++;
                }
                else
                {
                    goto COUNT;
                }
            } /* for ( n=0; n<1000; ++n ) */
COUNT:
            if ( pcnt>mxcnt )
            {
                mxcnt = pcnt;
                mxa = a;
                mxb = b;
            }
        } /* for ( a = amin; a<amax; a++ ) */
    } /* for ( pidx = 0; pidx<SMALL_PRIME_SZ; ++pidx ) */
END:
    printf("a = %d, b = %d\n",mxa,mxb);
    printf("Prime string = %d\n",mxcnt);
}











