/*
https://practice.geeksforgeeks.org/problems/subarray-with-given-sum/0

Find the subarray of an array such that the sum of the elements of
the subarray equals an inputted value.
*/

#include <stdio.h>
#include <stdlib.h>

struct tcase {
    int sum;        /* Sum of subarray */
    int * arr;      /* Array to check */
    int sz;         /* Size of array */
};

struct tcase * read_cmd ( int * sz, int argc, char ** argv ) ;
void test_case ( int * arr, int sz, int sum ) ;

/* ------------------------------------------- */
int main ( int argc, char ** argv ) {
    int t1[5] = {1,2,3,7,5};
    int t2[10] = {1,2,3,4,5,6,7,8,9,10};

    printf("    Test 1\n");
    test_case(t1,5,12);
    printf("\n------------------------------------------- \n");
    printf("    Test 2\n");
    test_case(t2,10,15);

    return 0;
}

/* ------------------------------------------- */


struct tcase * read_cmd ( int * sz, int argc, char ** argv )  {
    int k,m;
    int ntcase = 0,n,sum;
    struct tcase * tcase;
    int *arr = NULL;

    scanf("%d",&ntcase);
    tcase = calloc(ntcase,sizeof(*tcase));

    for ( k=0; k<ntcase; ++k ) {
        scanf("%d %d",&n,&sum);
        arr = calloc(1,sizeof(*arr));
        for ( m=0; m<n; ++m ) {
            scanf("%d",&arr[m]);
        }
        tcase[k].sum = sum;
        tcase[k].arr = arr;
        tcase[k].sz = n;
    }

    return tcase;
}

void print_answer ( int * arr, int sz, int lo, int hi, int sum ) {
    int k,sm=0;
    printf("arr = { %d", arr[0]);
    for ( k=1; k<sz; k++ ) {
        printf(", %d",arr[k]);
    }
    printf(" } \n");
    printf("sum = %d\n",sum);
    printf("%d -> %d\n",lo+1, hi+1);
    for ( k=lo; k<hi+1; ++k ) {
        sm += arr[k];
    }
    printf("Computed sum: %d\n",sm);
}

/*
 * Find the subarray of arr such that the sum of the elements
 * of the subarray equals 'sum'.
 */
void test_case ( int * arr, int sz, int sum ) {
    int lo = 0, k;
    int sm=arr[lo],tmp;

    if ( sm==sum ) {
        printf("0 0\n");
        return;
    }

    for ( k=1; k<sz; ++k ) {
        tmp = sm + arr[k];
        if ( tmp==sum ) {
            printf("%d %d\n",lo+1,k+1);
            //print_answer(arr,sz,lo,k,sum);
            return;
        } else if ( tmp<sum ) {
            sm = tmp;
        } else {
            while ( tmp>sum ) {
                tmp -= arr[lo];
                lo++;
                if ( tmp==sum ) {
                    printf("%d %d\n",lo+1,k+1);
                    //print_answer(arr,sz,lo,k,sum);
                    return;
                }
            }
            sm = tmp;
        } /* if-else */
    } /* for */
}











