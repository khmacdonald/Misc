#ifndef INTEGER_BINARY_TREE_H
#define INTEGER_BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>

struct ibt_node {
    int val;
    struct ibt_node * parent;
    struct ibt_node * lchild;
    struct ibt_node * rchild;
};
typedef struct ibt_node IBT_NODE;

struct ibt { 
    IBT_NODE * root;
};
typedef struct ibt IBT;

void print_tree ( const char * label, IBT * tree ) ;
void print_tree_by_level ( const char * label, IBT * tree ) ;
void print_tree_sorted  ( const char * label, IBT * tree, int ascending ) ;
void destroy_tree ( IBT * tree, int free_tree ) ;

/*
 * Add an integer to the tree.
 */ 
int ibt_add_node ( IBT * tree, int n ) ;

/*
 * Fill integer binary tree with random integers.
 */
int ibt_random_tree ( IBT * tree, int n ) ;

/* ---------- Unit Tests ---------- */
void ibt_test_print_tree ( void ) ;
void ibt_test_add_node ( void ) ;
void ibt_test_random_tree ( int ac, char ** av ) ;
void ibt_test_print_sorted ( int ac, char ** av ) ;


#endif
