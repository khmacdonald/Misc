#include "algos_common.h"

void a_print_arr_bool ( bool * arr, int n, int ret_ln ) {
    int k;
    if ( !arr || n<1 ) {
        return;
    }

    printf("( %d",arr[0]);
    for ( k=1; k<n; ++k ) {
        printf(", %d",arr[k]);
    }
    printf(" )");
    for ( ; ret_ln>0; ret_ln-- ) {
        printf("\n");
    }
}

void a_print_arr_int ( int * arr, int n, int ret_ln ) {
    int k;
    if ( !arr || n<1 ) {
        return;
    }

    printf("( %d",arr[0]);
    for ( k=1; k<n; ++k ) {
        printf(", %d",arr[k]);
    }
    printf(" )");
    for ( ; ret_ln>0; ret_ln-- ) {
        printf("\n");
    }
}


