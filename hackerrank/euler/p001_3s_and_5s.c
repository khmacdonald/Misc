#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/* ---------------------------------------------------------------- */
/*                           PROTOTYPES                             */

long long sum_lim_fast ( long long lim ); /* Not fast enough */

/* ---------------------------------------------------------------- */

/* ---------------------------------------------------------------- */
/*                              MAIN                                */
int main () {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    int k,nlims = 0;
    int lim = 0;
    long long sum = 0;

    scanf("%d",&nlims);
    for ( k=0; k<nlims; ++k ) {
        scanf("%d",&lim);
        sum = sum_lim_fast((long long)lim);
        printf("%lld\n\n",sum);
    }

    return 0;
}
/* ---------------------------------------------------------------- */


/* ---------------------------------------------------------------- */
/*                           DEFINITIONS                            */

long long sum_lim_mul ( long long mul, long long lim ) {
    int q, r, bsum, sum;

    q = lim/mul;
    r = lim % mul;
    if ( 0==r ) {
        q--;
    }
    bsum = q*(q+1)/2;
    sum = bsum * mul;

    return sum;
}

long long sum_lim_fast ( long long lim ) {
    long long s3 = sum_lim_mul( 3,lim);
    long long s5 = sum_lim_mul( 5,lim);
    long long s15= sum_lim_mul(15,lim);

    return s3 + s5 - s15;
}

/* ---------------------------------------------------------------- */
