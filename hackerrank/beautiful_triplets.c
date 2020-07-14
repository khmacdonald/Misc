#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Getting a run time error on the site, but I am getting the 
 * correct answers here.
 * I'm assuming this is solved.  I lose more and more faith in 
 * the capabilities of the hackerrank coding challenge writers.
 */

char* readline();
char** split_string(char*);

// Complete the beautifulTriplets function below.
int beautifulTriplets(int d, int arr_count, int* arr) {
    int k, m, n, diff;
    int count = 0;

    for ( k=0; k<arr_count-2; ++k ) {
        for ( m=k+1; k<arr_count-1 && (arr[m]-arr[k] <= d); ++m ) {
            diff = arr[m] - arr[k];
            if ( d!=diff ) {
                continue;
            }
            for ( n=m+1; m<arr_count && (arr[n]-arr[m] <= d); ++n ) {
                diff = arr[n] - arr[m];
                if ( diff==d ) {
                    count++;
                    break;
                }
            } /* For n */
        } /* For m */
    } /* For k */

    return count;
}

void test01 ( ) {
    const int n = 7;
    const int d = 3;
    int a[n] = { 1, 2, 4, 5, 7, 8, 10 };
    int count = beautifulTriplets(d,n,a);

    printf("[%d:%s] count = %d\n",__LINE__,__FUNCTION__,count);
}

void test02 ( ) {
    const int n = 10;
    const int d = 3;
    int a[n] = { 1, 6, 7, 7, 8, 10, 12, 13, 14, 19 };
    int count = beautifulTriplets(d,n,a);

    printf("[%d:%s] count = %d\n",__LINE__,__FUNCTION__,count);
}

int main ( int argc, char ** argv ) {
    test01();
    test02();
}

#if 0
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** nd = split_string(readline());

    char* n_endptr;
    char* n_str = nd[0];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* d_endptr;
    char* d_str = nd[1];
    int d = strtol(d_str, &d_endptr, 10);

    if (d_endptr == d_str || *d_endptr != '\0') { exit(EXIT_FAILURE); }

    char** arr_temp = split_string(readline());

    int* arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        char* arr_item_endptr;
        char* arr_item_str = *(arr_temp + i);
        int arr_item = strtol(arr_item_str, &arr_item_endptr, 10);

        if (arr_item_endptr == arr_item_str || *arr_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(arr + i) = arr_item;
    }

    int arr_count = n;

    int result = beautifulTriplets(d, arr_count, arr);

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
#endif
