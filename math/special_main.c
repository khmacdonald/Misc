#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print_macros.h"
#include "special.h"

int32_t test01 ( int32_t ac, char * av[] );
int32_t test02 ( int32_t ac, char * av[] );
int32_t test03 ( int32_t ac, char * av[] );
int32_t test04 ( int32_t ac, char * av[] );
int32_t test05 ( int32_t ac, char * av[] );
int32_t test06 ( int32_t ac, char * av[] );
int32_t test07 ( int32_t ac, char * av[] );

int32_t euler0070 ( int32_t ac, char * av[] );

int32_t write_exp_x ( int32_t ac, char * av[] );

/* ******************************************************** */
int32_t main ( int32_t argc, char * argv[] )
{
    euler0070(argc,argv);
    return 0;
}
/* ******************************************************** */

int32_t is_perm ( uint32_t a, uint32_t b )
{
    int32_t ret = 1;
    uint32_t ua[10], ub[10];
    uint32_t tmp,k;
    uint32_t aa=a, bb=b;

    memset(ua,0,10*sizeof(ua[0]));
    memset(ub,0,10*sizeof(ub[0]));

    while ( a>0 )
    {
        tmp = a % 10;
        ua[tmp]++;
        a = a/10;
    }

    while ( b>0 )
    {
        tmp = b % 10;
        ub[tmp]++;
        b = b/10;
    }
    for ( tmp = 0; tmp<10; ++tmp )
    {
        if ( ua[tmp]!=ub[tmp] )
        {
            ret = 0;
            goto END;
        }
    }
END:
    return ret;
}

int32_t euler0070 ( int32_t ac, char * av[] )
{
    int32_t k;
    double rmin = 100000000000.0,ratio;
    uint32_t tn, n_min;

    for ( k=2; k<10000000; ++k )
    {
        printf("%u\r",k);
        tn = totient(k);
        if ( is_perm(k,tn) )
        {
            ratio = ((double)k)/((double)tn);
            if (ratio<rmin)
            {
                rmin = ratio;
                n_min = k;
            }
        }
    }
    printf("\n");
    info_print("%u -> ration = %f\n",n_min,rmin);

    return 0;
}


int32_t test07 ( int32_t ac, char * av[] )
{
    uint32_t n = 1000,tn;

    if  ( 2==ac )
    {
        n = strtol(av[1],NULL,10);
    }
    tn = totient(n);
    info_print("totient(%u) = %u\n",n,tn);

    return 0;
}

int32_t write_exp_x ( int32_t ac, char * av[] )
{
    double x = 0.0,y;
    int32_t k;

    for ( k=0; k<10; ++k, x-=10.0 )
    {
        y = exponential(x);
        printf("exp(%f) = %e\n",x,y);
    }

    return 0;
}


int32_t test06 ( int32_t ac, char * av[] )
{
    double t = 0.5,x=0.0000001,inc=0.001;
    double a,b,m,sum;
    int32_t k,max_sz=10;

    printf("Usage: %s <t> <inc>\n",av[0]);
    if ( 2<=ac )
    {
        t = strtod(av[1],NULL);
    }
    if ( 3<=ac )
    {
        inc = strtod(av[2],NULL);
    }

    sum = 0.0;
    printf("t = %e, inc = %f\n",t,inc);
    t -= 1.0;
    for ( k=0; k<max_sz; ++k, x+=inc )
    {
        a = exponential(-x);
        b = my_pow_f(x,t);
        m = a*b;
        sum += m*inc;
        printf("x = %e, exp(-x) = %e, x**(t-1) = %e, exp(x)*x**(t-1) = %e\n",x,a,b,m);
    }
    printf("sum = %e\n",sum);

    return 0;
}


int32_t test05 ( int32_t ac, char * av[] )
{
    double b, e, l;

    if ( 2!=ac )
    {
        info_print("Usage: %s <double>\n",av[0]);
        goto END;
    }

    b = strtod(av[1],NULL);
    e = exponential(b);
    l = natural_log(e);

    info_print("exp(%f) = %e",b,e);
    info_print(" ln(%e) = %f",e,l);

END:
    return 0;
}

int32_t test04 ( int32_t ac, char * av[] )
{
    double x,y,z,a,b,c;
    uint64_t mantissa = (1L<<52);
    DOUBLE d = {0};

    if ( 2!=ac )
    {
        info_print("Usage: %s <double>\n",av[0]);
        goto END;
    }

    x = strtod(av[1],NULL);
    y = exponential(x);
    z = exponential(-1.0*x);
    a = y*z; 
    process_double(&d,y);
    b = natural_log(y);
    c = natural_log(z);

    info_print("x = %f, y = %e, z = %e",x,y,z);
    info_print("a = %f, b = %e, b = %e",a,b,c);
    info_print("%lld,%lld,%f",d.sgn,d.exp,(float)d.man/(float)mantissa);

END:
    return 0;
}


int32_t test03 ( int32_t ac, char * av[] )
{
    double x,y;

    if ( 2!=ac )
    {
        info_print("Usage: %s <double>\n",av[0]);
        goto END;
    }

    x = strtod(av[1],NULL);
    y = exponential(x);
    info_print("exp(%f) = %f\n",x,y);

END:
    return 0;
}


int32_t test02 ( int32_t ac, char * av[] )
{
    double y,x;
    int32_t k;

#if 1
    x = 0.0;
    for ( k=0; k<10; ++k, x-=5.0 )
    {
        y = exponential(x);
        info_print("exp(%f) = %f\n",x,y);
    }
#else
    x = -10.0;
    y = exponential(x);
    info_print("exp(%f) = %f\n",x,y);
#endif

    return 0;
}

int32_t test01 ( int32_t ac, char * av[] )
{
    double ep = exponential(1.0),x,y;
    int32_t k;

    x = 0.25;
    for ( k=0; k<5; ++k, x+=0.1 )
    {
        y = natural_log(x);
        printf("ln(%f) = %f\n",x,y);
    }

    x = 5.0;
    for ( k=0; k<5; ++k, x+=1.0 )
    {
        y = natural_log(x);
        printf("ln(%f) = %f\n",x,y);
    }


    return 0;
}

