#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "primes.h"
#include "print_statements.h"

void proj ( void );

void test ( int32_t argc, char * argv[] );

/* ---------------------------------------------------------------- */

int32_t main ( int32_t argc, char * argv[] )
{
    proj();
    //test(argc,argv);

    return 0;
}

/* ---------------------------------------------------------------- */
void test ( int32_t argc, char * argv[] )
{
    return;
}
/* ---------------------------------------------------------------- */

int32_t is_cube_prime ( pr_t p )
{
    pr_t n,nmx,np;
    double root;
    int32_t ret = 0;

    nmx = 100000;
    for ( n=1; n<nmx; ++n )
    {
        np = n*n*(n+p);
        root = cbrt((double)np);
        if ( (root-(int)root)==0 )
        {
            //printf("[%d] p = %llu, n = %llu -> np = %llu\n",__LINE__,p,n,np);
            ret = 1;
            break;
        }
    }

    return ret;
}


void proj ( void )
{
    pr_t k,p,kmx,pmx;
    int32_t cnt=0;

    kmx = 100000000;
    p = 1;
    pmx = 1200000;
    for ( k=0; k<kmx && p<pmx && k<SMALL_PRIME_SZ; ++k )
    {
        p = small_primes[k];
        if ( is_cube_prime(p) )
        {
            cnt++;
        }
        printf("[%d] k = %llu, cnt = %d\r",__LINE__,k,cnt);
    }

    printf("\n[%d] Total is %d\n",__LINE__,cnt);

    return;
}

















