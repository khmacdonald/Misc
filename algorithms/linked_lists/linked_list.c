#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

/* ---------------------------------------------------------------- */
/*                           LINKED LIST                            */

/**
 * @brief Prints a specified number of return lines.
 */
static void print_return_lines ( 
        int rline ) {       /**< Number of return lines to print */
    while ( rline > 0 ) {
        printf("\n");
        rline--;
    }
}

/**
 * @brief Prints a linked list node.
 */
void print_ll_node ( 
        LNODE * node ) {    /**< The node to print */
    if ( node ) {
        printf("[%p]: .blink = %p, .flink = %p, .val = %d\n",
               node,node->blink,node->flink,node->val);
    }
}

/**
 * @brief Sets a linked list node.
 */
int ll_set_node ( 
        LNODE * node,       /**< The node to set */
        LNODE * blink,      /**< The back link for the node */
        LNODE * flink,      /**< The forward link for the node */
        int val ) {         /**< The value of the node */
    if ( node ) {
        node->blink = blink;
        node->flink = flink;
        node->val   = val;
        return 0;
    }
    return 1;
}

/**
 * @brief Prints a linked list.
 */
void ll_print ( 
        const char * type,      /* Type of linked list */
        const char * label,     /* Label of linked list */
        LLIST * list,           /* Linked list */
        int rline ) {           /* Number of return lines to print */
    LNODE * node = NULL;

    if ( label ) {
        printf("%s_%s : ",label,type);
    }

    if ( NULL==list ) {
        printf("(nil)");
    }

    printf("(%d)",list->count);
    for ( node = list->root; node; node = node->flink ) {
        printf(" %d",node->val);
    }

    print_return_lines(rline);
}

/**
 * @brief Pushes an integer onto the linked list as root.
 */
int ll_push ( 
        LLIST * L,  /**< The linked list */
        int n ) {   /**< The value to add */
    LNODE * node = NULL;

    if ( !L ) {
        return 1;
    }

    node = calloc(1,sizeof(*node));
    if ( !node ) {
        return 2;
    }

    /* Push onto list as head */
    /* TODO - fix */
    ll_set_node(node,NULL,L->root,n);
    if ( L->root ) {
        L->root->blink = node;
    } else {
        L->tail = node;
    }
    L->root = node;
    L->count++;

    return 0;
}

int ll_push_tail ( 
        LLIST * L,  /**< The linked list */
        int n ) {   /**< The value to add */
    LNODE * node = NULL;

    if ( !L ) {
        return 1;
    }

    node = calloc(1,sizeof(*node));
    if ( !node ) {
        return 2;
    }

    /* TODO - finish */
    /* Push onto list as head */
    ll_set_node(node,L->tail,NULL,n);
    if ( L->tail ) {
        L->tail->flink = node;
    } else {
        L->tail = node;
    }
    L->tail = node;
    L->count++;

    return 0;
}

/**
 * @brief Inserts a value after a given value.
 */
int ll_insert_after ( 
        LLIST * L,      /**< Linked list */
        int k,          /**< Value to push after */
        int n ) {       /**< Value to push */
    LNODE * node = NULL;

    if ( !L ) {
        return 1;
    }
    if ( L->root && k<L->root->val ) { /* Push to head */
        return ll_push(L,n);
    }
    node = calloc(1,sizeof(*node));
    if ( !NULL ) {
        return 2;
    }

    /* Fast check */
    if ( L->tail ) {    
        if ( L->tail->val <= k ) {  /* Push to tail */
            /* push to tail */
            L->tail->flink = node;
            L->tail = node;
            L->count++;
        }
    }

    for ( node=L->root; node; node = node->flink ) {
        if ( k <= node->val ) {
        }
    }
}

/**
 * @brief Inserts a value before a given value.
 */
int ll_insert_before ( 
        LLIST * L,      /**< Linked list */
        int k,          /**< Value to push before */
        int n ) {       /**< Value to push */
}

/**
 * @brief Pops the head node off the list.
 */
