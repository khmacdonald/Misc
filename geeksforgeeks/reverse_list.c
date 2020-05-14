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
void print_list ( struct LL * ll ) ;

void test_case ( struct LL * ll );

/* ------------------------------------------- */
int main ( int argc, char ** argv ) {
    struct LL * ll = NULL;
    int n = 5;

    if ( 1<argc ) {
        n = atoi(argv[1]);
    }

    ll = create_list(n);

    test_case(ll);

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

void print_list ( struct LL * ll ) {
    struct node * node = ll->root;
    int k;

    printf("List = ");
    for ( k=0; NULL!=node; ++k ) {
        if ( 0==k ) {
            printf("%d",node->val);
        } else {
            printf(" -> %d",node->val);
        }
        node = node->next;
    }
    printf("\n");
}

void test_case ( struct LL * ll ) {
    struct LL * rev = calloc(1,sizeof(*ll));
    struct node * nnode = NULL;
    struct node * n1 = NULL;
    struct node * n2 = NULL;
    struct node * n3 = NULL;

    print_list(ll);
    n1 = ll->root;
    while ( n1 ) {
        nnode = calloc(1,sizeof(*nnode));
        nnode->val = n1->val;
        nnode->next = n2;
        n2 = nnode;
        n1 = n1->next;
    }
    rev->root = n2;
    print_list(rev);

    return;
}
