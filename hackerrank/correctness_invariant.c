#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

void print_array ( int n, int * a ) {
    int k;

    if ( n<1 ) {
        return;
    }

    printf("%d", a[0]);
    for ( k=1; k<n; ++k ) {
        printf(" %d", a[k]);
    }
    printf("\n");
}


void insertionSort(int N, int arr[]) {
    int i,j;
    int value;
    for(i=1;i<N;i++)
    {
        value=arr[i];
        j=i-1;
        while(j>=0 && value<arr[j])
        {
            arr[j+1]=arr[j];
            j=j-1;
        }
        arr[j+1]=value;
    }
    print_array(N,arr);
}


int main(void) {
    const int n = 6;
    int a[n] = {4, 1, 3, 5, 6, 2};

    print_array(n,a);
    printf(" --->\n");
    insertionSort(n, a);

    return 0;
}

