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

    q = lim/mul;        /* lim = q*mul + r */
    r = lim % mul;
    if ( 0==r ) {       /* Exclude lim in the sum */
        q--;
    }
    bsum = q*(q+1)/2; /* = 1 + 2 + 3 + ... + q */
    sum = bsum * mul; /* = mul + 2*mul + 3*mul + ... + q*mul */

    return sum;
}

long long sum_lim_fast ( long long lim ) {
    long long s3 = sum_lim_mul( 3,lim); /* The sum of all multiples of 3 less than lim */
    long long s5 = sum_lim_mul( 5,lim); /* The sum of all multiples of 5 less than lim */
    long long s15= sum_lim_mul(15,lim); /* The sum of all multiples of 15 less than lim */

    /*
     * s3 includes all mulitples of 15, as does s5.  Therefore, 
     * all mulitples of 15 are counted twice. 
     */
    return s3 + s5 - s15;
}

/* ---------------------------------------------------------------- */
