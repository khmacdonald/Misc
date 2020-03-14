/*
gcc merge_sort.c -o merge_sort ../math/brand.o
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../math/brand.h"

/* 
 * Testing the merge sort with a basic integer array 
 */

void merge_sort ( int * arr, int n );
void print_int_array ( int * arr, int n, int new_line );
void rnd_arr ( int * arr, int n );

int main ( int argc, char ** argv ) {
    int n = 10;
    int * arr = NULL;

    if ( 1<argc ) {
        n = atoi(argv[1]);
    }
    arr = malloc(n*sizeof(*arr));

    rnd_arr(arr,n);

    printf("\n");
    print_int_array(arr,n,1);
    printf("    Sorted:\n");
    merge_sort(arr,n);
    print_int_array(arr,n,1);

    free(arr);

    return 0;
}

void rnd_arr ( int * arr, int n ) {
    int k;
    int mod = 1000;
    brand_t ctx;
    brand_seed_init(ctx);
    brand_array((uint32_t*)arr,n,ctx);
    for ( k=0; k<n; ++k ) {
        arr[k] &= 0x7fffffff;
        arr[k] = arr[k] % mod;
    }

    return;
}

void print_int_array ( int * arr, int n, int new_line ) {
    int k;
    for ( k=0; k<n; ++k ) {
        printf("%d ",arr[k]);
    }
    if ( new_line ) {
        printf("\n");
    }
}

void merge ( int * arr, int n, int * low, int ln, int * high, int hn ) {
    int lidx=0, hidx=0,k;

    for ( k=0; k<n && lidx<ln && hidx<hn; ++k ) {
        if ( low[lidx] < high[hidx] ) {
            arr[k] = low[lidx++];
        } else {
            arr[k] = high[hidx++];
        }
    }

    if ( lidx<ln ) {
        for ( ; k<n && lidx<ln; ++k, ++lidx ) {
            arr[k] = low[lidx];
        }
    } else if ( lidx<ln ) {
        for ( ; k<n && hidx<ln; ++k, ++hidx ) {
            arr[k] = low[hidx];
        }
    }
}

void merge_sort ( int * arr, int n ) {
    int half,tmp,k;
    int ln,hn;
    int * low = NULL;
    int * high = NULL;

    if ( 1==n ) {
        return;
    } else if ( 2==n ) {
        if ( arr[0]>arr[1] ) {
            tmp = arr[0];
            arr[0] = arr[1];
            arr[1] = tmp;
        }
    }
    half = n/2;

    ln = half;
    low = calloc(ln,sizeof(*low));
    memcpy(low,arr,ln*sizeof(*low));

    hn = n-half;
    high= calloc(hn,sizeof(*high));
    memcpy(high,arr+half,hn*sizeof(*high));

    merge_sort(low,ln);
    merge_sort(high,hn);
    merge(arr,n,low,ln,high,hn);

    free(low);
    free(high);

    return;
}
