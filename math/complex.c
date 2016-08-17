#include "complex.h"

void complex_init ( complex_t a, double x, double y )
{
    a->x = x;
    a->y = y;

    return;
}

void complex_copy ( complex_t a, complex_t b )
{
    a->x = b->x;
    a->y = b->y;

    return;
}

void complex_print_file ( FILE * ofd, complex_t a )
{
    fprintf(ofd,"(%f,%f)",a->x,a->y);
}

void complex_print ( complex_t a )
{
    complex_print_file(stderr,a);
}

void complex_neg ( complex_t n, complex_t a )
{
    n->x = -a->x;
    n->y = -a->y;

    return;
}

void complex_conj ( complex_t c, complex_t a )
{
    c->x = a->x;
    c->y = -a->y;

    return;
}

double complex_abs_sq ( complex_t a )
{
    return a->x*a->x + a->y*a->y;
}

double complex_abs( complex_t a )
{
    return sqrt(complex_abs_sq(a));
}

khm_error_t complex_add ( complex_t sum, complex_t a, complex_t b )
{
    khm_error_t ret=khm_success;
    complex_t s;

    complex_init(s,0.0,0.0);

    s->x = a->x + b->x;
    s->y = a->y + b->y;

    complex_copy(sum,s);

    return ret;
}

khm_error_t complex_mul ( complex_t mul, complex_t a, complex_t b )
{
    khm_error_t ret=khm_success;
    complex_t m;

    complex_init(m,0.0,0.0);
    m->x = a->x*b->x - a->y*b->y;
    m->y = a->x*b->y + a->y*b->x;

    complex_copy(mul,m);

    return ret;
}

khm_error_t complex_exp ( complex_t ex, complex_t z, int32_t n )
{
    khm_error_t ret=khm_success;
    int32_t k;
    complex_t e,ek;

    complex_init(e,1.0,0.0);
    if ( n<0 )
    {
        ret = khm_failure;
        goto END;
    }
    if ( 0==n )
    {
        goto END;
    }

    complex_init(ek,1.0,0.0);
    for ( k=0; k<n; ++k )
    {
        complex_mul(ek,ek,z);
        ek->x = ek->x / (double)(k+1);
        ek->y = ek->y / (double)(k+1);
        dbg_complex_print(ek);
        complex_add(e,e,ek);
    }

    complex_copy(ex,e);

END:
    return ret;
}
