/*
https://www.hackerrank.com/challenges/apple-and-orange/problem
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
char** split_string(char*);

// Complete the countApplesAndOranges function below.
void countApplesAndOranges(int s, int t, int a, int b,
        int apples_count, int* apples,
        int oranges_count, int* oranges) {
    int k, acnt=0,ocnt=0, loc;

    printf("s = %d, t = %d\n",s,t);
    printf("a = %d, b = %d\n",a,b);
    /* Count apples */
    for ( k=0; k<apples_count; ++k ) {
        loc = a + apples[k];
        printf("    Apple Location: %d (%d)",loc,apples[k]);
        if ( s<=loc && loc<=t) {
            printf(" - on house");
            acnt++;
        }
        printf("\n");
    }

    /* Count oranges */
    for ( k=0; k<oranges_count; ++k ) {
        loc = b + oranges[k];
        printf("    Orange Location: %d (%d)",loc,oranges[k]);
        if ( s<=loc && loc<=t ) {
            printf(" - on house");
            ocnt++;
        }
        printf("\n");
    }
    printf("%d\n",acnt);
    printf("%d\n",ocnt);
}

#if 0
Wrong Answer
Input (stdin)
Download
2 3
1 5
1 1
2
-2
Expected Output
Download
1
1
#endif
typedef void (*test_t)(void);
void test1 ( void ) {
    int s=2, t=3;
    int a=1, b=5;
    int asz = 1, osz = 1;
    int apples[1] = {2};
    int oranges[1] = {-2};

    /* Expect 1 1 */
    //printf("    Test: %s\n",__FUNCTION__);
    countApplesAndOranges(s,t,a,b,asz,apples,osz,oranges);
}

void test2 ( void ) {
    int s=7, t=11;
    int a=5, b=15;
    int asz = 3, osz = 2;
    int apples[3] = {-2, 2, 1};
    int oranges[2] = {5, -6};

    /* Expect 1 1 */
    //printf("    Test: %s\n",__FUNCTION__);
    countApplesAndOranges(s,t,a,b,asz,apples,osz,oranges);
}

#define NTESTS 2
int main() {
    int k;
    test_t tfuncs[NTESTS] = { test1, test2 };

    for ( k=0; k<NTESTS; ++k ) {
        tfuncs[k]();
        if ( k<NTESTS-1 ) {
            printf("-----------\n");
        }
    }

    return 0;
}

int main_old()
{
    char** st = split_string(readline());

    char* s_endptr;
    char* s_str = st[0];
    int s = strtol(s_str, &s_endptr, 10);

    if (s_endptr == s_str || *s_endptr != '\0') { exit(EXIT_FAILURE); }

    char* t_endptr;
    char* t_str = st[1];
    int t = strtol(t_str, &t_endptr, 10);

    if (t_endptr == t_str || *t_endptr != '\0') { exit(EXIT_FAILURE); }

    char** ab = split_string(readline());

    char* a_endptr;
    char* a_str = ab[0];
    int a = strtol(a_str, &a_endptr, 10);

    if (a_endptr == a_str || *a_endptr != '\0') { exit(EXIT_FAILURE); }

    char* b_endptr;
    char* b_str = ab[1];
    int b = strtol(b_str, &b_endptr, 10);

    if (b_endptr == b_str || *b_endptr != '\0') { exit(EXIT_FAILURE); }

    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** apples_temp = split_string(readline());

    int* apples = malloc(m * sizeof(int));

    for (int i = 0; i < m; i++) {
        char* apples_item_endptr;
        char* apples_item_str = *(apples_temp + i);
        int apples_item = strtol(apples_item_str, &apples_item_endptr, 10);

        if (apples_item_endptr == apples_item_str || *apples_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(apples + i) = apples_item;
    }

    int apples_count = m;

    char** oranges_temp = split_string(readline());

    int* oranges = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        char* oranges_item_endptr;
        char* oranges_item_str = *(oranges_temp + i);
        int oranges_item = strtol(oranges_item_str, &oranges_item_endptr, 10);

        if (oranges_item_endptr == oranges_item_str || *oranges_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(oranges + i) = oranges_item;
    }

    int oranges_count = n;

    countApplesAndOranges(s, t, a, b, apples_count, apples, oranges_count, oranges);

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

