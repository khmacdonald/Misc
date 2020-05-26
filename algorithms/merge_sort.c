/*
gcc merge_sort.c -o merge_sort ../math/brand.o
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../math/brand.h"
#include "../common/print_statements.h"

/* 
 * Testing the merge sort with a basic integer array 
 */

 int level = 0;

void merge_sort ( int * arr, int n );
void merge_sort_01 ( int * arr, int n );
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
    //merge_sort(arr,n);
    merge_sort_01(arr,n);
    print_int_array(arr,n,1);

    free(arr);

    return 0;
}

/* ------------------------------------------------------------ */

void rnd_arr ( int * arr, int n ) {
    int k;
    int mod = 1000;
    int rnd;

    srand(time(NULL));

    for ( k=0; k<n; ++k ) {
        arr[k] = rand() & 0x7fffffff;       /* Ensure positive numbers */
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
    int * narr = calloc(n,sizeof(*narr));
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
    hn = n-ln;

    low  = copy_part_of_array(arr,ln);
    high = copy_part_of_array(arr+ln,hn);

    merge_sort(low,ln);             /* Sort low half of array */
    merge_sort(high,hn);            /* Sort high half of array */
    merge(arr,n,low,ln,high,hn);    /* Merge sorted halves */

    free(low);
    free(high);

END:
    level--;
    return;
}

void base_case_01 ( int * a, int n ) {
    int tmp;

    /* Do base cases */
    if ( 2==n ) {
        if ( a[0] > a[1] ) {
            tmp = a[0];
            a[0] = a[1];
            a[1] = tmp;
            return;
        }
    }
}

void merge_01 ( int * arr, int n, int ln ) {
    int * tarr = calloc(n,sizeof(*tarr));
    int hn = n-ln;
    int k, lidx = 0, hidx = 0;
    int * lo = arr;
    int * hi = arr + ln;

    if ( NULL==tarr ) {
        printf("[%d] Error: Could not allocate temporary array\n",__LINE__);
        printf("            for merge.  Exiting .... \n");
        exit(1);
    }

    /* Merge the halves */
    for ( k=0; k<n && lidx<ln && hidx<hn; ++k ) {
        if ( lo[lidx] < hi[hidx] ) {
            tarr[k] = lo[lidx++];
        } else {
            tarr[k] = hi[hidx++];
        }
    }

    /* 
     * There can be some left over in the lower or upper half, but
     * not both
     */
    if ( lidx<ln ) {  /* Copy remaining lower half */
        for ( ; k<n && lidx<ln; ++k ) {
            tarr[k] = lo[lidx++];
        }
    } else if ( hidx<hn ) {  /* Copy remaining upper half */
        for ( ; k<n && hidx<hn; ++k ) {
            tarr[k] = hi[hidx++];
        }
    }

    /* Copy sorted temp array to original array */
    memcpy(arr,tarr,n*sizeof(tarr[0]));
    free(tarr);

    return;
}

void merge_sort_01 ( int * arr, int n ) {
    int half, ln, hn, tmp;

    level++;

    if ( NULL==arr || n<1 ) {
        return;
    }

    if ( n<3 ) {
        base_case_01(arr,n);
        return;
    }

    ln = n/2;   /* Divide and conquer */
    hn = n-ln;

    merge_sort_01(arr,ln);      /* Sort lower half */
    merge_sort_01(arr+ln,hn);   /* Sort upper half */
    merge_01(arr,n,ln);         /* Merge the halves */

    level--;

    return;
}
