/*
https://www.hackerrank.com/challenges/counter-game/problem
 */

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

// Complete the counterGame function below.

// Please either make the string static or allocate on the heap. For example,
// static char str[] = "hello world";
// return str;
//
// OR
//
// char* str = "hello world";
// return str;
//
struct bt_cnt { 
    uint64_t p2;
    int shift;
};
int get_index01 ( long nn ) {
    uint64_t n = (uint64_t) nn;
    uint64_t t = n,one;
    int idx;
    int num = 0, k;
    struct bt_cnt bc[6] = { { 0xffffffffL, 32 }, { 0xffffL, 16 }, { 0xffL, 8 },
                            { 0xfL, 4 },         { 0x3L, 2 },     { 0x1L, 1 } };

    for ( k=0; k<6; ++k ) {
        if ( n > bc[k].p2 ) {
            num += bc[k].shift;
            n = (n >> bc[k].shift) & bc[k].p2;
        }
    }

    idx = num & 1;
    printf("0x%016llx -> num = %d, idx = %d\n",t,num,idx);
    one = 1L << num;
    printf("0x%016llx\n",one);

    return idx;
}

int get_index02 ( long nn ) {
    uint64_t n = (uint64_t)nn;
    uint64_t p2 = 1;
    int idx = 1;

    while ( (2*p2)<n ) {
        p2 *= 2;
    }
    n = p2;
    idx ^= 1;
    if ( 1==n ) {
        return idx;
    }
    while ( n>1 ) {
        n /= 2;
        idx ^= 1;
    }

    return idx;
}

char* counterGame(long nn ) {
    static char * names[2] = { "Richard", "Louise" };
    int idx;

    if ( 1==nn ) {
        return names[0];
    }

    idx = get_index01(nn);
    
    return names[idx];
} 

#if 0
1560834904
1768820483
1533726144
1620434450
1463674015

Richard
Richard
Louise
Richard
Louise
#endif

int main ( ) {
    printf("%s\n\n",counterGame(1560834904L));
    printf("%s\n\n",counterGame(1768820483L));
    printf("%s\n\n",counterGame(1533726144L));
    printf("%s\n\n",counterGame(1620434450L));
    printf("%s\n\n",counterGame(1463674015L));

    return 0;
}

#if 0
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* t_endptr;
    char* t_str = readline();
    int t = strtol(t_str, &t_endptr, 10);

    if (t_endptr == t_str || *t_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char* n_endptr;
        char* n_str = readline();
        long n = strtol(n_str, &n_endptr, 10);

        if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

        char* result = counterGame(n);

        fprintf(fptr, "%s\n", result);
    }

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}
#endif
