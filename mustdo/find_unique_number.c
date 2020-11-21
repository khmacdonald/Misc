#include <stdio.h>

int unique_element ( int * arr, int n ) ;

int main ( int argc, char ** argv ) {
    int arr[11] = { 1, 1, 2, 2, 3, 3, 4, 50, 50, 65, 65 } ;
    int ans = unique_element(arr,11); 

    printf("%d\n",ans);
}

/* Finds the first unique element in a sorted integer array */
int unique_element ( int * arr, int n ) {
    int k;
    if ( 1==n ) {
        return arr[0];
    }
    if ( 2==n ) {
        return -1;
    }
    if ( arr[n-1]!=arr[n-2] ) {
        return arr[n-1];
    }
    if ( arr[0]!=arr[1] ) {
        return arr[0];
    }
    for ( k=1; k<n-1; ++k ) {
        if ( arr[k-1]!=arr[k] && arr[k]!=arr[k+1] ) {
            return arr[k];
        }
    }
    return -1;
}
