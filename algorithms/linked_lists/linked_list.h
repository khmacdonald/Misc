#ifndef STACK_QUEUE_H
#define STACK_QUEUE_H

#include "print_statements.h"

struct _node {
    struct _node * blink;   /**< Back link */
    struct _node * flink;   /**< Forward link */

    int val;                /**< Node value */
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

void ll_print ( const char*, const char*, LLIST*, int ) ;
int ll_set_node ( LNODE*, LNODE*, LNODE*, int ) ;

int ll_push ( LLIST*, int ) ;
int ll_push_tail ( LLIST*, int ) ;
int ll_insert_after ( LLIST*, int, int ) ;
int ll_insert_before ( LLIST*, int, int ) ;

LNODE * ll_node_pop_head ( LLIST* ) ;
LNODE * ll_node_pop_tail ( LLIST* ) ;


LLIST * ll_create ( int*, int ) ;
void ll_clean ( LLIST* ) ;

/* ------------------------------------------------------- */
/*                       Unit Test                         */

void unit_test_print_generic ( void ) ;
void unit_test_push ( void ) ;
void unit_test_pop_head ( void ) ;
void unit_test_pop_tail ( void ) ;

#endif
