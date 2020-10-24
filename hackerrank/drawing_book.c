#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
number of pages is 59867
page number is     35733
expected return is 12067
#endif

char* readline();

/*
 * Complete the pageCount function below.
 */
int pageCount(int n, int p) {
    /*
     * Write your code here.
     */
    int m = n-p;
    int odd = n%1;

    if ( p < m ) { /* p is closer to the front of the book */
        if ( 1==p ) {
            return 0;
        } else {
            return p/2;
        }
    } else { /* p is closer to the back of the book */
        if ( !odd ) {
            return m/2;
        } else {
            return (m+1)/2;
        }
    }

}

int main ( int argc, char ** argv ) {
    int n = 59867;
    int p = 35733;
    int e = 12067;
    int ret = 0;

    if ( 3<argc ) {
        n = atoi(argv[1]);
        p = atoi(argv[2]);
        e = atoi(argv[3]);
    }
    ret = pageCount(n,p);
    printf("For n = %d and p = %d, ret = %d\n",n,p,ret);
    printf("Expected ret to be %d\n",e);

    return 0;
}

#if 0
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* n_endptr;
    char* n_str = readline();
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* p_endptr;
    char* p_str = readline();
    int p = strtol(p_str, &p_endptr, 10);

    if (p_endptr == p_str || *p_endptr != '\0') { exit(EXIT_FAILURE); }

    int result = pageCount(n, p);

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
#endif
