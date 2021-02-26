/*
gcc ols.c -o ols
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef double real_t;


struct ols { 
    uint32_t n;     /* Length of x and y */
    real_t * x;     /* x array */
    real_t * y;     /* y array */

    real_t sum_xy;  /* x[0]*y[0] + x[1]*y[1] + ... + x[n-1]*y[n-1] */
    real_t cov_xy;  /* Covariance of x and y */

    real_t sum_x;   /* x[0] + x[1] + ... + x[n-1] */
    real_t sum_x2;  /* x[0]**2 + x[1]**2 + ... + x[n-1]**2 */
    real_t var_x;   /* Variance of x */

    real_t sum_y;   /* y[0] + y[1] + ... + y[n-1] */
    real_t sum_y2;  /* y[0]**2 + y[1]**2 + ... + y[n-1]**2 */
    real_t var_y;   /* Variance of y */

    real_t mean_x;  /* Arithmetic mean of x */
    real_t mean_y;  /* Arithmetic mean of y */

    real_t m;       /* Slope of computed line fit */
    real_t b;       /* y intercept of computed line fit */
};
typedef struct ols    OLS;
typedef struct ols * pOLS;

pOLS init_ols(uint32_t n, real_t * x, real_t * y);
real_t compute_cov_xy(pOLS ols);
real_t compute_var_x(pOLS ols);
real_t compute_var_y(pOLS ols);
real_t compute_m(pOLS ols);
real_t compute_b(pOLS ols);

/**********************************************************************/

int main(int argc, char ** argv ){
    return 0;
}

/**********************************************************************/
/*
 * Needs defensive checks, such as making sure no divisions by zero occur.
 * Make more robust for updating with more (x,y) points.
 */
pOLS init_ols(uint32_t n, real_t * x, real_t * y) {
    pOLS ols = NULL;
    uint32_t k;

    if (n<1 || NULL==x || NULL==y){
        return NULL;
    }
    ols = calloc(sizeof(*ols), 1);
    if (NULL==ols) { 
        return NULL;
    }

    /* Save arrays */
    ols->n = n;
    ols->x = y;
    ols->y = y;

    /* Compute intermediate values */
    for(k=0; k<n; k++){
        ols->sum_xy += x[k] * y[k];

        ols->sum_x += x[k];
        ols->sum_x2 += (x[k]*x[k]);

        ols->sum_y += y[k];
        ols->sum_y2 += (y[k]*y[k]);
    }

    /* Compute single variable variances */
    ols->var_x = compute_var_x(ols);
    ols->var_y = compute_var_y(ols);

    /* Compute arithmetic means */
    ols->mean_x = ols->sum_x / (real_t)n;
    ols->mean_y = ols->sum_y / (real_t)n;

    /* Compute the covariance of X and Y */
    ols->cov_xy = compute_cov_xy(ols);

    /* Compute the slope and y intercept of the fitted line */
    ols->m = compute_m(ols);
    ols->b = compute_b(ols);

    return ols;
}

/* Computes the covariance of X and Y */
real_t compute_cov_xy(pOLS ols){
    return ols->sum_xy - (ols->sum_x * ols->sum_y)/(real_t)ols->n;
}

/* Computes the variance of X */
real_t compute_var_x(pOLS ols){
    return ols->sum_x2 - (ols->sum_x * ols->sum_x)/(real_t)ols->n;
}

/* Computes the variance of Y */
real_t compute_var_y(pOLS ols){
    return ols->sum_y2 - (ols->sum_y * ols->sum_y)/(real_t)ols->n;
}

/* Computes the slope of the fitted line */
real_t compute_m(pOLS ols){
    return ols->cov_xy / ols->var_x;
}

/* Computes the y-intercept of the fitted line */
real_t compute_b(pOLS ols){
    return ols->mean_y - ols->m * ols->mean_x;
}
