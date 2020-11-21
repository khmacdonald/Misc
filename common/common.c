#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "common.h"
#include "print_statements.h"

/**
 * @brief Creates an array of n random integers modulo some number.
 */
int * c_random_array ( int n,           /**< The length of the array. */
                       int positive,    /**< Force the integer to be positive */
                       int mod ) {      /**< Compute modulus */
    int * arr = calloc(n,sizeof(*arr));
    int k, rnd;

    srand(time(NULL));

    for ( k=0; k<n; ++k ) {
        rnd = rand();
        if ( positive ) {
            rnd = rnd & 0x7fffffff; /* Get rid of the negative sign */
        }
        if ( mod ) {
            rnd = rnd % mod;    /* Compute modulus */
        }
        arr[k] = rnd;
    }

    return arr;
}

/**
 * @brief Creates an array of n random bytes.
 */
uint8_t * c_random_byte_array ( int n ) {   /**< The number of bytes */
    uint8_t * arr = calloc(1,sizeof(*arr));
    uint8_t * b = arr;
    uint32_t rnd;
    static int seeded = 0;

    if (!seeded) {
        seeded = 1;
        srand(time(NULL));
    }

    while ( n>=4 ) {    /* compute four bytes at a time */
        rnd = (uint32_t)rand();
        memcpy(b,&rnd,4);
        b += 4;
        n -= 4;
    }
    if ( n ) {   /* Handle the remainder */
        rnd = rand();
        memcpy(b,&rnd,n);
    }

    return arr;
}

/**< Define a type value */
typedef enum { type_byte, type_int } type_t;

/**
 * @brief A generic function to wrap to print types.
 */
static void print_type ( void * b,              /**< Pointer to array */
                         int idx,               /**< Index into array */
                         type_t type ) {        /**< Type of array */
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

/**
 * @brief A generic function to wrap to print arrays. 
 */
static void print_array_gen ( void * b,         /**< The pointer to the array */
                              int n,            /**< The length of the array */
                              type_t type,      /**< The type of array */
                              int new_line) {   /**< The number of new lines to print */
    int k;

    printf("(");
    print_type(b,0,type);       /* Handle type print */
    for ( k=1; k<n; ++k ) {
        printf(", ");
        print_type(b,k,type);   /* Handle type print */
    }
    printf(")");

    /* Print the requested number of return lines */
    for ( k=0; k<new_line;++k ) {
        printf("\n");
    }
}

/**
 * @brief Print an array of bytes 
 */
void c_print_array_bytes ( uint8_t * b,         /**< The pointer to the array */
                           int n,               /**< The length of the array */
                           int new_line ) {     /**< The number of return lines to print */
    print_array_gen(b,n,type_byte,new_line);
}

/**
 * @brief Print an array of bytes 
 */
void c_print_array_int ( int * b,               /**< The pointer to the array */
                         int n,                 /**< The length of the array */
                         int new_line ) {       /**< The number of return lines to print */
    print_array_gen(b,n,type_int,new_line);
}

/**
 * @brief Print an array with a label.
 */
void c_print_array_int_lbl ( char * label,      /**< The array label */
                             int * b,           /**< The pointer to the array */
                             int n,             /**< The length of the array */
                             int new_line ) {   /**< The number of return lines to print */
    if ( NULL!=label ) {
        printf("%s = ",label);
    }
    c_print_array_int(b,n,new_line);
}

/**
 * @brief Revrse the bytes of an array.
 */
void c_reverse_bytes ( uint8_t * b,     /**< The pointer to the array */
                       int n ) {        /**< The length of the array */
    int half = n/2;
    int k;
    uint8_t tmp;

    for ( k=0; k<half; ++k ) {
        /* Swap opposite pairs */
        tmp = b[k];
        b[k] = b[n-1-k];
        b[n-1-k] = tmp;
    }
}

/**
 * @brief Prints commas for an integer to a stream.
 */
void c_print_formated_integer ( FILE * fd,   /**< The stream to print to */
                                int x ) {    /**< The number to print */
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
#define print_test printf(" *** %s ***\n",__FUNCTION__); 
void c_unit_test_random_array ( void ) {
    const int n = 3;
    int * rnd = NULL;
    int size[n] = {1, 4, 9};
    int mod[n] = {100, 256, 53452};
    int k, p = 0, start, end;

    print_test;

    start = 0;
    end = n;
    for ( k=start; k<end; ++k ) {
        rnd = c_random_array(size[k], p, mod[k]); 
        if ( NULL == rnd ) {
            dbg_print("rnd = NULL\n");
        } else {
            dbg_print("Size = %d, p = %d, Modulus = %d\n",size[k], p, mod[k]);
            c_print_array_int(rnd, size[k], 2);
        }

        SET_FREE(rnd);
        p ^= 1;
    }
}

void c_unit_test_array_bytes ( void ) {
    const int n = 3;
    uint8_t * rnd = NULL;
    int size[n] = {1, 4, 9};
    int k, start, end;

    print_test;

    start = 0;
    end = n;
    for ( k=start; k<end; ++k ) {
        rnd = c_random_byte_array(size[k]);
        if ( NULL == rnd ) {
            dbg_print("rnd = NULL\n");
        } else {
            dbg_print("Size = %d\n",size[k]);
            c_print_array_bytes(rnd, size[k], 2);
        }

        SET_FREE(rnd);
    }
}

void c_unit_test_array_int ( int argc, char ** argv ) {
}

void c_unit_test_array_int_lbl ( int argc, char ** argv ) {
}

void c_unit_test_reverse_bytes ( int argc, char ** argv ) {

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









