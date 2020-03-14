#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ( ) {
    char c;
    int dig[10] = {0};
    int k;

    memset(dig,0,10*sizeof(dig[0]));

    while ( EOF!=(c=fgetc(stdin)) ) { 
        if ( '\n'==c ) {
            break;
        } else if ( '0'<=c && c<='9' ) {
            dig[c-'0']++;
        }
    }

    for ( k=0; k<10; ++k ) {
        printf("%d ",dig[k]);
    }
    printf("\n");

    return 0;
}
