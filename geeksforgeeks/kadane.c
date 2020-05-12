/*
https://practice.geeksforgeeks.org/problems/count-the-triplets/0

Count all the triples in an array such that the sum of two of the 
numbers equals the third.
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void test_case ( int * arr, int sz ) ;

/* ------------------------------------------- */
int main ( int argc, char ** argv ) {
    int t1[5] = { 1, 2, 3, -2, 5 };
    int t2[4] = { -1, -2, -3, -4 };

    test_case(t1,5);
    test_case(t2,4);

    return 0;
}

/* ------------------------------------------- */

void test_case ( int * a, int sz ) {
    int max = INT_MIN;
    int sum;
    int k, m;

    for ( k=0; k<sz-1; k++ ) {
        sum = a[k];
        if ( sum>max ) {
            max = sum;
        }
        for ( m=k+1; m<sz; ++m ) {
            sum += a[m];
            if ( sum>max ) {
                max = sum;
            }
        }
        //printf("k = %d; sum = %d\n",k,sum);
    }

    printf("%d\n",max);

    return;
}
