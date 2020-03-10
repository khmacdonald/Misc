/* https://www.hackerrank.com/challenges/printing-pattern-2/problem */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_level ( int n, int level ) {
    int half = n/2,k;
    for ( k=n; k>=1; k-- ) {
        if ( k>level ) {
            printf("%d ",k);
        } else {
            printf("%d ",level);
        }
    }
    for ( k=2; k<=n; k++ ) {
        if ( k>level ) {
            printf("%d ",k);
        } else {
            printf("%d ",level);
        }
    }
    printf("\n");
}

void print_pattern ( int n ) {
    int k;

    for ( k=n; k>=1; k-- ) {
        print_level(n,k);
    }
    for ( k=2; k<=n; ++k ) {
        print_level(n,k);
    }
}

int main ( void ) {
    int n;

    scanf("%d",&n);
    print_pattern(n);

    return 0;
}
