#include <stdint.h>

int64_t lucas( int64_t n )
{
    int64_t x1=1, x2=3, ret=0,k;

    if ( 1==n )
    {
        ret=x1;
        goto END;
    }
    if ( 2==n )
    {
        ret=x2;
        goto END;
    }
    for ( k=2; k<n; )
    {
        ++k;
        ret = x1+x2;
        x1=x2;
        x2=ret;
    }

END:
    return ret;
}

int64_t lucas_lehmer ( int64_t n )
{
    int64_t x1=4,ret=0,k;

    if ( 1==n )
    {
        ret = x1;
        goto END;
    }

    for ( k=0; k<n; )
    {
        ++k;
        ret = x1*x1 - 2;
        x1 = ret;
    }

END:
    return ret;
}
