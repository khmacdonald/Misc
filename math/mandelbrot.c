/*
gcc -o mandelbrot mandelbrot.c
 */

#include <stdio.h>
#include <stdlib.h>

#define N 10000

struct comp
{
    double x;
    double y;
};

typedef struct comp _c[1];

int add ( _c s, _c a, _c b );
int sq ( _c s, _c a);
double sq_mod ( _c a );
void c_print ( _c a );

int mfunc ( _c x, _c c );
int mandelbrot ( _c c, int iter );

/* ---------------------------------------------- */

int main ( int argc, char * argv[] )
{
    double cx = 0.0, cy = 0.0;
    int iter=N;
    _c c;

    if ( 2<=argc )
    {
        cx = strtod(argv[1],NULL);
    }
    if ( 3<=argc )
    {
        cy = strtod(argv[2],NULL);
    }
    if ( 4<=argc )
    {
        iter = strtol(argv[3],NULL,10);
    }

    c->x = cx;
    c->y = cy;

    mandelbrot(c,iter);

    return 0;
}

/* ---------------------------------------------- */

int add ( _c s, _c a, _c b )
{
    int ret = 0;

    s->x = a->x + b->x;
    s->y = a->y + b->y;

    return ret;
}

int sq ( _c s, _c a)
{
    int ret=0;

    s->x = a->x*a->x - a->y*a->y;
    s->y = 2.0*a->x*a->y;

    return ret;
}
    
double sq_mod ( _c a )
{
    return a->x*a->x + a->y*a->y;
}

void c_print ( _c a )
{
    printf("(%.2f,%.2f)\n",a->x,a->y);
}

int mfunc ( _c x, _c c )
{
    _c z;
    sq(z,x);
    add(x,z,c);

    return 0;
}

int mandelbrot ( _c c, int iter )
{
    _c x = {0.0, 0.0};
    int k;
    double m;

    for ( k=0; k<iter; ++k )
    {
        mfunc(x,c);
        m = sq_mod(x);
        if ( m>=4.0 )
        {
            break;
        }
    }
    c_print(x);
    printf("m = %f (%d)\n",m,k);

    return k;
}






























