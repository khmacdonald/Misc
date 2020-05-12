/*
https://practice.geeksforgeeks.org/problems/largest-number-formed-from-an-array/0

From an array of number, permute so that the concatenated string of numbers
form a string representing the largest number possible from the numbers
in the array.

3, 30, 34, 5, 9 -> 9534330
54, 546, 548, 60 -> 6054854654
*/

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/common.h"
#include "../common/print_statements.h"
#include "../math/brand.h"

struct dig { 
    int n;
    int arr[4];
    int sz;
};

void get_dig ( struct dig * d, int n ) ;
int lex_cmp ( const void * aa, const void * bb ) ;
void print_dig ( struct dig * d ) ;
void random_array ( int * arr, int n );


void test_case ( int * arr, int sz ) ;

/* ------------------------------------------- */
int main ( int argc, char ** argv ) {
    int t1[5] = { 3, 30, 34, 5, 9 };
    long a1 = 9534330;
    int t2[4] = { 54, 546, 548, 60 };
    long a2 = 6054854654L;

    test_case(t1,5);
    printf(" -> %ld\n",a1);

    test_case(t2,4);
    printf(" -> %ld\n",a2);


    return 0;
}
int test_main ( int argc, char ** argv ) {
    int n = 10;
    int * arr = NULL;

    if ( 1<argc ) {
        n = atoi(argv[1]);
    }
    arr = calloc(n,sizeof(*arr));
    dbg_print("n = %d\n",n);
    random_array(arr,n);
    dbg_print("arr = ");
    c_print_array_int(arr,n,1);

    return 0;
}

/* ------------------------------------------- */
void random_array ( int * arr, int n ) {
    int k;
    brand_t b;
    brand_seed_init(b);

    brand_array((uint32_t*)arr,n,b);
    for ( k=0; k<n; ++k ) {
        arr[k] = arr[k] & 0x7fffffff;
        arr[k] = arr[k] % 1000;
    }
}

int lex_cmp ( const void * aa, const void * bb ) {
    int a = *((int*)aa);
    int b = *((int*)bb);
    struct dig ad, bd;
    int k, min;

    get_dig(&ad,a);
    get_dig(&bd,b);

    min = (ad.sz<bd.sz) ? ad.sz : bd.sz;

    for ( k=0; k<min; ++k ) {
        if ( ad.arr[k] > bd.arr[k] ) {
            return -1;
        } else if ( ad.arr[k] < bd.arr[k] ) {
            return 1;
        }
    }

    if ( ad.sz > bd.sz ) {
        for ( k=min; k<ad.sz; ++k ) {
            if ( ad.arr[0] > ad.arr[k] ) {
                return -1;
            }
        }
        return 1;
    } else if ( ad.sz < bd.sz ) {
        for ( k=min; k<bd.sz; ++k ) {
            if ( bd.arr[0] > bd.arr[k] ) {
                return -1;
            }
        }
        return 1;
    }

    return 0;
}

void get_dig ( struct dig * d, int n ) {
    int idx;

    memset(d,0,sizeof(*d));

    d->n = n;

    if ( n>999 ) {
        d->sz = 4;
        idx = 3;
    } else if ( n>99 ) {
        d->sz = 3;
        idx = 2;
    } else if ( n > 9 ) {
        d->sz = 2;
        idx = 1;
    } else {
        d->sz = 1;
        idx = 0;
    }

    while ( n > 0 ) {
        d->arr[idx--] = n % 10;
        n = n / 10;
    }
}

void print_dig ( struct dig * d ) {
    int k;

    printf("[%d] { %d",d->n,d->arr[0]);
    for ( k=1; k<d->sz; ++k ) {
        printf(", %d",d->arr[k]);
    }
    printf("}\n");
    
}

void test_case ( int * arr, int sz ) {
    c_print_array_int(arr,sz,0);
    qsort(arr,sz,sizeof(arr[0]),lex_cmp);
    printf(" -> ");
    c_print_array_int(arr,sz,0);
}

