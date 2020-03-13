#include <stdio.h>
#include <string.h>

void print_tokens ( char * s ) {
    char * c = s;
    int k,n = strlen(s);

    printf("\n%s -> \n",s);
    for ( k=0; k<n; ++k ) {
        if ( (n-1)==k ) {
            printf("%s\n",c);
            break;
        } else if ( ' '==s[k] ) {
            s[k] = '\0';
            printf("%s\n",c);
            c = s + k + 1;
        }
    }
    return;
}

int main ( ) {
    char s[1024];

    snprintf(s,1024,"This is C");
    print_tokens(s);
    snprintf(s,1024,"Learning C is fun");
    print_tokens(s);
    snprintf(s,1024,"How is that");
    print_tokens(s);

    return 0;
}
