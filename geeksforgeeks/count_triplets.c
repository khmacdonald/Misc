/*
https://practice.geeksforgeeks.org/problems/count-the-triplets/0

Count all the triples in an array such that the sum of two of the 
numbers equals the third.
*/

#include <stdio.h>
#include <stdlib.h>

void test_case ( int * arr, int sz ) ;

/* ------------------------------------------- */
int main ( int argc, char ** argv ) {
    int t1[4] = { 1, 5, 3, 2 };
    int t2[3] = { 3, 2, 7 };

    test_case(t1,4);
    test_case(t2,3);

    return 0;
}

/* ------------------------------------------- */

int cmp ( const void * a, const void * b ) {
    int aa = *((int*)a);
    int bb = *((int*)b);

    return aa-bb;
}

void test_case ( int * a, int sz ) {
    int count = 0;
    int k, m, l, sum;

    qsort(a,sz,sizeof(a[0]),cmp);
    for ( k=0; k<sz-2; ++k ) {
        for ( m=k; m<sz-1; m++ ) {
            sum = a[k] + a[m];
            for ( l=m+1; m<sz; ++m ) {
                if ( sum==a[l] ) {
                    count++;
                    break;
                }
            } /* l */
        } /* m */
    } /* k  */

    //return;
    if ( count ) {
        printf("%d\n",count);
    } else {
        printf("-1\n");
    }
}
