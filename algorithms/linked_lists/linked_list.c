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
void ll_print_node ( 
        LNODE * node,           /**< The node to print */
        print_data_t pdata ) {  /**< Printer for user data */
    if ( node ) {
        printf("[%p]: .blink = %p, .flink = %p, .val = %d",
               node,node->blink,node->flink,node->val);
        if ( pdata && node->data ) {
            pdata(node->data);
        }
        printf("\n");
    }
}

/**
 * @brief Sets a linked list node.
 */
int ll_set_node ( 
        LNODE * node,       /**< The node to set */
        LNODE * blink,      /**< The back link for the node */
        LNODE * flink,      /**< The forward link for the node */
        void  * data,       /**< User data */
        int val ) {         /**< The value of the node */

    if ( node ) {
        node->blink = blink;    /* Set back link */
        node->flink = flink;    /* Set forward link */
        node->val   = val;      /* Set value */
        node->data  = data;     /* Set user data */
        return 0;
    }

    return 1;
}

LNODE * ll_create_node ( 
        LNODE * blink,      /**< The back link for the node */
        LNODE * flink,      /**< The forward link for the node */
        void  * data,       /**< User data */
        int val ) {         /**< The value of the node */

    LNODE * node = calloc(1,sizeof(*node));
    if ( node ) {
         ll_set_node(node,blink,flink,data,val);
    }
    return node;
}

/**
 * @brief Prints a linked list.
 */
void ll_print ( 
        const char * type,      /**< Type of linked list */
        const char * label,     /**< Label of linked list */
        LLIST * list,           /**< Linked list */
        print_data_t pdata,     /**< Print data */
        int rline ) {           /**<  Number of return lines to print */
    LNODE * node = NULL;

    if ( label ) {
        printf("%s_%s : ",label,type);
    }

    if ( NULL==list ) {
        printf("(nil)");
    }

    printf("{%d}",list->count);
    for ( node = list->root; node; node = node->flink ) {
        if ( node->data && pdata ) {
            printf(" (%d: ",node->val);
            pdata(node->data);
            printf(")");
        } else {
            printf(" %d",node->val);
        }
    }

    print_return_lines(rline);
}

/**
 * @brief Pushes an integer onto the linked list as root.
 */
int ll_push ( 
        LLIST * L,      /**< The linked list */
        void * data,    /** User data */
        int n ) {       /**< The value to add */
    LNODE * node = NULL;

    /* Check arguments */
    if ( !L ) {
        return 1;
    }

    /* Create new node */
    node = ll_create_node(NULL,L->root,data,n); /* Set values for new node */
    if ( !node ) {
        return 2;
    }

    /* Push onto list as head */
    if ( L->count>0 && L->root ) {
        /* If non-zero root, set the back link of the current root
           to the new node, which will become the new root */
        L->root->blink = node; 
    } else {
        /* If the list is empty, when adding the new root, the tail
           must be set, as well as the root. */
        L->tail = node;
    }
    L->root = node; /* Set new root */
    L->count++;     /* Increment the count */

    return 0;
}

/**
 * @brief Pushes an integer onto the linked list as tail.
 */
int ll_push_tail ( 
        LLIST * L,      /**< The linked list */
        void * data,    /**< User data */
        int n ) {       /**< The value to add */
    LNODE * node = NULL;

    /* Check inputs */
    if ( !L ) {
        return 1;
    }
    
    /* Allocate and set new node */
    node = ll_create_node(L->tail,NULL,data,n);
    if ( !node ) {
        return 2;
    }

    /* Push onto list as tail */
    if ( L->count>0 && L->tail ) {
        /* The new node becomes the forward link of the
           existing tail */
        L->tail->flink = node; 
    } else {
        /* If the list is empty, the new root is also the tail */
        L->root = node; 
    }
    L->tail = node; /* Push as tail */
    L->count++;     /* Increment the number of elements */

    return 0;
}

/**
 * @brief Inserts a value after a given value.
 */
