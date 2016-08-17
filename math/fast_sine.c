#include <stdio.h>
#include <math.h>

/*
http://stackoverflow.com/questions/3380628/fast-arc-cos-algorithm
 */

#define pi 3.1459

float my_abs ( float x );
float fast_sine(float x);
float fast_cosine(float x);

int main ( int argc, char * argv[] )
{
    float interval = pi/500.0, x = -pi, y, z, r, d, sumd = 0.0;
    float max = -1.0, rmax = -1.0;
    int k;

#if 1
    for ( k=0; k<1000; ++k, x += interval )
    {
#if 1
        y = fast_sine(x);
        z = sin(x);
        d = my_abs(y-z);
        if ( d>max )
        {
            max = d;
        }
        r = d/z;
        if ( r>rmax )
        {
            rmax = r;
        }

        printf("fast_sine(%2.5f) = %2.5f\n",x,y);
        printf("sin      (%2.5f) = %2.5f\n",x,z);
        printf("abs_diff           = %2.5f\n",d);
        printf("rel_diff           = %2.5f\n\n",r);
        sumd += d;
#endif
    }
    y = sumd/1000.0;
    printf("Average difference = %f\n",y);
    printf("Max difference = %f\n",max);
    printf("Max rel diff   = %f\n",rmax);
#endif
    
    return 0;
}
    



float my_abs ( float x )
{
    return (x<0.0) ? -x : x;
}


float fast_sine(float x)
{
    const float B = 4/pi;
    const float C = -4/(pi*pi);

    float y = B * x + C * x * my_abs(x);

    //  const float Q = 0.775;
    const float P = 0.225;

    y = P * (y * my_abs(y) - y) + y;   // Q * y + P * y * abs(y)


    return y;
}


float fast_cosine(float x)
{
    return fast_sine(x + (pi / 2));
}

