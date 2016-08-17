#include "least_squares.h"

pLS new_ls( void )
{
    pLS ls = (pLS)calloc(1,sizeof(*ls)); /* Allocate the least squares data structure */
    
    if ( ls )
    {
        zero_ls(ls); /* zero out least squares data structure */
    }

    return ls;
}

void zero_ls ( pLS ls )
{
    if ( ls )
    {
        memset(ls,0,sizeof(*ls)); /* zero out least squares data structure */
    }
    return;
}

khm_error_t add_ls_points ( pLS ls, pLSP p, int32_t psz )
{
    khm_error_t ret = khm_success;
    int32_t k;

    if ( NULL==ls || NULL==p )
    {
        ret = khm_badargs;
        goto END;
    }

    for ( k=0; k<psz; ++k )
    {
        /* For each point in the point list */
        ls->sum_x += p[k].x;                /* Sum of x */
        ls->sum_y += p[k].y;                /* Sum of y */
        ls->sum_x2 += (p[k].x * p[k].x);    /* sum of x**2 */
        ls->sum_y2 += (p[k].y * p[k].y);    /* sum of y**2 */
        ls->sum_xy += (p[k].x * p[k].y);    /* sum of x*y */
        ls->n++;                            /* Total number of points */
    }

END:
    return ret;
}

khm_error_t best_line ( lsel * m, lsel * b, pLS ls )
{
    khm_error_t ret = khm_success;
    lsel num,den;

    if ( NULL==m || NULL==b || NULL==ls )
    {
        ret = khm_badargs;
        goto END;
    }
    *m = 0; /* Initialize slope */
    *b = 0; /* Initialize y-intercept */

    /* Compute the slope of the best fit line */
    num = ((float)ls->n * ls->sum_xy) - (ls->sum_x * ls->sum_y);
    den = ((float)ls->n * ls->sum_x2) - (ls->sum_x * ls->sum_x);
    if ( den )
    {
        *m = num/den; /* Estimated slope */
    }

    /* The mean of x and y are on the best fit line */
    num = ls->sum_y - (*m * ls->sum_x);
    den = (float)ls->n;
    if ( den )
    {
        *b = num/den; /* Estimated y-intercept */
    }
    else
    {
        ret = khm_badargs; /* No points in the least squares data structure */
    }

END:
    return ret;
}

khm_error_t generate_random_line ( pLSP p, int32_t n, lsel m, lsel b, lsel x, lsel y )
{
    khm_error_t ret = khm_success;
    int32_t k;
    float interval=0,next, random, nx;
    brand_t ctx; 

    if ( y<=x || NULL==p || n<1 )
    {
        ret = khm_badargs;
        goto END;
    }

    /* Set up random data structure */
    brand_seed_init(ctx);
    interval = (y-x)/(float)n; /* Divide the interval (x,y) into n equal spaces */
    nx = x + (interval/2.0);; /* The first point is the mid-point of the first interval */
    for ( k=0; k<n; ++k )
    {
        /* Save off x and y */
        p[k].x = nx;
        p[k].y = m*nx + b;

        /* Add white noise to point */
        random =  brand_next_standard_normal(ctx);
        p[k].x += random;
        random =  brand_next_standard_normal(ctx);
        p[k].y += random;

        /* Got to mid-point of the next interval */
        nx += interval; 
    }

END:
    return ret;
}






















