
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "primes.h"
#include "print_statements.h"

int32_t  all_odd_dig ( uint32_t x );
uint32_t basic_circle ( uint32_t x );
uint32_t circular ( uint32_t x, uint32_t * d, int32_t n );
uint32_t dig_arr ( uint32_t x, uint32_t ** d, int32_t * n );


void p35 ( void );

void print_array ( uint32_t * d, int32_t n );

void test01 ( int32_t argc, char * argv[] );

/* ---------------------------------------------------------------- */


int32_t main ( int32_t argc, char * argv[] )
{
    int32_t n;

    //test01(argc,argv);
    p35();

END:
    return 0;
}


/* ---------------------------------------------------------------- */

int32_t  all_odd_dig ( uint32_t x )
{
    int32_t ret = 1;
    uint32_t d;    
    
    while ( x )
    {
        d = x % 10;
        if ( 0==(d & 1) )
        {
            ret = 0;
            goto END;
        }
        x /= 10;
    }

END:
    return ret;
}

uint32_t dig_arr ( uint32_t x, uint32_t ** d, int32_t * n )
{
    uint32_t ret = 0,y,cnt,k;
    uint32_t * dd = NULL;

    y = x;
    cnt = 0;
    while ( y )
    {
        y /= 10;
        cnt++;
    }

    dd = calloc(sizeof(x),cnt);
    *n = cnt;
    *d = dd;
    y = x;
    for ( k=0; k<cnt; ++k )
    {
        dd[k] = y % 10;
        y /= 10;
    }

    return ret;
}

int32_t is_bad ( uint32_t x, uint32_t * p )
{
    int32_t  ret = 0;

    if ( 0==p[x] )
    {
        ret = 1;
        goto END;
    }
    if ( !all_odd_dig(x) )
    {
        ret = 1;
        goto END;
    }
    if ( !is_prime(x) )
    {
        ret = 1;
        goto END;
    }
END:
    return ret;
}

void p35 ( void )
{
    int32_t k,pr,x,y;
    int32_t cnt,good;
    int32_t max = 1000000;
    //int32_t max = 100;

    cnt = 1;
    for ( k=2; k<max; ++k )
    {
        if ( !all_odd_dig(k) )
        {
            continue;
        }
        if ( !is_prime(k) )
        {
            continue;
        }
        pr = basic_circle(k);
        if ( k<10 )
        {
            info_print("%d",k);
            cnt++;
            continue;
        }
        good = 1;
        while ( pr!=k )
        {
            if ( !is_prime(pr) )
            {
                good = 0;
            }
            pr = basic_circle(pr);
        }
        if ( good )
        {
            info_print("%d",k);
            cnt++;
        }
    }
    info_print("Count = %d",cnt);
}


void print_array ( uint32_t * d, int32_t n )
{
    int32_t k;

    for ( k=0; k<n; ++k )
    {
        printf("%d ",d[k]);
    }
}

uint32_t basic_circle ( uint32_t x )
{
    uint32_t d,y;

    if ( x<10 )
    {
        y = x;
        goto END;
    }

    d = x % 10;
    x = x / 10;

    y = 10;
    while(y<x)
    {
        y *= 10;
    }
    
    y = y*d + x;

END:
    return y;
}

uint32_t circular ( uint32_t x, uint32_t * d, int32_t n )
{
    uint32_t y,tmp,k,ten=1;

    tmp = d[0];
    y = 0;
    for ( k=0; k<n-1; ++k )
    {
        d[k] = d[k+1];
        y = y + d[k] * ten;
        ten *= 10;
    }
    y = y + ten * tmp;
    d[n-1] = tmp;

END:
    return y;
}

void test01 ( int32_t argc, char * argv[] )
{
    uint32_t x,y;

    if ( 2!=argc )
    {
        printf("ERROR: %s <integer>\n",argv[0]);
        goto END;
    }

    x = strtol(argv[1],NULL,10);
    y = basic_circle(x);

    info_print("%u -> %u\n",x,y);

END:
    return;
}




























