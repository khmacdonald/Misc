#ifndef STACK_H
#define STACK_H

#include <stdio.h>

#include "linked_list.h"

#include "print_statements.h"

//typedef void (*unit_test_t)(void) ;     /**< Unit test function type */
//typedef void (*dealloc_t)(void*) ;      /**< Deallocattion function */
typedef void (*print_data_t)(void*) ;   /**< Prints data */

/* ---------------------------------------------------------------- */
/*                              STACK                               */

/*
 * Stack data structures.
 */
typedef struct _node SNODE; /* Stack node */
typedef struct _base STACK; /* Stack data structure */

void s_print ( const char*, STACK*, print_data_t, int ) ;
void s_print_node ( SNODE*, print_data_t );
int s_set_node ( SNODE*, SNODE*, SNODE*, void*, int ) ;
SNODE * s_create_node ( SNODE*, SNODE*, void*, int ) ;

int s_push ( STACK*, void*, int ) ;
SNODE * s_pop ( STACK* ) ;

void s_clean ( STACK*, dealloc_t ) ;

/* ------------------------------------------------------- */
/*                       Unit Test                         */

#endif