int ll_insert_after ( 
        LLIST * L,      /**< Linked list */
        int k,          /**< Value to push after */
        void * data,    /**< User data */
        int n ) {       /**< Value to push */
    LNODE * node = NULL;
    LNODE * new_node = NULL;

    /* Check argument */
    if ( !L ) {
        return 1;
    }
    if ( 0==L->count ) {
        return ll_push(L,data,n);
    }
    for ( node = L->root; node; node = node->flink ) {
        //dbg_print("node %d (k=%d)\n",node->val,k);
        if ( k==node->val || 
             ( node->val < k && node->flink && k < node->flink->val ) ) { 
            //dbg_print("    val = %d, flink->val = %d, k = %d\n",
            //          node->val,node->flink->val,k);
            /* Insert after */
            new_node = ll_create_node(node,node->flink,data,n);
            if ( NULL==new_node ) {
                return 2;
            }
            if ( node->flink ) {
                node->flink->blink = new_node;
            }
            node->flink = new_node;
            L->count++;
            return 0;
        }
    }

    /* Not inserted, yet, so insert as tail */
    ll_push_tail(L,data,n);

    return 0;
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
    node->blink = NULL;     /* Disconnect returned node from list */
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
    node = L->tail;         /* Pop tail */
    if ( 1==L->count ) {
        L->root = NULL; /* Popping the tail empties the list */
        L->tail = NULL;
        L->count = 0;
    } else {
        L->tail = node->blink;  /* Adjust the tail */
        L->tail->flink = NULL;
        L->count--;
    }
    node->blink = NULL; /* Disconnect returned node from list */
    return node;
}

LNODE * ll_node_pop_by_val ( 
        LLIST * L, 
        int n ) {
    LNODE * node = NULL;
    LNODE * ret_node = NULL;
    LNODE * flink = NULL;
    LNODE * blink = NULL;

    if ( !L ) {
        return NULL;
    }

    for ( node = L->root; node; node = node->flink ) {
        if ( n == node->val ) {
            ret_node = node;
            /* Remove node from list */
            flink = node->flink;
            blink = node->blink;
            if ( flink ) {
                flink->blink = blink;
            }
            if ( blink ) {
                blink->flink = flink;
            }
            ret_node->flink = NULL;
            ret_node->blink = NULL;
            L->count--;
        }
    }

    return ret_node;
}

/**
 * @brief Create a list from an array.
 */
LLIST * ll_create ( 
        int * arr,      /**< Array */
        void ** data,   /**< Array of user data */
        int n ) {       /**< Length of array */
    LLIST * list = calloc(1,sizeof(*list));
    void * insert_data;
    int k;

    if ( !list ) {
        return NULL;
    }
    
    /* Add values and user data to the list */
    for ( k=0; k<n; ++k ) {
        insert_data = (data) ? data[k] : NULL;      /* If user data exists */
        if ( ll_push(list,insert_data,arr[k]) ) {
            ll_clean(list,NULL);     /* Error, so deallocate all memory */
            return NULL;
        }
    }

    return list;
}

/**
 * @brief Deallocate dynamically allocated memory.
 */
void ll_clean ( 
        LLIST * L,              /**< Linked list */
        dealloc_t deall ) {     /**< Deallocate user data function */
    LNODE * node;
    LNODE * next_node;

    if ( !L ) {
        return;
    }

    /* Free each node */
    for ( node = L->root; node; node = next_node ) {
        if ( deall ) {
            deall(node->data);
        }
        next_node = node->flink; /* Save forward link */
        free(node);
    }
}

/* ------------------------------------------------------- */
/*                       Unit Test                         */

void ll_unit_test_print_generic ( void ) {
    LNODE n1, n2, n3, n4, n5;
    LLIST L = {0};
    LNODE * node;

    printf("[%d]    *** %s ***\n",__LINE__,__FUNCTION__);

    ll_set_node(&n1,NULL, &n2,NULL,1);
    ll_set_node(&n2, &n1, &n3,NULL,2);
    ll_set_node(&n3, &n2, &n4,NULL,3);
    ll_set_node(&n4, &n3, &n5,NULL,4);
    ll_set_node(&n5, &n4,NULL,NULL,5);
    L.root  = &n1;
    L.count = 5;

    printf("\n[%d] ",__LINE__);
    ll_print("linked_list",__FUNCTION__,&L,NULL,1);
}

void ll_unit_test_push ( void ) {
    LLIST L = {0};
    int k;

    printf("[%d]    *** %s ***\n",__LINE__,__FUNCTION__);

    for ( k=5; k>0; k-- ) {
        ll_push(&L,NULL,2*k);
    }

    printf("\n[%d] ",__LINE__);
    ll_print("linked_list",__FUNCTION__,&L,NULL,1);

    ll_clean(&L,NULL);
}

void ll_unit_test_pop_head ( void ) {
    LLIST L = {0};
    LNODE * node = NULL;;
    int k;

    printf("[%d]    *** %s ***\n",__LINE__,__FUNCTION__);

    for ( k=5; k>0; k-- ) {
        ll_push(&L,NULL,2*k);
    }

    printf("\n[%d] ",__LINE__);
    ll_print("linked_list",__FUNCTION__,&L,NULL,1);
    node = ll_node_pop_head(&L); 
    printf("Popped node value = %d\n",node->val);
    free(node);
    ll_print("popped_linked_list",__FUNCTION__,&L,NULL,1);

    ll_clean(&L,NULL);
}

