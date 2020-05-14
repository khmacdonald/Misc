/*
https://practice.geeksforgeeks.org/problems/count-the-triplets/0

Count all the triples in an array such that the sum of two of the 
numbers equals the third.
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node * next;
};

struct LL  {
    struct node * root;
};
struct LL * create_list ( int n ) ;

void test_case ( struct LL * ll );

/* ------------------------------------------- */
int main ( int argc, char ** argv ) {
    //struct node n6 = { 6, NULL };
    //struct node n5 = { 5, &n6};
#if 0
    struct node n5 = { 5, NULL };
    struct node n4 = { 4, &n5 };
    struct node n3 = { 3, &n4 };
    struct node n2 = { 2, &n3 };
    struct node n1 = { 1, &n2 };
    struct LL ll = { &n1 };

    test_case(&ll);
#else
    struct LL * ll = NULL;
    int n = 5;
    if ( 1<argc ) {
        n = atoi(argv[1]);
    }
    ll = create_list(n);
    test_case(ll);
#endif


    return 0;
}

/* ------------------------------------------- */

struct LL * create_list ( int n ) {
    struct LL * ll = calloc(1,sizeof(*ll));
    struct node * node = NULL;
    struct node * pnode = NULL;
    int k;

    for ( k=0; k<n; ++k ) {
        node = calloc(1,sizeof(*node));
        node->val = k+1;
        if ( 0==k ) {
            ll->root = node;
        } else {
            pnode->next = node;
        }
        pnode = node;
    }

    return ll;
}

void test_case ( struct LL * ll ) {
    struct node * next = ll->root;
    struct node * half = ll->root;
    int k;

    for ( k=0; next!=NULL; ++k ) {
        next = next->next;
        if ( k&1 ) {
            half = half->next;
        }
    }

    printf("%d\n",half->val);

    return;
}
