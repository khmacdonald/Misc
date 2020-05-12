#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/print_statements.h"

int smallest_n ( int * arr, int sz, int n ) ;
extern int * shuffle ( int n ) ;

#define N   100
int main ( int argc, char ** argv ) {
    int n = 4;
    int * arr = shuffle(N);
    int ans; 

    if ( 1<argc ) {
        n = atoi(argv[1]);
    }

    ans = smallest_n(arr,N,n);
    dbg_print("%d -> ans = %d\n",n,ans);

    free(arr);
    return 0;
}

/*
 * Finds the nth smallest number in an array.
 */
int level = 0;
int smallest_n ( int * arr, int sz, int n ) {
    int * lo = NULL;
    int * hi = NULL;
    int k,lidx = 0, hidx = 0;
    int ppnt, pivot, ans = INT_MIN;

    level++;
    if ( n>sz ) {
        goto END;
    }
    if ( 0==n ) {
        err_print("Error, leve = %d, n = 0\n",level);
        exit(1);
    }
    /* Special case */
    if ( 1==n ) {
        ans = arr[0];
        for ( k=1; k<sz; ++k ) {
            if ( arr[k]<ans ) {
                ans = arr[k];
            }
        }
        goto END;
    }
    /* Another special case */
    if ( sz==n ) {
        ans = arr[0];
        for ( k=1; k<sz; ++k ) {
            if ( arr[k]>ans ) {
                ans = arr[k];
            }
        }
        goto END;
    }
    lo = calloc(sz,sizeof(*lo));
    hi = calloc(sz,sizeof(*lo));
    ppnt = sz/2;
    pivot = arr[ppnt];

    /* Divide and conquor */
    for ( k=0; k<sz; ++k ) {
        if ( k==ppnt ) {
            continue;
        }
        if ( arr[k] < pivot ) {
            lo[lidx++] = arr[k];
        } else {
            hi[hidx++] = arr[k];
        }
    }

    if ( lidx==(n-1) ) {
        ans = pivot;
        goto END;
    }
    if ( lidx < n ) {
        ans = smallest_n(hi,hidx,n-1-lidx);
    } else {
        ans = smallest_n(lo,lidx,n);
    }
    free(lo);
    free(hi);

END:
    level--;
    return ans;
}
