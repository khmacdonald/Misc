/*
https://www.hackerrank.com/challenges/extra-long-factorials/problem
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

void big_mul ( int * f, int sz, int x ) {
    int k, tmp, carry=0;

    for ( k=0; k<sz; ++k ) {
        tmp = carry + f[k] * x;
        f[k] = tmp % 10;
        carry = tmp/10;
    }
    return;

}

// Complete the extraLongFactorials function below.
#define FSZ 256
void extraLongFactorials(int n) {
    int fact[FSZ] = {0};
    int k;

    memset(fact,0,100*sizeof(fact[0]));
    fact[0] = 1;
    for ( k=2; k<=n; ++k ) {
        big_mul(fact,FSZ,k);
    }
    k = FSZ-1;
    while ( 0==fact[k] ) {
        k--;
    }
    for ( ; k>=0; k-- ) {
        printf("%d",fact[k]);
    }
    printf("\n");

}

int main ( int argc, char ** argv ) {
    int n = 25; /* 15511210043330985984000000 */
                /* 15511210043330985984000000 */

    if ( 1<argc ) {
        n = atoi(argv[1]);
    }
    extraLongFactorials(n);
    if ( 77==n ) {
        printf("145183092028285869634070784086308284983740379224208358846781574688061991349156420080065207861248000000000000000000\n");
    } else if ( 25==n ) {
        printf("15511210043330985984000000\n");
    }
}

#if 0
int main()
{
    char* n_endptr;
    char* n_str = readline();
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    extraLongFactorials(n);

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
