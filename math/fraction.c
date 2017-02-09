#include "fraction.h"

int32_t add_fraction ( frac_t c, frac_t a, frac_t b )
{
    int32_t ret = 0,d;

    if ( a->den==b->den )
    {
        c->den = a->den;
        c->num = a->num + b->num;
    }
    else
    {
        c->den = a->den * b->den;
        c->num = a->num * b->den + a->den * b->num;
    }
    d = gcd(c->num,c->den);
    if ( d>1 )
    {
        c->num /= d;
        c->den /= d;
    }

    return ret;
}

int32_t sub_fraction ( frac_t c, frac_t a, frac_t b )
{
    frac_t d;
    d->num = -b->num;
    d->den = b->den;

    return add_fraction(c,a,d);
}

uint64_t fxgcd ( uint64_t a, uint64_t b, uint64_t * x, uint64_t * y )
{
    uint64_t c,xx,yy;

    /*
     * Will have to add the xx and yy to the algorithm to complete
     * the Euclidean algorithm.
     */
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


























