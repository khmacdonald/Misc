#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>

#include "print_statements.h"

typedef void (*unit_test_t)(void) ;     /**< Unit test function type */
typedef void (*dealloc_t)(void*) ;      /**< Deallocattion function */
typedef void (*print_data_t)(void*) ;   /**< Prints data */

struct _node {
    struct _node * blink;   /**< Back link */
    struct _node * flink;   /**< Forward link */

    int val;                /**< Node value */
    void * data;            /**< Pointer to user data */
};

struct _base {
    struct _node * root;    /**< Root of the list */
    struct _node * tail;    /**< Tail of the list */

    int count;              /**< Number of nodes in list */
};

/* ---------------------------------------------------------------- */
/*                           LINKED LIST                            */

/*
 * Generic linked list class.
 */
typedef struct _node LNODE; /* Linked list node */
typedef struct _base LLIST; /* Linked list data structure */

void gen_base_print ( const char*, const char*, LLIST*, print_data_t, int ) ;

void ll_print ( const char*, LLIST*, print_data_t, int ) ;
void ll_print_node ( LNODE*, print_data_t ) ;
int ll_set_node ( LNODE*, LNODE*, LNODE*, void*, int ) ;
LNODE * ll_create_node ( LNODE*, LNODE*, void*, int ) ;

int ll_push ( LLIST*, void*, int ) ;
int ll_push_tail ( LLIST*, void*, int ) ;
int ll_insert_after ( LLIST*, int, void*, int ) ;

LNODE * ll_node_pop_head ( LLIST* ) ;
LNODE * ll_node_pop_tail ( LLIST* ) ;
LNODE * ll_node_pop_by_val ( LLIST*, int ) ;


LLIST * ll_create ( int*, void**, int ) ;
void ll_clean ( LLIST*, dealloc_t ) ;

/* ------------------------------------------------------- */
/*                       Unit Test                         */

void ll_unit_test_print_generic ( void ) ;
void ll_unit_test_push ( void ) ;
void ll_unit_test_pop_head ( void ) ;
void ll_unit_test_pop_tail ( void ) ;
void ll_unit_test_remove_node ( void ) ;

void ll_unit_test_insert_after ( void ) ;
void ll_unit_test_create_list ( void ) ;

void ll_unit_test_print_data ( void ) ;

void ll_unit_test_all ( void ) ;

#endif