LNODE * ll_node_pop_head ( 
        LLIST * L ) {       /**< Linked list */
    LNODE * node = NULL;

    if ( !L || L->count < 1 ) { /* Nothing to pop */
        return NULL;
    }
    node = L->root;         /* Pop head */
    if ( 1==L->count ) {    /* Resultant list is empty */
        L->root = NULL;
        L->tail = NULL;
        L->count = 0;
    } else {
        L->root = node->flink; /* Adjust root */
        L->root->blink = NULL;
        L->count--;
    }
    node->blink = NULL;
    return node;
}

/**
 * @brief Pops the tail node off the list.
 */
LNODE * ll_node_pop_tail ( 
        LLIST * L ) {       /**< Linked list */
    LNODE * node = NULL;

    if ( !L || L->count < 1 ) {
        return NULL;
    }
    node = L->tail;
    if ( 1==L->count ) {
        L->root = NULL;
        L->tail = NULL;
        L->count = 0;
    } else {
        L->tail = node->blink;
        L->tail->flink = NULL;
        L->count--;
    }
    node->blink = NULL;
    return node;
}

/**
 * @brief Create a list from an array.
 */
LLIST * ll_create ( 
        int * arr,      /**< Array */
        int n ) {       /**< Length of array */
    LLIST * list = calloc(1,sizeof(*list));
    int k;

    if ( !list ) {
        return NULL;
    }
    
    for ( k=0; k<n; ++k ) {
        if ( ll_push(list,arr[k]) ) {
            ll_clean(list);
            return NULL;
        }
    }

    return list;
}

/**
 * @brief Deallocate dynamically allocated memory.
 */
void ll_clean ( 
        LLIST * L ) {   /**< Linked list */
    LNODE * node;
    LNODE * next_node;

    if ( !L ) {
        return;
    }

    /* Free each node */
    for ( node = L->root; node; node = next_node ) {
        next_node = node->flink; /* Save forward link */
        free(node);
    }
}

/* ------------------------------------------------------- */
/*                       Unit Test                         */

void unit_test_print_generic ( void ) {
    LNODE n1, n2, n3, n4, n5;
    LLIST L = { .root = &n1, .count = 5 } ;

    printf("    *** %s ***\n",__FUNCTION__);

    ll_set_node(&n1,NULL, &n2,1);
    ll_set_node(&n2, &n1, &n3,2);
    ll_set_node(&n3, &n2, &n4,3);
    ll_set_node(&n4, &n3, &n5,4);
    ll_set_node(&n5, &n4,NULL,5);

    printf("\n[%d] ",__LINE__);
    ll_print("linked_list",__FUNCTION__,&L,1);
}

void unit_test_push ( void ) {
    LLIST L = {0};
    int k;

    printf("    *** %s ***\n",__FUNCTION__);

    for ( k=5; k>0; k-- ) {
        ll_push(&L,2*k);
    }

    printf("\n[%d] ",__LINE__);
    ll_print("linked_list",__FUNCTION__,&L,1);

    ll_clean(&L);
}

void unit_test_pop_head ( void ) {
    LLIST L = {0};
    LNODE * node = NULL;;
    int k;

    printf("    *** %s ***\n",__FUNCTION__);

    for ( k=5; k>0; k-- ) {
        ll_push(&L,2*k);
    }

    printf("\n[%d] ",__LINE__);
    ll_print("linked_list",__FUNCTION__,&L,1);
    node = ll_node_pop_head(&L); 
    info_print("Popped node value = %d\n",node->val);
    free(node);
    ll_print("popped_linked_list",__FUNCTION__,&L,1);

    ll_clean(&L);
}

void unit_test_pop_tail ( void ) {
    LLIST L = {0};
    LNODE * node = NULL;;
    int k;

    printf("    *** %s ***\n",__FUNCTION__);

    for ( k=5; k>0; k-- ) {
        ll_push(&L,2*k);
    }

    printf("\n[%d] ",__LINE__);
    ll_print("linked_list",__FUNCTION__,&L,1);
    node = ll_node_pop_tail(&L); 
    info_print("Popped node value = %d\n",node->val);
    free(node);
    ll_print("popped_linked_list",__FUNCTION__,&L,1);

    ll_clean(&L);
}













