#include <stdio.h>

#include "common.h"
#include "lex_perm.h"
#include "print_statements.h"

int test01(int argc, char ** argv);
int test02(int argc, char ** argv);
int test03(int argc, char ** argv);

/* ------------------------------------------------------ */

int main ( int argc, char ** argv ) {
    test03(argc, argv);
}

/* ------------------------------------------------------ */

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
