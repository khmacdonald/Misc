#include <stdio.h>

#include "common.h"

static int  find_k  (int n, int * a );
static int  find_m  (int n, int * a, int k);
static void reverse (int * a, int k, int n );
static void swap    (int * a, int k, int m);

/* ------------------------------------------------------ */

/**
 * @brief Compute n!
 * 
 * @return Returns n!.  Could over flow.
 */
unsigned int lex_factorial(unsigned int n){ /**< The integer to compute n!. */
    if ( n<2 ) {
        return 1;
    }
    return n * lex_factorial(n-1);
}

/**
 * @brief Computes the next lexicographic permutation, in place.
 * 
 * @return TBD.
 */
perm_t next_lex_perm(int n,     /**< The length of the array. */
                     int * a) { /**< The array to permute. */
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

/* ------------------------------------------------------ */

/* Find the first non-ascending number starting at the end of the array */
static int find_k(int n, int * a ) {
    int k = n-1;
    while ( k>0 ) {
        if (a[k-1] < a[k] ) {
            return k-1;
        }
        k--;
    }
    return -1;
}

/* Find the first number greater than a[k] starting at the end of the array */
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

/* Swaps a[k] and a[m] */
static void swap(int * a, int k, int m) {
    int tmp = a[k];
    a[k] = a[m];
    a[m] = tmp;
}

/* Reverses the last n-k elements of an array:
   (a[0] ... a[k]   a[k+1] ... a[n-2] a[n-1]) 
-> (a[0] ... a[n-1] a[n-2] ... a[k+1] a[k]) */
static void reverse(int * a, int k, int n ){
    int half = (n-k)/2;
    int m;

    for ( m=0; m<half; ++m ) {
        swap(a, k+m, n-1-m);
    }
}
