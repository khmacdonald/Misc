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
char** split_string(char*);

// Complete the serviceLane function below.

// Please store the size of the integer array to be returned in 
//    result_count pointer. For example,
// int a[3] = {1, 2, 3};
//
// *result_count = 3;
//
// return a;
//

int* serviceLane(
        int n, 
        int cases_rows, 
        int cases_columns, 
        int** cases, 
        int* result_count) {


}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** nt = split_string(readline());

    char* n_endptr;
    char* n_str = nt[0];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { 
        exit(EXIT_FAILURE); 
    }

    char* t_endptr;
    char* t_str = nt[1];
    int t = strtol(t_str, &t_endptr, 10);

    if ( t_endptr == t_str || *t_endptr != '\0') { 
        exit(EXIT_FAILURE); 
    }

    char** width_temp = split_string(readline());

    int* width = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        char* width_item_endptr;
        char* width_item_str = *(width_temp + i);
        int width_item = strtol(width_item_str, &width_item_endptr, 10);

        if ( width_item_endptr == width_item_str || 
             *width_item_endptr != '\0') { 
            exit(EXIT_FAILURE); 
        }

        *(width + i) = width_item;
    }

    int** cases = malloc(t * sizeof(int*));

    for (int i = 0; i < t; i++) {
        *(cases + i) = malloc(2 * (sizeof(int)));

        char** cases_item_temp = split_string(readline());

        for (int j = 0; j < 2; j++) {
            char* cases_item_endptr;
            char* cases_item_str = *(cases_item_temp + j);
            int cases_item = strtol(cases_item_str, &cases_item_endptr, 10);

            if ( cases_item_endptr == cases_item_str || 
                 *cases_item_endptr != '\0') { 
                exit(EXIT_FAILURE); 
            }

            *(*(cases + i) + j) = cases_item;
        }
    }

    int cases_rows = t;
    int cases_columns = 2;

    int result_count;
    int* result = serviceLane(n, cases_rows, cases_columns, cases, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

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
