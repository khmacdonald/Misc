
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "primes.h"
#include "print_statements.h"

pr_t g_pr = 0;
uint64_t g_cnt = 0;

void permute( char * a, int l, int r );

int32_t is_pan ( pr_t x );

void p41 ( void );

void test01 ( int32_t argc, char * argv[] );
void test02 ( int32_t argc, char * argv[] );

void print_array ( int32_t * p, int32_t n );

/* ---------------------------------------------------------------- */


int32_t main ( int32_t argc, char * argv[] )
{
    int32_t n;

    //test01(argc,argv);
    //test02(argc,argv);
    p41();

END:
    return 0;
}


/* ---------------------------------------------------------------- */

void p41 ( void )
{
    //char dig[] = "0123456789";
    char dig[] = "0123456789";
    //int32_t len = 10;

    permute(dig,0,10);
    info_print("g_pr = %llu",g_pr);

    return;
}

int32_t is_pan ( pr_t x )
{
    int32_t ret = 1;
    uint32_t dig[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    uint32_t d,cnt=0;

    while ( x )
    {
        d = x % 10;
        x = x / 10;
        if ( 0==dig[d] )
        {
            ret = 0;
            goto END;
        }
        dig[d] = 0;
    }

END:
    return ret;
}

void test01 ( int32_t argc, char * argv[] )
{
    //pr_t x = 10123457689, y;
    pr_t x = 1023456789, y;
    //pr_t x = 9814072356, y;
    //pr_t x = 10000004797, y;
    

    if ( 2==argc )
    {
        x = strtol(argv[1],NULL,10);
    }

    if ( is_prime(x) )
    {
        info_print("%llu is a prime",x);
    }
    else
    {
        info_print("%llu is not prime",x);
    }

    if ( is_pan(x) )
    {
        info_print("%llu is a pandigital",x);
    }
    else
    {
        info_print("%llu is a not pandigital",x);
    }
    
    return;
}

void test02 ( int32_t argc, char * argv[] )
{
    char dig[] = "0123456789";
    uint64_t y = 10*9*8*7*6*5*4*3*2*1;

    g_cnt=0;
    permute(dig,0,10);
    info_print("y     = %llu",y);
    info_print("g_cnt = %llu",g_cnt);

    /*
    memset(d,0,11);
    memcpy(d,dig,k);
    permute(d,0,k);
    */
}

void print_array ( int32_t * p, int32_t n )
{
    int32_t k;

    for ( k=0; k<n; ++k )
    {
        printf(" %d ",p[k]);
    }
    printf("\n");

    return;
}

void swap ( char * x, char * y )
{
    char tmp=*x;
    *x = *y;
    *y = tmp;
    return;
}

void pp_check ( pr_t x )
{
    if ( is_prime(x) )
    {
        //info_print("%llu is prime",x);
        //printf("%llu\n",x);
        if ( x>g_pr )
        {
            g_pr = x;
        }
    }
}


void prime_pandigit_check ( char * dig )
{
    char d[11];
    pr_t lpr;
    int32_t k;
    
    for ( k=10; k>1; --k )
    {
        memset(d,0,11);
        memcpy(d,dig,k);
        lpr = strtoll(d,NULL,10);
        pp_check(lpr);
    }
}

void permute( char * a, int l, int r )
{
    int i;

    if ( l==r )
    {
        prime_pandigit_check(a);
    }
    else
    {
        for ( i=l; i<r; i++ )
        {
            swap((a+l),(a+i));
            permute(a,l+1,r);
            swap((a+l),(a+i));
        }
    }

    return;
}






















