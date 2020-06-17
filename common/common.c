#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"

int * c_random_array ( int n, int positive, int mod ) {
    int * arr = calloc(n,sizeof(*arr));
    int k, rnd;

    srand(time(NULL));

    for ( k=0; k<n; ++k ) {
        if ( positive ) {
            rnd = rand() & 0x7fffffff;
        }
        if ( mod ) {
            rnd = rnd % mod;
        }
        arr[k] = rnd;
    }

    return arr;
}

typedef enum { type_byte, type_int } type_t;

static void print_type ( void * b, int idx, type_t type ) {
    switch(type) {
        case type_byte:
            printf("%02x",((uint8_t*)b)[idx]);
            return;
        case type_int:
            printf("%d",((int*)b)[idx]);
            return;
    }
    return;
}

static void print_array_gen ( void * b, int n, type_t type, int new_line) {
    int k;

    printf("(");
    print_type(b,0,type);
    for ( k=1; k<n; ++k ) {
        printf(", ");
        print_type(b,k,type);
    }
    printf(")");
    for ( k=0; k<new_line;++k ) {
        printf("\n");
    }
}

void c_print_array_bytes ( uint8_t * b, int n, int new_line ) {
    print_array_gen(b,n,type_byte,new_line);
}

void c_print_array_int ( int * b, int n, int new_line ) {
    print_array_gen(b,n,type_int,new_line);
}

void c_print_array_int_lbl ( char * label, int * b, int n, int new_line ) {
    if ( NULL!=label ) {
        printf("%s = ",label);
    }
    c_print_array_int(b,n,new_line);
}

void c_print_formated_integer ( FILE * fd, int x ) {
    int d[4];
    int idx=0;

    if ( 0==x ) {
        fprintf(fd,"0");
        return;
    }
    while ( x && idx<4 ) {
        d[idx++] = x % 1000;
        x /= 1000;
    }
    fprintf(fd,"%d",d[idx-1]);
    for ( idx = idx-1; idx>0; idx-- ) {
        fprintf(fd,",%d",d[idx-1]);
    }
}


/* Unit tests */
void c_unit_test_random_array ( int argc, char ** argv ) {
}

void c_unit_test_array_bytes ( int argc, char ** argv ) {
}

void c_unit_test_array_int ( int argc, char ** argv ) {
}

void c_unit_test_array_int_lbl ( int argc, char ** argv ) {
}

void c_unit_test_print_formated_integer ( int argc, char ** argv ) {
    printf("0       = ");
    c_print_formated_integer(stdout,0);
    printf("\n");

    printf("2**8    = ");
    c_print_formated_integer(stdout,1<<8);
    printf("\n");

    printf("2**16   = ");
    c_print_formated_integer(stdout,1<<16);
    printf("\n");

    printf("2**24   = ");
    c_print_formated_integer(stdout,1<<24);
    printf("\n");

    printf("2**31-1 = ");
    c_print_formated_integer(stdout,0x7fffffff);
    printf("\n");
}









