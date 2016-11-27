#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "primes.h"
#include "print_statements.h"

int32_t check ( pr_t x );
void proj ( void );

void test ( int32_t argc, char * argv[] );

/* ---------------------------------------------------------------- */

int32_t main ( int32_t argc, char * argv[] )
{
    //proj();
    test(argc,argv);

    return 0;
}

/* ---------------------------------------------------------------- */
void test ( int32_t argc, char * argv[] )
{
    int32_t ret,cnt;
    pr_t x = 10,sum,mx,inc,start;

    ret = check(x);
    info_print("%llu -> ret = %d\n",x,ret);
    cnt = 0;
    sum = 0;
    mx = 1000000;
    start = 10;
    inc = 10;
    for ( x=start; x<mx; x+=inc )
    {
        //printf("[%d] x = %llu\r",__LINE__,x);
        ret = check(x);
        cnt += ret;
        if ( ret )
        {
            printf("[%d] x = %llu\n",__LINE__,x);
            sum += x;
        }
    }
    printf("\n");
    info_print("Count below %llu is %d",mx,cnt);
    info_print("Sum below %llu is %llu",mx,sum);

    return;
}
/* ---------------------------------------------------------------- */

int32_t check ( pr_t x )
{
    pr_t y,z;
    pr_t list[6] = { 1, 3, 7, 9, 13, 27 };
    int32_t ret = 1, k;

    y = x*x;
    for ( k=0; k<6; ++k )
    {
        z = y+list[k];
        if ( !is_prime(z) )
        {
            ret = 0;
            break;
        }
    }
    return ret;
}


void proj ( void )
{
    int32_t pnum = 146;
    pr_t mil = 1000000;
    //pr_t mx = 150*mil;
    pr_t mx = mil;
    pr_t sum = 0,x;

    for ( x=10; x<mx; ++x )
    {
        printf("[%d] x = %llu, sum = %llu\r",__LINE__,x,sum);
        if ( check(x) )
        {
            sum += x;
        }
    }

    printf("\nProject %d answer is %llu\n",pnum,sum);

    return;
}

















