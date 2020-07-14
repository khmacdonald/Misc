/*
https://www.hackerrank.com/challenges/climbing-the-leaderboard/problem?utm_campaign=challenge-recommendation&utm_medium=email&utm_source=24-hour-campaign

This works, except for test 8, which is a very large array of scores of
200,000 and 100,000 games played by Alice.
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

// Complete the climbingLeaderboard function below.

#define MAX_PRINT_ARRAY 16

/* ------------------------------------------------------------------------ */
/*                              Data Structures                             */
struct orig_loc { 
    int val, loc;
};

/* ------------------------------------------------------------------------ */
/*                            Prototype Functions                           */
void print_array ( char * label, int * arr, int n, int line ) ;
int cmp_oloc ( const void * aa, const void * bb ) ;
void random_array ( int *arr, int n ) ;
int cmp_int ( const void * aa, const void * bb ) ;


void set_rank ( int * srank, int * scores, int scnt ) ;
void print_oloc ( struct orig_loc * oloc, int n ) ;
struct orig_loc * sorted_orig_loc ( int * arr, int n );
int* climbingLeaderboard( int scores_count, int* scores, 
                          int alice_count, int* alice, int* result_count ) ;


void test_base_new ( int * scores, int scnt, 
                     int * alice, int acnt, int * expected ) ;
void test01 ( void ) ;
void test02 ( void ) ;
void test_random ( int argc, char ** argv ) ;

/* ------------------------------------------------------------------------ */
/*                               Main Functions                             */

int main ( int argc, char ** argv ) {
    printf("\n---------------------------------------------\n\n");
    //test01();
    //printf("\n---------------------------------------------\n\n");
    //test02();
    test_random(argc,argv) ;
    printf("\n---------------------------------------------\n\n");
    return 0;
}
/* ------------------------------------------------------------------------ */

// Please store the size of the integer array to be returned 
//   in result_count pointer. For example,
// int a[3] = {1, 2, 3};
//
// *result_count = 3;
//
// return a;

int * climbingLeaderboard(
        int scores_count, int* scores, 
        int alice_count, int* alice, 
        int* result_count ) {
    struct orig_loc * oloc = sorted_orig_loc(alice,alice_count);
    int * res = calloc(alice_count,sizeof(*res));
    int * rank = calloc(scores_count,sizeof(*rank));
    int k, n, val, loc;

    *result_count = alice_count;

    /* Sort Alices scores, but maintain the original order */
    set_rank(rank,scores,scores_count);

    /* Check Alices sorted scores against the sorted scoreboard */
    for ( k=0, n=0; k<alice_count; ++k ) {
        while ( n<scores_count ) {
            val = oloc[k].val;
            loc = oloc[k].loc;
            if ( val >= scores[n] ) { /* Check Alices score againt the score board */
                res[loc] = rank[n]; /* Put the score in the right order */
                break;
            }
            n++; /* Check next score */
        }
        /* All remaing scores are lower than the scoreboard */
        if ( !res[loc] ) {
            res[loc] = rank[scores_count-1]+1; /* Put the score in the right order */
        }
    }

    return res;
}


/* ------------------------------------------------------------------------ */
/*                              Helper Functions                            */
void set_rank ( int * srank, int * scores, int scnt ) {
    int k;

    srank[0] = 1;
    for ( k=1; k<scnt; ++k ) {
        if ( scores[k]!=scores[k-1] ) {
            srank[k] = srank[k-1]+1;
        } else {
            srank[k] = srank[k-1];
        }
    }
}

void print_oloc ( struct orig_loc * oloc, int n ) {
    int k;

    for ( k=0; k<n; ++k ) { 
        printf("(%3d,%3d) ",oloc[k].loc,oloc[k].val);
    }
    printf("\n");
}

struct orig_loc * sorted_orig_loc ( int * arr, int n ) {
    struct orig_loc * oloc = calloc(n,sizeof(*oloc));
    int k;

    for ( k=0; k<n; ++k ) {
        oloc[k].val = arr[k];
        oloc[k].loc = k;
    }
    qsort(oloc,n,sizeof(oloc[0]),cmp_oloc);

    return oloc;
}

void print_array ( char * label, int * arr, int n, int line ) {
    int k;
#define MAX_PRINT_ARRAY 16

    printf("[%d] %s (%d) = { %d",line,label,n,arr[0]);
    n = (n <= MAX_PRINT_ARRAY) ? n : MAX_PRINT_ARRAY;
    for ( k=1; k<n; ++k ) {
        printf(", %d",arr[k]);
    }
    printf(" }\n");
}

int cmp_oloc ( const void * aa, const void * bb ) {
    struct orig_loc * a = (struct orig_loc *) aa;
    struct orig_loc * b = (struct orig_loc *) bb;

    return b->val - a->val;
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

/* ------------------------------------------------------------------------ */
/*                              Tester Functions                            */

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
    const int scnt = 6;
    int scores[scnt] = { 100, 90, 90, 80, 75, 60 };
    const int acnt = 5;
    int alice[acnt] = { 50, 65, 77, 90, 102 };
    int expected[acnt] = { 6, 5, 4, 2, 1 };

    test_base_new(scores,scnt,alice,acnt,expected);
}

void test02 ( void ) {
    const int scnt = 7;
    int scores[scnt] = { 100, 100, 50, 40, 40, 20, 10 };
    const int acnt = 4;
    int alice[acnt] = { 5, 25, 50, 120 };
    int expected[acnt] = { 6, 4, 2, 1 };

    test_base_new(scores,scnt,alice,acnt,expected);
}

/* ------------------------------------------------------------------------ */


