/*
https://www.hackerrank.com/challenges/climbing-the-leaderboard/problem?utm_campaign=challenge-recommendation&utm_medium=email&utm_source=24-hour-campaign
*/

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int * g_scores = NULL;
int g_scnt = 0;

// Complete the climbingLeaderboard function below.

// Please store the size of the integer array to be returned in result_count pointer. For example,
// int a[3] = {1, 2, 3};
//
// *result_count = 3;
//
// return a;
//

void print_array ( char * label, int * arr, int n, int line ) {
    int k;

    printf("[%d] %s (%d) = { %d",line,label,n,arr[0]);
    for ( k=1; k<n; ++k ) {
        printf(", %d",arr[k]);
    }
    printf(" }\n");
}

struct orig_loc { 
    int val, loc;
};

int cmp ( const void * aa, const void * bb ) {
    struct orig_loc * a = (struct orig_loc *) aa;
    struct orig_loc * b = (struct orig_loc *) bb;

    return b->val - a->val;
}

int* climbingLeaderboard(
        int scores_count, int* scores, 
        int alice_count, int* alice, 
        int* result_count ) {
    struct orig_loc * orig = calloc(alice_count,sizeof(*orig));
    int * res = calloc(alice_count,sizeof(*res));
    int k, j, ridx, rank=1;

    *result_count = alice_count;

    /* 
     * Need to do sort (for speed) and keep track of the original order
     */
    for ( k=0; k<alice_count; ++k ) {
        orig[k].val = alice[k];
        orig[k].loc = k;
    }
    qsort(orig,alice_count,sizeof(orig[0]),cmp);

    k=0;
    for ( j=0; j<alice_count; ++j ) {
        while ( k<scores_count ) {
            if ( orig[j].val >= scores[k] ) {
                res[orig[j].loc] = rank;
                goto OUT_WHILE;
            }
            if ( k>0 && scores[k]!=scores[k-1] ) {
                rank++;
            }
            k++;
        }
OUT_WHILE:
        if ( 0==res[orig[j].loc] && k>=scores_count ) {
            res[orig[j].loc] = rank+1;
        }
    }

    return res;
}

void test_base_new ( int * scores, int scnt, 
                     int * alice, int acnt, 
                     int * expected ) {
    int rcnt = 0;
    int * res = NULL;
    int k;

    print_array("scores",scores,scnt,__LINE__);
    print_array("alice",alice,acnt,__LINE__);

    res = climbingLeaderboard(scnt,scores,acnt,alice,&rcnt);
    for ( k=0; k<rcnt; ++k ) {
        if ( expected ) {
            printf("%d (%d)\n",res[k],expected[k]);
        } else {
            printf("%d\n",res[k]);
        }
    }
}

int cmp_int ( const void * aa, const void * bb ) {
    int a = *((int*)aa);
    int b = *((int*)bb);

    return b-a;
}

void random_array ( int *arr, int n ) {
    static int seeded = 0;
    int k;

    if ( !seeded ) {
        srand(time(NULL));
        seeded = 1;
    }

    for ( k=0; k<n; ++k ) {
        arr[k] = rand() % 100;
    }
}

int * random_array_old ( int n ) {
    int * arr = calloc(1,sizeof(*arr));
    static int seeded = 0;
    int k;

    //printf("[%d] Here\n",__LINE__);
    print_array("g_scores",g_scores,g_scnt,__LINE__);

    if ( !seeded ) {
        srand(time(NULL));
        seeded = 1;
    }
    print_array("g_scores",g_scores,g_scnt,__LINE__);

    for ( k=0; k<n; ++k ) {
        //printf("[%d] Here (%d)\n",__LINE__,k);
        arr[k] = rand() % 100;
    }
    print_array("g_scores",g_scores,g_scnt,__LINE__);
    return arr;
}

void test_random ( int argc, char ** argv ) {
    int scores[10] = {0};
    int alice[6] = {0};
    int scnt = 10;
    int acnt = 6;
    int k,n=10;

    if ( 1<argc ) {
        n = atoi(argv[1]);
    }

    for ( k=0; k<n; k++ ) {
        printf("---------------------------------------------------\n");
        printf("    *** [%d] Test %2d ***\n",__LINE__,k+1);

        random_array(scores,scnt);
        qsort(scores,scnt,sizeof(*scores),cmp_int);

        random_array(alice,acnt);

        test_base_new(scores,scnt,alice,acnt,NULL);
    }
}

void test01 ( void ) {
    int scores[6] = { 100, 90, 90, 80, 75, 60 };
    int scnt = 6;
    int alice[5] = { 50, 65, 77, 90, 102 };
    int acnt = 5;
    int expected[5] = { 6, 5, 4, 2, 1 };

    test_base_new(scores,scnt,alice,acnt,expected);
}

void test02 ( void ) {
    int scores[7] = { 100, 100, 50, 40, 40, 20, 10 };
    int scnt = 7;
    int alice[4] = { 5, 25, 50, 120 };
    int acnt = 4;
    int expected[4] = { 6, 4, 2, 1 };
    int rcount;

    test_base_new(scores,scnt,alice,acnt,expected);
}

int main ( int argc, char ** argv ) {
    printf("\n---------------------------------------------\n\n");
    test_random(argc,argv) ;
    printf("\n---------------------------------------------\n\n");
    return 0;
}

