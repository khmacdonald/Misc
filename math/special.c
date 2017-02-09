#include "special.h"

#define GAMMA_INC  0.00001
#define LN_INC  0.00001
#define EXP_DIFF 0.00001

#define ABS(X) ((X)<0.0) ? -(X) : (X)

static double gamma_kernel ( double x );
static double ln_neg ( double x );
static double ln_pos ( double x );
static double natural_log_old ( double x );

/* ---------------------------------------------------------------------------------- */

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

double gamma ( double x )
{
    double ret;

    if ( x<=0.0 )
    {
        ret = 0.0;
    }
#if 0
    else if ( x<0.5 )
    {
        ret = gamma_kernel(x+1.0)/x; /* Puts x in [0.5,1.5) */
    }
    else if ( x<1.5 )
    {
        ret = gamma_kernel(x); /* Puts x in [0.5,1.5) */
    }
    else
    {
        ret = (x-1.0) * gamma(x-1.0); /* Recurse till x in [0.5,1.5) */
    }
#else
    else if ( x<1.0 )
    {
        ret = gamma_kernel(x);
    }
    else
    {
        ret = (x-1.0) * gamma(x-1.0);
    }
#endif

END:
    return ret;
}

double my_pow_f ( double base, double exp )
{
    return exponential ( exp * natural_log(base) );
}

double exponential ( double x )
{
    int32_t k;
    double sum = 1.0, sn = 1.0, neg = 1.0;

    if ( x<0.0 )
    {
        neg = -1.0;
        x = x * neg;
    }

    for ( k=1; k<10000 && ABS(sn)>=EXP_DIFF; ++k )
    {
        sn /= (float)k;
        sn *= x;
        sum += sn;
    }

    if ( neg<0.0 )
    {
        sum = 1.0/sum;
    }

    return sum;
}

/* 
Need something faster

x = s|exponent|mantissa
                                
 0                   1                   2                   3   
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                        Mantissa                              
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                        |        Exponent     |s|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

s = b63
e = b52-b62
m = 1.b51b50...b0

x = (-1)**s * m * 2**(e-1023)

->

for x>0, then s=0, so (-1)**s=1
LOG LINE: log(x) = log(m) + (e-1023)log(2)

 */
double natural_log ( double x )
{
    double ret = 0.0;
    DOUBLE d = {0};
    double mantissa = 0.0;
    double ln2 = 0.69314718056;
    double two_2_52 = (1L<<52);
    double ln_mantissa = 0.0;

    if ( x<0.0 )
    {
        goto END;
    }

    process_double(&d,x);
    mantissa = 1+(float)d.man/two_2_52;
    ln_mantissa = natural_log_old(mantissa);
    ret = ln_mantissa + (float)d.exp * ln2; /* See LOG LINE above */

END:
    return ret;
}

uint64_t n_ones ( int64_t n )
{
    uint64_t ones = 0-1;

    if ( 0==n || n>63 )
    {
        goto END;
    }

    ones = (1L<<n)-1;

END:
    return ones;
}

static double natural_log_old ( double x )
{
    double ret = 0.0;

    if ( x<=0 )
    {
        ret = 0.0;
    }
    else if ( x<=1.0 )
    {
        ret = ln_neg(x);
    }
    else
    {
        ret = ln_pos(x);
    }

    return ret;
}

/* ---------------------------------------------------------------------------------- */

static double gamma_kernel ( double x )
{
    double ret = 0.5;
    double inc = GAMMA_INC;

    /* 
    Computation of the gamma function only necessitates the computation
    of x such that |x|<=1 due to the fact that gamma(x+1) = x*gamma(x)
    Still need to figure out how to do this.

                    TODO - still need to figure this out.
                    easier to do something along the lines
                    of 0.5 <= x < 1.5.
     */

    return ret;
}

static double ln_neg ( double x )
{
    double sum = 0.0;
    double start = 1.0;

    while ( start>=x )
    {
        sum += (LN_INC*(1.0/start));
        start -= LN_INC;
    }

    return -sum;
}



static double ln_pos ( double x )
{
    double sum = 0.0;
    double start = 1.0;

    while ( start<=x )
    {
        sum += (LN_INC*(1.0/start));
        start += LN_INC;
    }

    return sum;
}

#define DSGN(D)    (((D)>>63) & 1L)
#define DEXP(D)    (((D)>>52) & n_ones(11))
#define DMAN(D)    (((D))     & n_ones(52))

void process_double ( pDOUBLE d,  double x )
{
    union 
    {
        uint64_t u;
        double x;
    } dbl;
    dbl.x = x;

    if ( NULL==d )
    {
        goto END;
    }

    d->sgn = DSGN(dbl.u);
    d->exp = DEXP(dbl.u)-1023;
    d->man = DMAN(dbl.u);

END:
    return;
}

double compute_double ( pDOUBLE dbl )
{
    double x=0.0;
    int64_t s,e;
    uint64_t m;
    union 
    {
        double x;
        uint64_t u;
    } u;

    if ( NULL==dbl )
    {
        goto END;
    }

    /* Set bits according according to data structure */
    s = ((dbl->sgn & 1L)<<63);
    e = ((dbl->exp & n_ones(11))<<52);
    m = dbl->man & n_ones(52);

    /* Converts the bits of an uint64_t to double */
    u.u = 0;
    u.u = s | e | m;
    x = u.x;

END:
    return x;
}

uint32_t totient ( uint32_t n )
{
    uint32_t x=0, k;

    for (  k=1; k<n; ++k )
    {
        if ( 1==gcd(n,k) )
        {
            x++;
        }
    }
    return x;
}














