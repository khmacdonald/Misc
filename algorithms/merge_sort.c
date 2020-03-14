/*
gcc merge_sort.c -o merge_sort ../math/brand.o
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../math/brand.h"
#include "../common/print_statements.h"

/* 
 * Testing the merge sort with a basic integer array 
 */

 int level = 0;

void merge_sort ( int * arr, int n );
void print_int_array ( int * arr, int n, int new_line );
void rnd_arr ( int * arr, int n );

/* ------------------------------------------------------------ */

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

/* ------------------------------------------------------------ */

void rnd_arr ( int * arr, int n ) {
    int k;
    int mod = 1000;
    brand_t ctx;

    brand_seed_init(ctx);               /* Seed and initialize randomizer */
    //brand_init(ctx,0xbadbeef);        /* Initialize with a fixed seed */
    brand_array((uint32_t*)arr,n,ctx);  /* Get random integer array */

    for ( k=0; k<n; ++k ) {
        arr[k] &= 0x7fffffff;       /* Ensure positive numbers */
        arr[k] = arr[k] % mod;      /* Modulo numbers */
    }

    return;
}

void print_int_array ( int * arr, int n, int new_line ) {
    int k;

    if ( n<1 ) {
        return;
    }
    printf("(%d",arr[0]);
    for ( k=1; k<n; ++k ) {
        printf(", %d",arr[k]);
    }
    printf(")");
    if ( new_line ) {
        printf("\n");
    }
}

void merge ( int * arr, int n, int * low, int ln, int * high, int hn ) {
    int lidx=0, hidx=0,k;

    /* Merge arrays */
    for ( k=0; k<n && lidx<ln && hidx<hn; ++k ) {
        if ( low[lidx] < high[hidx] ) {
            arr[k] = low[lidx++];
        } else {
            arr[k] = high[hidx++];
        }
    }

    /* Copy the remainder of the low or high array */
    if ( lidx<ln ) {
        for ( ; k<n && lidx<ln; ++k ) {
            arr[k] = low[lidx++];
        }
    } else if ( hidx<hn ) {
        for ( ; k<n && hidx<hn; ++k ) {
            arr[k] = high[hidx++];
        }
    }
}

void merge_sort_base ( int * arr, int n ) {
    int tmp;
    if ( 2==n ) {
        if ( arr[0]>arr[1] ) {
            tmp = arr[0];
            arr[0] = arr[1];
            arr[1] = tmp;
        }
    }
    return;
}

int * copy_part_of_array ( int * arr, int n ) {
    int * narr = calloc1(n,sizeof(*narr));
    memcpy(narr,arr,n*sizeof(narr));
    return narr;
}

void merge_sort ( int * arr, int n ) {
    int half,ln,hn;
    int * low = NULL;
    int * high = NULL;

    level++;    /* Level of recursion */

    if ( n<3 ) {
        merge_sort_base(arr,n);
        goto END;
    }

    /* Divide and conquor */
    ln = n/2;
    hn = n-ln

    low  = copy_part_of_array(arr,ln);
    high = copy_part_of_array(arr+half,hn);

    merge_sort(low,ln);             /* Sort low half of array */
    merge_sort(high,hn);            /* Sort high half of array */
    merge(arr,n,low,ln,high,hn);    /* Merge sorted halves */

    free(low);
    free(high);

END:
    level--;
    return;
}
