#ifndef ALGOS_QUEUE_H
#define ALGOS_QUEUE_H

#include "algos_common.h"

#define QUEUESIZE   1000

typedef struct _queue {
    int q[QUEUESIZE+1];     /* body of queue */
    int first;              /* position of first element */
    int last;               /* position of last element */
    int count;              /* number of queue elements */
} queue;

void init_queue ( queue * q ) ;
int enqueue ( queue * q, int x ) ;
int dequeue ( int * x, queue * q ) ;
int headq ( int * x, queue * q ) ;
int empty_queue ( queue * q ) ;
void print_queue ( queue * q ) ;

#endif
