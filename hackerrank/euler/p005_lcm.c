#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------------------------------------------------------- */
/*                           PROTOTYPES                             */

/* Recursively compute the Euclidean algorithm */
long gcd ( long a, long b ) {
    if ( 0==a ) {
        return b;
    }
    return gcd(b%a,a);
}

long lcm ( long a, long b ) {
    return a*b/gcd(a,b);
}

/* Get the max number in the array */
long max_arr ( long a[10], int n ) {
    long mx = -1;
    int k;

    for ( k=0; k<n; ++k ) {
        if (a[k]>mx) {
            mx = a[k];
        }
    }

    return mx;
}

void array_lcm ( long a[10], int n ) {
    long mxnum = max_arr(a,n);
    long lcm_array[41];
    int k;

    /*
     * lcm(1,2,...,n) = lcm(lcm(1,2,...,n-1),n). 
     * 
     * Therefore, find the maximum number in the array and
     * save all intermediate values in a lookup table.
     */
    memset(lcm_array,0,41*sizeof(lcm_array[0]));
    lcm_array[1] = 1; /* Prepopulate small values */
    lcm_array[2] = 2;
    lcm_array[3] = 6;
    
    for ( k=4; k<=mxnum; ++k ) {
        /* Create lookup table */ 
        lcm_array[k] = lcm(k,lcm_array[k-1]); 
    }

    for ( k=0; k<n; ++k ) {
        /* Print out LCM for each integer set */ 
        printf("%ld\n",lcm_array[a[k]]); 
    }

    return;
}


/* ---------------------------------------------------------------- */

/* ---------------------------------------------------------------- */
/*                              MAIN                                */
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    int n,k;
    long a[10];

    scanf("%d",&n);
    for ( k=0; k<n; ++k ) {
        scanf("%ld",&a[k]);
    }
    array_lcm(a,n);

    return 0;
}
/* ---------------------------------------------------------------- */


/* ---------------------------------------------------------------- */
/*                           DEFINITIONS                            */

/* ---------------------------------------------------------------- */
