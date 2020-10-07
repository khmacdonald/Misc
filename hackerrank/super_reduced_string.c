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


// Complete the superReducedString function below.

/*
 * To return the string from the function, you should either do 
   static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */

int level;
char* superReducedString(char* s) {
    int slen = strlen(s);
    char * ss = calloc(1,slen);
    static char * ans = "Empty String";
    int k, sidx=0;

    level++;
    for ( k=0; k<slen; ) {
        if ( k==slen-1 ) {
            ss[sidx] = s[k];
            sidx++;
            ss[sidx] = '\0';
            break;
        }
        if ( s[k]==s[k+1] ) {
            k += 2;
        } else {
            ss[sidx++] = s[k];
            k++;
        }
    }

END:
    if ( 0==sidx ) {
        return ans;
    } else if ( sidx<slen ) {
        return superReducedString(ss);
    } else {
        return ss;
    }
}

void base_test ( char * test, char * e ) {
    char * s = superReducedString(test);

    level = 0;
    printf("Original = %s\n",test);
    printf("Computed = %s\n",s);
    printf("Expected = %s\n",e);
}


void test01() {
    char * test = "aaabccddd";
    char * expected = "abd";

    base_test(test,expected);
}

int main()
{
    test01();
    return 0;
}
