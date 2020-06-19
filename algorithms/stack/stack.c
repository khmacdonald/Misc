#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

/* ---------------------------------------------------------------- */
/*                              STACK                               */

/*
 * These amount to wrapping particular linked list functions.
 */

/**
 * @brief Prints a stack starting with the head.
 */
void s_print ( 
        const char * label,     /**< Label of stack */
        STACK * stack,          /**< list */
        print_data_t pdata,     /**< Print data */
        int rline ) {           /**<  Number of return lines to print */
    gen_base_print("stack",label,stack,pdata,rline);
}

/**
 * @brief Prints a stack node.
 */
void s_print_node ( 
        SNODE * node,           /**< The node to print */
        print_data_t pdata ) {  /**< Printer for user data */
    ll_print_node(node,pdata);
}

/**
 * @brief Sets a stack node.
 */
int s_set_node ( 
        SNODE * node,       /**< The node to set */
        SNODE * blink,      /**< The back link for the node */
        SNODE * flink,      /**< The forward link for the node */
        void  * data,       /**< User data */
        int val ) {         /**< The value of the node */
    return ll_set_node(node,blink,flink,data,val);
}

/**
 * @brief Creates a stack node.
 */
SNODE * s_create_node ( 
        SNODE * blink,      /**< The back link for the node */
        SNODE * flink,      /**< The forward link for the node */
        void  * data,       /**< User data */
        int val ) {         /**< The value of the node */
    return ll_create_node(blink,flink,data,val);
}

/**
 * @brief Pushes data and value onto the stack.
 */
int s_push ( 
        STACK * stack,  /**< The stack */
        void * data,    /** User data */
        int n ) {       /**< The value to add */
    return ll_push(stack,data,n);
}

/**
 * @brief Pops a node off the stack.
 */
SNODE * s_pop ( 
        STACK * stack ) {  /**< The stack */
    return ll_node_pop_head(stack);
}

/**
 * @brief Cleans the memory allocated for the stack nodes.
 * 
 * @note Does not deallocate the stack data structure.
 */
void s_clean ( 
        STACK * stack,          /**< Linked list */
        dealloc_t deall ) {     /**< Deallocate user data function */
    ll_clean(stack,deall);
}

/* ---------------------------------------------------------------- */
/*                            Unit Test                             */

