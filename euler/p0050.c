#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "primes.h"

void sum_primes ( void );

void test ( int32_t argc, char * argv[] );

/* ---------------------------------------------------------------- */

int32_t main ( int32_t argc, char * argv[] )
{
    sum_primes();
    return 0;
}

/* ---------------------------------------------------------------- */
void test ( int32_t argc, char * argv[] )
{
    return;
}
/* ---------------------------------------------------------------- */

void sum_primes ( void )
{
    int64_t sum = 0;
    int64_t mx = 2;
    int32_t k;
    int64_t lim = 100;
    pr_t pr;

    for ( k=0; k<SMALL_PRIME_SZ; ++k )
    {
        pr = small_primes[k];
        sum += pr;
        if ( sum>lim )
        {
            printf("\nLess than %llu is %llu\n",lim,mx);
            lim *= 10;
        }

        if ( sum>1000000 )
        {
            break;
        }
        if ( prime_array[sum] )
        {
            mx = sum;
        }
    }

    printf("\n");
    printf("sum = %llu\n",sum);
    printf("max = %llu\n",mx);
    printf("k   = %d\n",k);
}













