#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>

#include "linked_list.h"

#include "print_statements.h"

//typedef void (*unit_test_t)(void) ;     /**< Unit test function type */
//typedef void (*dealloc_t)(void*) ;      /**< Deallocattion function */
typedef void (*print_data_t)(void*) ;   /**< Prints data */

/* ---------------------------------------------------------------- */
/*                              QUEUE                               */

/*
 * Stack data structures.
 */
typedef struct _node QNODE; /* Queue node */
typedef struct _base QUEUE; /* Queue data structure */

void q_print ( const char*, QUEUE*, print_data_t, int ) ;
void q_print_node ( QNODE*, print_data_t );
int q_set_node ( QNODE*, QNODE*, QNODE*, void*, int ) ;
QNODE * q_create_node ( QNODE*, QNODE*, void*, int ) ;

int q_push ( QUEUE*, void*, int ) ;
QNODE * q_pop ( QUEUE* ) ;

void q_clean ( QUEUE*, dealloc_t ) ;

/* ------------------------------------------------------- */
/*                       Unit Test                         */

#endif
