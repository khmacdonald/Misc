#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t gcd ( uint32_t a, uint32_t b )
{
    uint32_t c;
    
    while ( b!=0 )
    {
        c = a % b;
        a = b;
        b = c;
    }

    return a;
}

uint32_t xgcd ( int32_t *xx, int32_t * yy, uint32_t a, uint32_t b ) {
    uint32_t g;
    int32_t x,y;

    if ( 0==a ) {
        *xx = 0;
        *yy = 1;
        return b;
    }

    g = xgcd(&x,&y,b%a,a);
    *xx = y-((int32_t)b/(int32_t)a) * x;
    *yy = x;

    return g;
}

/* ------------------------------------------------------------ */
int main ( int argc, char ** argv ) {
    uint32_t a = 30, b = 42;
    int32_t s, t;
    uint32_t g;

    printf("Usage: %s <optional number> <optional number>\n",argv[0]);
    printf("    Prints the gcd and xgcd of two numbers.\n");
    printf("    The default numbers are %d and %d.\n",a,b);

    if ( 1<argc ) {
        a = (uint32_t)atoi(argv[1]);
    }
    if ( 2<argc ) {
        b = (uint32_t)atoi(argv[2]);
    }

    g = gcd(a,b);
    printf("%u = gcd(%u,%u)\n",g,a,b);

    g = xgcd(&s,&t,a,b);
    printf("%u = %d * %u + %d * %u\n",g,s,a,t,b);

    return 0;
}

