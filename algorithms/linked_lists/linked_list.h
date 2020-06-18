#ifndef STACK_QUEUE_H
#define STACK_QUEUE_H

struct _queue_node {
    int val;
    struct _queue_node * blink;
    struct _queue_node * flink;
};
typedef struct _queue_node QNODE;
typedef struct _queue_node SNODE;

struct _queue {
    struct _queue_node * root;
    struct _queue_node * tail;
};
typedef struct _queue QUEUE;
typedef struct _queue STACK;

/* Print a Queue */
void print_queue ( const char * label, QUEUE * Q ) ;

/* Push an integer onto the queue */
int queue_push ( QUEUE * Q, int n ) ;

/* Pop an integer off the queue */
QNODE * queue_pop ( QUEUE * Q ) ;

/* Creates a random queue of size n */
QNODE * queue_create_node ( int n ) ;

/* Deallocates all memory assicated with the queue */
void queue_empty ( QUEUE * Q, int free_q ) ;



/* ------------------------------------------------------- */
/*                       Unit Test                         */
void unit_test_print_q ( ) ;
void unit_test_push_q ( ) ;
void unit_test_pop_q ( ) ;

#endif
