#include <ctype.h>
#include <stdio.h>
#include <string.h>

int is_palindrome( const char * str ) ;

int main ( int argc, char ** argv ) {
    if ( 2!=argc ) {
        printf("Usage: %s <string to check as palidrome>\n",argv[0]);
        return 0;
    }
    if ( is_palindrome(argv[1]) ) {
        printf("Palindrome: True\n");
    } else {
        printf("Palindrome: False\n");
    }

    return 0;
}


int is_palindrome( const char * str ) {
    int slen = strlen(str);
    int hlen = slen/2;
    int k;
    char c1, c2;

    for ( k=0; k<=hlen; ++k ) {
        c1 = tolower(str[k]);
        c2 = tolower(str[slen-1-k]);
        if ( c1!=c2 ) {
            return 0;
        }
    }

    return 1;
}
