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
    int64_t mx = 2, mx_len=0,mn_len=0;;
    int32_t k, m, mmax, kmax,mmx,kmx;
    int64_t lim = 100;
    pr_t pr;
    FILE * fd = fopen("p0050_out.txt","w");

    printf("[%d] Starting\n",__LINE__);
#if 1
    mmax = SMALL_PRIME_SZ-1;
    kmax = SMALL_PRIME_SZ;
#else
    mmax = 1;
    kmax = SMALL_PRIME_SZ;
#endif
    for ( m=0; m<mmax; ++m )
    {
        sum = 0;
        lim = 100;
        for ( k=m; k<kmax; ++k )
        {
            pr = small_primes[k];
            sum += pr;
#if 0
            if ( sum>lim )
            {
                printf("\nLess than %llu is %llu\n",lim,mx);
                lim *= 10;
            }
#endif

            if ( sum>1000000 )
            {
                break;
            }
            if ( prime_array[sum] )
            {
                mn_len = k-m;
                if ( mn_len>mx_len )
                {
                    mmx = m;
                    kmx = k;
                    mx_len = mn_len;
                    mx = sum;
                }
            }
            printf("[%d] m=%d, k=%d, sum = %llu, mx = %llu, mx_len = %llu, mn_len = %llu\r",
                   __LINE__,m,k,sum,mx,mx_len,mn_len);
        }
    }

    printf("\n");
    printf("[%d] mx = %llu\n",__LINE__,mx);
    printf("[%d] mx_len = %llu, kmx = %d, mmx = %d\n",__LINE__,mx_len,kmx,mmx);
    fclose(fd);
    fd = NULL;
}













