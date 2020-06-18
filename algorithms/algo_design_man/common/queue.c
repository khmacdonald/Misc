/*
 * https://www3.cs.stonybrook.edu/~skiena/algorist/book/programs/queue.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print_statements.h" /* Formatted print wrappers */

#include "queue.h"


void init_queue ( queue * q ) {
    if ( !q ) {
        return;
    }

    q->first = 0;
    q->last = QUEUESIZE-1;
    q->count = 0;
}

int enqueue ( queue * q, int x ) {
    if ( !q){
        return 1;
    }

    if ( q->count >= QUEUESIZE ) {
        printf("Warning: queue overflow enqueue x = %d\n",x);
        return 1;
    }
    q->last = (q->last+1) % QUEUESIZE;
    q->q[ q->last ] = x;
    q->count++;

    return 0;
}

int dequeue ( int * x, queue * q ) {
    int f;
    if ( q->count <=0 ) {
        printf("Warning: empty queue dequeue.\n");
        return 1;
    }
    *x = q->q[ q->first ];
    q->first = (q->first+1) % QUEUESIZE;
    q->count = q->count-1;

    return 0;
}

int headq ( int * x, queue * q ) {
    if ( !q ) {
        return 1;
    }
    *x = q->q[ q->first ];

    return 0;
}

int empty_queue ( queue * q ) {
    if ( !q || q->count<=0 ) {
        return TRUE;
    }
    return FALSE;
}

void print_queue ( queue * q ) {
    int k;

    if ( !q ) {
        return;
    }

    k = q->first;

    printf("queue:");
    while ( k != q->last ) {
        printf(" %d",q->q[k]);
        k = (k+1) % QUEUESIZE;
    }

    printf(" %d\n",q->q[k]);

    return;
}


