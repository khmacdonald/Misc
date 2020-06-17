#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack_queue.h"

void print_queue ( const char * label, QUEUE * Q ) {
    QNODE * node = NULL;
    int count = 0;

    if ( label ) {
        printf("%s_queue = ",label );
    }
    if ( NULL==Q || NULL==Q->root ) {
        printf("NULL");
    }

    for ( node = Q->root; NULL!=node; node = node->flink ) {
        printf("%d",node->val);
        if ( node->flink ) {
            printf(" -> ");
        }
    }

    printf("\n");
}

void queue_empty ( QUEUE * Q, int free_q ) {
    QNODE * node = NULL;

    if ( NULL==Q ) {
        return;
    }

    node = queue_pop(Q);
    while ( node ) {
        free(node);
        node = queue_pop(Q);
    }
    if ( free_q ) {
        free(Q);
    }
}

QNODE * queue_create_node ( int n ) {
    QNODE * node = calloc(1,sizeof(*node));

    if ( NULL==node ) {
        return NULL;
    }
    node->val = n;
    node->flink = NULL;
    node->blink = NULL;

    return node;
}

int queue_push ( QUEUE * Q, int n ) {
    QNODE * node = NULL;

    /* Check to make sure the queue exists */
    if ( NULL==Q ) {
        return 1;
    }

    /* Create node with value */
    node = queue_create_node(n); 
    if ( NULL==node ) {
        return 1;
    }

    /* Push node onto queue */
    if ( NULL==Q->root ) {
        /* Push onto an empty queue */ 
        Q->root = node;
        Q->tail = node;
    } else {
        /* Push onto queue as the root */ 
        node->flink = Q->root;
        Q->root->blink = node;
        Q->root = node;
    }

    return 0;
}

QNODE * queue_pop ( QUEUE * Q ) {
    QNODE * node = NULL;

    if ( NULL==Q || NULL==Q->root ) {
        return NULL;
    }

    if ( Q->tail==Q->root ) {
        /* Queue has only one element */
        node = Q->root;
        Q->root = NULL;
    } else {
        /* Queue has more than one element */
        /* Pop the root's back link */
        node = Q->tail;
        Q->tail = Q->tail->blink;
        Q->tail->flink = NULL;

        /* For safety */
        node->blink = NULL;
    }

    return node;
}


/* ------------------------------------------------------- */
/*                       Unit Test                         */
void unit_test_print_q ( ) {
    QUEUE Q = {0};
    QNODE n1 = { 1, NULL, NULL };
    QNODE n2 = { 2, NULL, NULL };
    QNODE n3 = { 3, NULL, NULL };
    QNODE n4 = { 4, NULL, NULL };
    QNODE n5 = { 5, NULL, NULL };

    printf("    ***Beginning: %s\n",__FUNCTION__);

    Q.root = &n1;

    n1.flink = &n2;
    n1.blink = NULL;

    n2.flink = &n3;
    n2.blink = &n1;

    n3.flink = &n4;
    n3.blink = &n2;

    n4.flink = &n5;
    n4.blink = &n3;

    n5.flink = NULL;
    n5.blink = &n4;

    print_queue(__FUNCTION__,&Q);
    printf("        Success!\n");
}
void unit_test_push_q ( ) {
    QUEUE Q = {0};

    printf("    ***Beginning: %s\n",__FUNCTION__);

    queue_push(&Q,5);
    print_queue("Push 5",&Q);

    queue_push(&Q,4);
    print_queue("Push 4",&Q);

    queue_push(&Q,3);
    print_queue("Push 3",&Q);

    queue_push(&Q,2);
    print_queue("Push 2",&Q);

    queue_push(&Q,1);
    print_queue("Push 1",&Q);

    print_queue(__FUNCTION__,&Q);
    queue_empty(&Q,0);
    printf("        Success!\n");
}

void unit_test_pop_q ( ) {
    QUEUE Q = {0};
    QNODE * node = NULL;

    printf("    ***Beginning: %s\n",__FUNCTION__);

    queue_push(&Q,5);
    queue_push(&Q,4);
    queue_push(&Q,3);
    queue_push(&Q,2);
    queue_push(&Q,1);

    print_queue(__FUNCTION__,&Q);
    while ( Q.root ) {
        node = queue_pop(&Q);
        if ( NULL==node ) {
            printf("    Pop Failed\n");
        } else { 
            printf("    Pop Value = %d\n",node->val);
        }
        print_queue("    After",&Q);
        free(node);
    }
    queue_empty(&Q,0);
    printf("        Success!\n");
}






























