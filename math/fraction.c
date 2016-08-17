#include "fraction.h"

int32_t add_fraction ( frac_t c, frac_t a, frac_t b )
{
    int32_t ret = 0;
    uint64_t gcd,lcm,d,n;

    lcm = flcm(&gcd,a->den,b->den);

    return ret;
}

uint64_t fxgcd ( uint64_t a, uint64_t b, uint64_t * x, uint64_t * y )
{
    uint64_t c,xx,yy;

    while ( 0!=b )
    {
        c = a%b;
        a = b;
        b = c;
    }

    return a;
}

uint64_t flcm( uint64_t * gcd, uint64_t a, uint32_t b )
{
    uint64_t g = 0;
     
    if ( 0==a || 0==b )
    {
        goto END;
    }

    g = fgcd(a,b);

    if ( gcd )
    {
        *gcd = g;
    }

    g = (a/g) * b;

END:
    return g;
}

void print_fraction ( frac_t f )
{
    print_fraction_2_file(stdout,f);

    return;
}

int32_t print_fraction_2_str  ( char * str, int32_t slen, frac_t f )
{
    return snprintf(str,slen,"%llu/%llu",f->num,f->den);
}

void print_fraction_2_file  ( FILE * fd,  frac_t f )
{
    char str[512];

    print_fraction_2_str(str,512,f);
    fprintf(fd,"%s",str);

    return;
}
