/* 
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

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

void print_mat (int arr_rows, int arr_columns, int** arr) {
    int k,m;

    for ( k=0; k<arr_rows; ++k ) {
        for ( m=0; m<arr_rows; ++m ) {
            printf("%5d ",arr[k][m]);
        }
        printf("\n");
    }
    printf("\n");
}

/*
 * Complete the 'diagonalDifference' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY arr as parameter.
 */

int diagonalDifference(int arr_rows, int arr_columns, int** arr) {
    int diag1=0, diag2=0, diff,tmp;
    int k, m;

    printf("\n");
    print_mat(arr_rows,arr_columns,arr);
    printf("\n");

    for ( k = 0; k < arr_rows; ++k ) {
        tmp = arr[k][k];
        diag1 += tmp;
        printf("arr[%d][%d] = %d\n",k,k,arr[k][k]);

        tmp = arr[k][arr_columns-1-k];
        diag2 += tmp;
        printf("arr[%d][%d] = %d\n",k,arr_columns-1-k,tmp);
    }

    diff = diag1 - diag2;
    printf("%d = %d - %d\n",diff,diag1,diag2);
    if ( diff < 0 ) {
        diff = -1 * diff;
    }
    printf("diff = %d\n",diff);

    exit(1);
    return diff;
}

int ** get_arr ( ) {
    int ** arr = calloc(3,sizeof(*arr));
    arr[0] = calloc(3,sizeof(*arr[0]));
    arr[1] = calloc(3,sizeof(*arr[0]));
    arr[2] = calloc(3,sizeof(*arr[0]));

    arr[0][0] = 11;
    arr[0][1] = 2;
    arr[0][2] = 4;

    arr[1][0] = 4;
    arr[1][1] = 5;
    arr[1][2] = 6;

    arr[2][0] = 10;
    arr[2][1] = 8;
    arr[2][2] = -12;

    return arr;
}

void free_arr ( int ** arr ) {
    free(arr[2]);
    free(arr[1]);
    free(arr[0]);
    free(arr);
}

int main ( ) {
    int ** arr = get_arr();

    diagonalDifference(3,3,arr);

    free_arr(arr);
    return 0;
}

int main_old()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    int** arr = malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        *(arr + i) = malloc(n * (sizeof(int)));

        char** arr_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < n; j++) {
            int arr_item = parse_int(*(arr_item_temp + j));

            *(*(arr + i) + j) = arr_item;
        }
    }

    int result = diagonalDifference(n, n, arr);

    fprintf(fptr, "%d\n", result);

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

