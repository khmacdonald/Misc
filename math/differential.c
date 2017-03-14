#include <stdio.h>
#include <math.h>

#define LIM1    20.0
#define a       -5.0
#define b       5.0
#define pre     100.0

/*
This file calculates the func, makes a plot.
It also calculates the max and min of func
at given points and its first and second
numerical derivative.
 */
float func ( float x )
{
    return exp ( x / 2.0 ) / pow ( x, 2 );
}

int main ( void )
{
    return 0;
}
