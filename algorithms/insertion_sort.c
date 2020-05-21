/*
gcc insertion_sort.c -o insertion_sort../common/common.o

The Algorithm Design Manual Figure 2.5, page 42
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../common/common.h"

int insertion_sort ( int sz, int * a ) ;

/* ------------------------------------------------ */

int main ( int argc, char ** argv ) {
    int n = 10;
    int * a;

    if ( 1<argc ) {
        n = atoi(argv[1]);
    }

    a = c_random_array(n,1,100);

    c_print_array_int_lbl("Before",a,n,1);

    insertion_sort(n,a); /* Sort */

    c_print_array_int_lbl("After ",a,n,1);

    return 0;
}

/* ------------------------------------------------ */

void swap ( int * arr, int s, int t ) {
    int tmp  = arr[s];
    arr[s] = arr[t];
    arr[t] = tmp;
    return;
}
/*
 * Doesn't quite work.
 */
int insertion_sort ( int sz, int * a ) {
    int k, m, min;

    if ( NULL==a ) {
        return 1;
    }

    for ( k=1; k<sz; ++k ) {
        m=k;
        while ( (m>0) && (a[m] < a[m-1]) ) {
            swap(a,m,m-1);
            m = m-1;
        }
    }

    return 0;
}








