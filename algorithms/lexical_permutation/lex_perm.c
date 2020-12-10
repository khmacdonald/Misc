#include <stdio.h>

#include "common.h"
#include "print_statements.h"


int factorial(int n);
int next_lex_perm(int n, int * a);

int test01(int argc, char ** argv);
int test02(int argc, char ** argv);
int test03(int argc, char ** argv);

/* ------------------------------------------------------ */

int main ( int argc, char ** argv ) {
    test03(argc, argv);
}

/* ------------------------------------------------------ */

int test03 ( int argc, char ** argv ) {
    const int n = 3;
    int arr[n] = {0, 1, 2};
    int cnt, max_cnt = 10;

    c_print_array_int(arr, n, 1);
    for ( cnt=0; cnt<max_cnt; ++cnt ) {
        next_lex_perm(n, arr);
        c_print_array_int(arr, n, 1);
    }
    return 0;
}


int test02 ( int argc, char ** argv ) {
    const int n = 3;
    int arr[n] = {0, 1, 2};

    c_print_array_int(arr, n, 1);
    while (1) {
        if ( next_lex_perm(n, arr) ) {
            break;
        }
        c_print_array_int(arr, n, 1);
    }
    return 0;
}


int test01 ( int argc, char ** argv ) {
    const int n = 7;
    int arr[n] = {0, 1, 2, 5, 3, 3, 0};

    c_print_array_int(arr, n, 1);

    next_lex_perm(n, arr);
    c_print_array_int(arr, n, 1);
    next_lex_perm(n, arr);
    c_print_array_int(arr, n, 1);
    next_lex_perm(n, arr);
    c_print_array_int(arr, n, 1);
    next_lex_perm(n, arr);
    c_print_array_int(arr, n, 1);

    return 0;
}

/* ------------------------------------------------------ */

int factorial(int n){
    if ( n<2 ) {
        return 1;
    }
    return n * factorial(n-1);
}

static int find_k(int n, int * a ) {
    /* Find the first non-ascending number starting at the end of the array */
    int k = n-1;
    while ( k>0 ) {
        if (a[k-1] < a[k] ) {
            return k-1;
        }
        k--;
    }
    return -1;
}

static int find_m(int n, int * a, int k) {
    int m=n-1, a_k = a[k];
    
    while ( m>k ) {
        if ( a[m] > a_k ) {
            return m;
        }
        m--;
    }
    return -1;
}

static void swap(int * a, int k, int m) {
    int tmp = a[k];
    a[k] = a[m];
    a[m] = tmp;
}

static void reverse(int * a, int k, int n ){
    int half = (n-k)/2;
    int m;

    for ( m=0; m<half; ++m ) {
        swap(a, k+m, n-1-m);
    }
}

int next_lex_perm(int n, int * a) {
    static int cnt = 0;
    int k, m;

    /*
     * Starting at the end of the array, find the first non-ascending
     * element.  For example, if arr[n] = {0, 1, 2, 5, 3, 3, 0}, then
     * arr[2] = 2 is the first non-ascending element starting at arr[6].
     */
    k = find_k(n, a);
    if ( k<0 ) {
        reverse(a, 0, n);
        return 1;
    }

    /*
     * Starting at the end of the array, find the first element greater
     * than a[k].  For example, if arr[n] = {0, 1, 2, 5, 3, 3, 0}, k=2, 
     * therefore a[5] = 3 is the first element greater than a[2] = 2.
     */
    m = find_m(n, a, k);

    /* Swap a[k] and a[m] */
    swap(a, k, m);

    /* Reverse arr[k+1: n-1] */
    reverse(a, k+1, n);

    return 0;
}
