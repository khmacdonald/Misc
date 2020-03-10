/* https://www.hackerrank.com/challenges/1d-arrays-in-c/problem */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_numbers ( int * arr, int n ) {
    char c;
    char number[5];
    int m=0, idx=0;

    memset(number,0,5);
    while ( 1 ) {
        c = fgetc(stdin);
        if ( c==' ' ) {
            arr[idx++] = atoi(number);
            memset(number,0,5);
            m = 0;
        } else if ( c=='\n' ) {
            arr[idx++] = atoi(number);
            memset(number,0,5);
            return;
        } else {
            number[m++] = c;
        }
    }
}

void print_array ( int * arr, int n ) {
    int k;
    printf("array = ");
    for ( k=0; k<n; ++k ) {
        printf("%d ",arr[k]);
    } 
    printf("\n");
}

int sum_numbers ( int * arr, int n ) {
    int sum = 0,k;

    for ( k=0; k<n; ++k ) {
        sum += arr[k];
    }
    return sum;
}

int main ( void ) {
    int n,k;
    int * arr = NULL;

    scanf("%d",&n);
    arr = malloc(n*sizeof(*arr));
    scanf("\n");
    get_numbers(arr,n);

    printf("%d\n",sum_numbers(arr,n));
    free(arr);

    return 0;
}
