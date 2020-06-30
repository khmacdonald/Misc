/*
https://www.hackerrank.com/challenges/encryption/problem
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

// Complete the encryption function below.

// Please either make the string static or allocate on the heap. For example,
// static char str[] = "hello world";
// return str;
//
// OR
//
// char* str = "hello world";
// return str;
//
char* encryption(char* s) {
    int slen = strlen(s);
    double fl = floor(sqrt((double)slen));
    int row = (int)fl;
    int col = row;
    char * enc = NULL;
    int k,m,idx, eidx=0;

    if ( row*row!=slen ) {
        col++; /* slen is not a perfect square */
    }
    if ( row*col<slen ) {
        row++;
    }

    enc = calloc((row+1)*(row+1),sizeof(*enc));
    for ( k=0; k<col; ++k ) {
        for ( m=0; m<row && k+m*col<slen; ++m ) {
            idx = k+m*col;
            if ( idx < slen ) {
                enc[eidx++] = s[idx];
            }
        }
        enc[eidx++] = ' ';
    }
    enc[strlen(enc)-1] = '\0';

    return enc;
}

void test_base ( char * str, char * expected ) {
    char * enc = encryption(str);

    printf("Testing:  '%s'\n",str);
    printf("Computed: '%s'\n",enc);
    if ( expected ) {
        printf("Expected: '%s'\n",expected);
    }
}

void test01 ( ) {
    char * str = "chillout";
    char * expected = "clu hlt io";

    test_base(str,expected);
}

void test02 ( ) {
    char * str = "haveaniceday";
    char * expected = "hae and via ecy";

    test_base(str,expected);
}

void test03 ( ) {
    char * str = "feedthedog";
    char * expected = "fto ehg ee dd";

    test_base(str,expected);
}

int main ( ) {
    printf("\n------------------------------------------\n");
    test01();
    printf("------------------------------------------\n");
    test02();
    printf("------------------------------------------\n");
    test03();
    printf("------------------------------------------\n\n");
    return 0;
}

#if 0
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = encryption(s);

    fprintf(fptr, "%s\n", result);

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
