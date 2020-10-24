#include <stdio.h>

void almostSorted ( int arr_count, int * arr ) ;

/* ------------------------------------------------ */

void tests ( ) {
    const int n1 = 4;
    int a1[n1] = { 2, 3, 5, 4 };
    const int n2 = 2;
    int a2[n2] = { 4, 2 };
    const int n3 = 3;
    int a3[n3] = { 3, 1, 2 };
    const int n4 = 6;
    int a4[n4] = { 1, 5, 4, 3, 2, 6 };
    const int N = 4;
    int n[N] = { 4, 2, 3, 6 };
    int * x[N] = { a1, a2, a3, a4 };
    int k;

    for ( k=0; k<N; ++k ) {
        almostSorted(n[k],x[k]);
    }
}

int main ( int argc, char ** argv ) {
    tests();
    return 0;
}

/* ------------------------------------------------ */

int get_start ( int arr_count, int * arr ) {
    int k;

    for ( k=0; k<arr_count-1; ++k ) {
        if ( arr[k] > arr[k+1] ) {
            return k;
        }
    }

    return -1;
}

int get_end ( int arr_count, int * arr, int start ) {
    int k;

    for ( k=start+1; k<arr_count-1; ++k ) {
        if ( arr[k] < arr[k+1] ) {
            return k;
        }
    }

    return -1;
}

void almostSorted ( int arr_count, int * arr ) {
    int start = get_start(arr_count,arr);
    int end = get_end(arr_count,arr,start);

    printf("[%d] start = %d, end = %d\n",__LINE__,start,end);
}

