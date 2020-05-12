/*
https://practice.geeksforgeeks.org/problems/recursively-remove-all-adjacent-duplicates/0

Recursively remove all duplicate characters.  For example

geeksforgeek -> gksforgk
acaaabbbacdddd -> acac
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_case ( char * str );

/* ------------------------------------------- */
int main ( int argc, char ** argv ) {
    char * t1 = "geeksforgeek";
    char * t2 = "acaaabbbacdddd";
    char * t3 = "aacaaabbbacdddd";

    test_case(t1);
    test_case(t2);
    test_case(t);

    return 0;
}

/* ------------------------------------------- */

void recurse_remove ( char * str, char * rem ) {
    char c;
    if ( '\0'==*str ) {
        return;
    }
    if ( strlen(str)==1 ) {
        *rem = *str;
        return;
    }
    if ( str[0]==str[1] ) {
        c = str[0];
        str += 2;
        while ( c==*str ) {
            str++;
        }
    } else {
        *rem = *str;
        rem++;
        str++;
    }
    recurse_remove(str,rem);
}

void test_case ( char * str ) {
    int slen = strlen(str)+1;
    char * nstr = calloc(1,slen);

    recurse_remove(str,nstr);
    printf("%s -> %s\n",str,nstr);

    free(nstr);
    nstr = NULL;

    return;
}
