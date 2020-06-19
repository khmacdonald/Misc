#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* ---------------------------------------------------------------- */
/*                              QUEUE                               */

/*
 * These amount to wrapping particular linked list functions.
 */

/**
 * @brief Prints a queue starting with the head.
 */
void q_print ( 
        const char * label,     /**< Label of queue */
        QUEUE * queue,          /**< list */
        print_data_t pdata,     /**< Print data */
        int rline ) {           /**< Number of return lines to print */
    gen_base_print("queue",label,queue,pdata,rline);
}

/**
 * @brief Prints a queue node.
 */
void q_print_node ( 
        QNODE * node,           /**< The node to print */
        print_data_t pdata ) {  /**< Printer for user data */
    ll_print_node(node,pdata);
}

/**
 * @brief Sets a queue node.
 */
int q_set_node ( 
        QNODE * node,       /**< The node to set */
        QNODE * blink,      /**< The back link for the node */
        QNODE * flink,      /**< The forward link for the node */
        void  * data,       /**< User data */
        int val ) {         /**< The value of the node */
    return ll_set_node(node,blink,flink,data,val);
}

/**
 * @brief Creates a queue node.
 */
QNODE * q_create_node ( 
        QNODE * blink,      /**< The back link for the node */
        QNODE * flink,      /**< The forward link for the node */
        void  * data,       /**< User data */
        int val ) {         /**< The value of the node */
    return ll_create_node(blink,flink,data,val);
}

/**
 * @brief Pushes data and value onto the queue.
 */
int q_push ( 
        QUEUE * queue,  /**< The queue */
        void * data,    /** User data */
        int n ) {       /**< The value to add */
    return ll_push(queue,data,n);
}

/**
 * @brief Pops a node off the queue.
 */
QNODE * q_pop ( 
        QUEUE * queue ) {  /**< The queue */
    return ll_node_pop_tail(queue);
}

/**
 * @brief Cleans the memory allocated for the queue nodes.
 * 
 * @note Does not deallocate the queue data structure.
 */
void q_clean ( 
        QUEUE * queue,          /**< Queue */
        dealloc_t deall ) {     /**< Deallocate user data function */
    ll_clean(queue,deall);
}

/* ---------------------------------------------------------------- */
/*                            Unit Test                             */