void ll_unit_test_pop_tail ( void ) {
    LLIST L = {0};
    LNODE * node = NULL;;
    int k;

    printf("[%d]    *** %s ***\n",__LINE__,__FUNCTION__);

    for ( k=5; k>0; k-- ) {
        ll_push(&L,NULL,2*k);
    }

    printf("\n[%d] ",__LINE__);
    ll_print("linked_list",__FUNCTION__,&L,NULL,1);
    node = ll_node_pop_tail(&L); 
    printf("Popped node value = %d\n",node->val);
    free(node);
    ll_print("popped_linked_list",__FUNCTION__,&L,NULL,1);

    ll_clean(&L,NULL);
}

void ll_unit_test_remove_node ( void ) {
    LLIST L = {0};
    LNODE * node = NULL;;
    int k;

    printf("[%d]    *** %s ***\n",__LINE__,__FUNCTION__);

    for ( k=5; k>0; k-- ) {
        ll_push(&L,NULL,2*k);
    }

    printf("\n[%d] ",__LINE__);
    ll_print("linked_list",__FUNCTION__,&L,NULL,2);

    printf("Removing node 8\n");
    node = ll_node_pop_by_val(&L,8); 
    ll_print_node(node,NULL);
    ll_print("new_linked_list",__FUNCTION__,&L,NULL,2);
    free(node);

    printf("Removing node 10\n");
    node = ll_node_pop_by_val(&L,10); 
    ll_print_node(node,NULL);
    ll_print("new_linked_list",__FUNCTION__,&L,NULL,1);
    free(node);

    ll_clean(&L,NULL);
}

void ll_unit_test_insert_after ( void ) {
    LLIST L = {0};
    LNODE * node = NULL;;
    int k;

    printf("[%d]    *** %s ***\n",__LINE__,__FUNCTION__);

    for ( k=5; k>0; k-- ) {
        ll_push(&L,NULL,2*k);
    }

    ll_print("linked_list",__FUNCTION__,&L,NULL,2);

    printf("Insert value 5 after value 4.\n");
    ll_insert_after(&L,4,NULL,5); /* Insert 5 after 4 */
    ll_print("after_insert",__FUNCTION__,&L,NULL,2);

    printf("Insert value 7 after value 7 (7 isn't in the list).\n");
    ll_insert_after(&L,7,NULL,7); /* Insert 7 after 7 */
    ll_print("after_2nd_insert",__FUNCTION__,&L,NULL,1);

    ll_clean(&L,NULL);
}

/* For use in ll_unit_test_print_data */
static void print_data ( void * data ) {
    char * d = (char*)data;

    printf("'%s'",data); 
}

void ll_unit_test_create_list ( void ) {
    int arr[4] = { 4, 3, 2, 1 } ;
    char * str[4] = { "Test 1", "Test 4", "Test 3", "Test 4" };
    void * varr[4] = { str[3], str[2], str[1], str[0] } ;
    LLIST * list = ll_create(arr,varr,4);

    printf("[%d]    *** %s ***\n",__LINE__,__FUNCTION__);

    ll_print("linked_list",__FUNCTION__,list,print_data,1);

    ll_clean(list,NULL);
    free(list);
}

void ll_unit_test_print_data ( void ) {
    LLIST L = {0};
    char * data[4] = {
        "test data 1",
        "test data 2",
        "test data 3",
        "test data 4" 
    };
    int k;

    printf("[%d]    *** %s ***\n",__LINE__,__FUNCTION__);

    for ( k=4; k>0; k-- ) {
        ll_push(&L,data[k-1],k);
    }
    ll_print("linked_list",__FUNCTION__,&L,print_data,1);

    ll_clean(&L,NULL);
}

void ll_unit_test_all ( void ) {
    char * delim = "----------------------------------------";

    printf("\n%s\n",delim);

    ll_unit_test_print_generic();
    printf("\n%s\n\n",delim);

    ll_unit_test_push();
    printf("\n%s\n\n",delim);

    ll_unit_test_pop_head();
    printf("\n%s\n\n",delim);

    ll_unit_test_pop_tail();
    printf("\n%s\n\n",delim);

    ll_unit_test_insert_after();
    printf("\n%s\n\n",delim);

    ll_unit_test_create_list();
    printf("\n%s\n\n",delim);

    ll_unit_test_print_data();

    printf("\n%s\n\n",delim);
}












