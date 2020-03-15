/*
gcc quick_sort.c -o quick_sort ../math/brand.o
 */

#include <stdio.h>
#include <stdlib.h>

#include "../math/brand.h"
#include "../common/common.h"
#include "../common/print_statements.h"

int partition ( int * arr, int lo, int hi );
void quick_sort ( int * arr, int lo, int hi );
int * rnd_array ( int n );
void swap ( int * arr, int n, int m );

/* ------------------------------------------------------------------------ */
int main ( int argc, char ** argv ) {
    int n = 10;
    int * arr = NULL;
    if ( 1<argc ) {
        n = atoi(argv[1]);
    }

    arr = rnd_array(n);
    c_print_array_int(arr,n,1);
    quick_sort(arr,0,n);
    c_print_array_int(arr,n,1);
    free(arr);

    return 0;
}
/* ------------------------------------------------------------------------ */

int * rnd_array ( int n ) {
    int * arr = calloc(n,sizeof(*arr));
    int mod = 1000,k;
    brand_t ctx;

    brand_seed_init(ctx);               /* Seed and initialize randomizer */
    //brand_init(ctx,0xbadbeef);        /* Initialize with a fixed seed */
    brand_array((uint32_t*)arr,n,ctx);  /* Get random integer array */

    for ( k=0; k<n; ++k ) {
        arr[k] &= 0x7fffffff;       /* Ensure positive numbers */
        arr[k] = arr[k] % mod;      /* Modulo numbers */
    }

    return arr;
}

void quick_sort ( int * arr, int lo, int hi ) {
    int p;
    if ( lo<hi ) {
        p = partition(arr,lo,hi);
        quick_sort(arr,lo,p-1);
        quick_sort(arr,p+1,hi);
    }
    return;
}

int partition ( int * arr, int lo, int hi ) {
    int pivot = arr[hi];
    int k = lo,m;
    for ( m=lo; m<hi; ++m ) {
        if ( arr[m] < pivot ) {
            swap(arr,m,k);
            k++;
        }
    }
    swap(arr,m,k);
    return k;
}

void swap ( int * arr, int n, int m ) {
    int tmp = arr[n];
    arr[n] = arr[m];
    arr[m] = tmp;
}
