/*
https://www.hackerrank.com/challenges/sorting-array-of-strings/problem
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

int lex ( char *, char *);
int lex_rev ( char *, char *);
int nchar ( char *, char *);
int lchar ( char *, char *);
void string_sort ( 
        char ** arr, 
        const int len, 
        int (*cmp_func)(const char *, const char *) );

char ** set_strings ( );
void destroy_strings ( char ** s );
void test ( int (*cmp)(char*,char*) );

int main ( ) {

    test(lex);
    test(lex_rev);
    test(nchar);
    test(lchar);

    return 0;
}

void test ( int (*cmp)(char*,char*) ) {
    char ** s = set_strings();
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
    return strcmp(s1,s2);;
}

int lex_rev ( char * s1, char * s2 ) { 
    return strcmp(s2,s1);;
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

    return n1-n2;;
}

int lchar ( char * s1, char * s2 ) {
    return strlen(s1)-strlen(s2);;
}

void string_sort ( 
        char ** arr, 
        const int len, 
        int (*cmp_func)(const char *, const char *) ) {

}

