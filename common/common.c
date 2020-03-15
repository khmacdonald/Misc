#include <stdio.h>

#include "common.h"

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

#if 0
void print_array_bytes_old ( uint8_t * b, int n, int new_line ) {
    int k;
    if ( NULL==b || n<1 ) {
        return;
    }
    printf("(%02x",b[0]);
    for ( k=1; k<n; ++k ) {
        printf(" %02x",b[k]);
    }
    printf(")");
    for ( k=0; k<new_line; ++k ) {
        printf("\n");
    }
    return;
}

void print_array_int_old ( int32_t * b, int n, int new_line ) {
    int k;
    if ( NULL==b || n<1 ) {
        return;
    }
    printf("(%d",b[0]);
    for ( k=1; k<n; ++k ) {
        printf(" %d",b[k]);
    }
    printf(")");
    for ( k=0; k<new_line; ++k ) {
        printf("\n");
    }
    return;
}
#endif
