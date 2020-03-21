/*
https://www.hackerrank.com/challenges/sorting-array-of-strings/problem
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/print_statements.h"

#define N 4
//typedef int (*cmp_t)(const char *, const char *);
typedef int (*cmp_t)(char *, char *);

int lex ( char *, char *);
int lex_rev ( char *, char *);
int nchar ( char *, char *);
int lchar ( char *, char *);
void string_sort ( char ** arr, const int len, cmp_t cmp_func );

char ** set_strings ( );
void destroy_strings ( char ** s );
void test ( int (*cmp)(char*,char*), char * name );

/* ----------------------------------------------------------------- */
int level=0;
int main ( ) {
    test(lex,"lex");
    test(lex_rev,"lex_rev");
    test(nchar,"nchar");
    test(lchar,"lchar");

    return 0;
}
/* ----------------------------------------------------------------- */

void test ( int (*cmp)(char*,char*), char * name ) {
    static int first = 1;
    char ** s = set_strings();
    int k;

    if ( first ) {
        printf("-----------------------------------------------------------------\n");
        for ( k=0; k<N; ++k ) {
            printf("%s, ",s[k]);
        }
        printf("\n-----------------------------------------------------------------\n");
        first = 0;
    }
    printf("-----------------------------------------------------------------\n");
    printf("    Test: %s\n",name);
    string_sort(s,N,cmp);

    for ( k=0; k<N; ++k ) {
        printf("%s\n",s[k]);
    }
    printf("-----------------------------------------------------------------\n\n");

    destroy_strings(s);
}

char ** set_strings ( ) {
    char ** s = calloc(N,sizeof(*s));

    s[0] = calloc(1,10);
    snprintf(s[0],10,"wkue");

    s[1] = calloc(1,10);
    snprintf(s[1],10,"qoi");

    s[2] = calloc(1,10);
    snprintf(s[2],10,"sbv");

    s[3] = calloc(1,10);
    snprintf(s[3],10,"fekls");

    return s;
}

void destroy_strings ( char ** s ) {
    int k;

    for ( k=0; k<N; ++k ) {
        free(s[k]);
    }
    free(s);
    
    return;
}

int lex ( char * s1, char * s2 ) {
    return strcmp(s2,s1);;
}

int lex_rev ( char * s1, char * s2 ) { 
    return strcmp(s1,s2);;
}

int get_num_chars ( char * s ) {
    int k, num=0, slen;
    int ch[26];

    memset(ch,0,26*sizeof(ch[0]));
    slen = strlen(s);
    for ( k=0; k<slen; ++k ) {
        if ( 'a'<=s[k] && s[k]<='z' ) {
            ch[s[k]-'a']++;
        }
    }
    for ( k=0; k<26; ++k ) {
        if ( ch[k]>0 ) {
            num++;
        }
    }

    return num;
}

int nchar ( char * s1, char * s2 ) {
    int n1 = get_num_chars(s1); 
    int n2 = get_num_chars(s2); 

    if ( n1==n2 ) {
        return strcmp(s2,s1);
    }
    return n2-n1;;
}

int lchar ( char * s1, char * s2 ) {
    if ( strlen(s1)==strlen(s2) ) {
        return strcmp(s2,s1);
    }
    return strlen(s2)-strlen(s1);;
}

void swap ( char ** arr, int m, int k ) {
    char * tmp = arr[m];
    arr[m] = arr[k];
    arr[k] = tmp;
}

void string_sort ( char ** arr, const int n, cmp_t cmp_func ) {
    char * tmp = NULL;
    int k,m,min_idx;

    for ( k=0; k<n-1; ++k ) {
        min_idx = k;
        for ( m=k+1; m<n; ++m ) {
            if ( cmp_func(arr[min_idx],arr[m])<0 ) {
                min_idx = m;
            }
        }
        swap(arr,k,min_idx);
    }
}

