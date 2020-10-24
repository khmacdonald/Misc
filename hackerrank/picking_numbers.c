/*
https://www.hackerrank.com/challenges/picking-numbers/problem
*/

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define phere printf("[%d] Here\n",__LINE__)

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'pickingNumbers' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY a as parameter.
 */

int my_cmp ( const void * aa, const void * bb ) {
    int a = *((int*)aa);
    int b = *((int*)bb);

    return a-b;
}

int parr (int a_count, int* a) {
    int k;

    printf("(");
    for ( k=0; k<a_count; ++k ) {
        printf(" %d",a[k]);
    }
    printf(" )\n");

    return 0;
}

/*
 * I think this shouldn't work, but it does.
 */
int pickingNumbers(int a_count, int* a) {
    int max = 0, bcnt, diff, begin;
    int k;

    if ( 1>a_count ) {
        return 0;
    }

    qsort(a,a_count,sizeof(a[0]),my_cmp);
    //parr(a_count,a);
    
    begin = a[0];
    bcnt = 1;
    
    // 6
    // 4 6 5 3 3 1
    // Expected 3

    // 6
    // 1 2 2 3 1 2
    // Expected 5

    //100
    //66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66 66
    // Expected 100


    for ( k=1; k<a_count; ++k ) {
        diff = abs(begin-a[k]);
        if ( diff>1 ) {
            if ( bcnt>max ) {
                max = bcnt;
            }
            begin = a[k];
            bcnt = 1;
        } else {
            bcnt++;
        }
    }
    if ( bcnt>max ) {
        max = bcnt;
    }

    return max;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** a_temp = split_string(rtrim(readline()));

    int* a = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int a_item = parse_int(*(a_temp + i));

        *(a + i) = a_item;
    }

    int result = pickingNumbers(n, a);

    printf("%d\n",result);

    //fprintf(fptr, "%d\n", result);
    //fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            //data = '\0';
            data = NULL;

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            //data = '\0';
            data = NULL;
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            //data = '\0';
            data = NULL;
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        //return '\0';
        return NULL;
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        //return '\0';
        return NULL;
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}

