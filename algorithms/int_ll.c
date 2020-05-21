#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "int_ll.h"
#include "../common/print_statements.h"

void print_isll ( const char * label, ISLL * ll ) {
    ISLL_NODE * node = NULL;

    /* Check inputs */
    if ( NULL==ll || NULL==ll->root ) {
        return;
    }
    
    /* Print the label and the list, node by node */
    node = ll->root;
    printf("%s = %d",label,node->val);
    for ( node = node->next; NULL!=node; node = node->next ) {
        printf(" -> %d",node->val);
    }
    printf("\n");
}

void destroy_isll ( ISLL * ll, int free_ll ) {
    ISLL_NODE * node = NULL;
    ISLL_NODE * nnode = NULL;

    /* Check inputs */
    if ( NULL==ll ) {
        return;
    }

    /* Get root node and free the list data structure */
    node = ll->root;
    if ( free_ll ) {
        free(ll);
        ll = NULL;
    }

    /* Free each non-NULL node */
    while ( node ) {
        nnode = node->next;
        free(node);
        node = nnode;
    }
}

ISLL * create_isll ( int root ) {
    ISLL * ll = calloc(1,sizeof(*ll));
    ISLL_NODE * node = NULL;

    /* Check memory allocation */
    if ( NULL==ll ) {
        return NULL;
    }
    node = calloc(1,sizeof(*node));
    if ( NULL==node ) {
        free(ll);
        return NULL;
    }

    /* Set the node as the root node */
    ll->root = node;
    node->val = root;
    node->next = NULL;

    return ll;
}

ISLL * create_simple_isll ( int n ) {
    ISLL * ll = calloc(1,sizeof(*ll));
    int k;

    /* Check memory allocation */
    if ( NULL==ll ) {
        return NULL;
    }

    /* 
     * Create a node and push it on the list.  The count down
     * in the loop is to make the list in order that starts
     * at 1.
     */
    for ( k=n; k>0; --k ) {
        if ( push_isll(ll,k) ) {
            destroy_isll(ll,1);
            return NULL;
        }
    }

    return ll;
}

ISLL * create_random_isll ( int n ) {
    ISLL * ll = calloc(1,sizeof(*ll));
    int k,rnd;

    /* check memory allocation */
    if ( NULL==ll ) {
        return NULL;
    }

    /* Seed random number generator */
    srand(time(NULL));
    for ( k=0; k<n; ++k ) {
        /* Create a random value less than 1000 and push it onto the list */
        rnd = (rand() & 0x7fffffff) % 1000;
        if ( push_isll(ll,rnd) ) {
            destroy_isll(ll,1);
            return NULL;
        }
    }

    return ll;
}

ISLL_NODE * pop_isll ( ISLL * ll ) {
    ISLL_NODE * node = NULL;

    /* Check inputs */
    if ( NULL==ll || NULL==ll->root ) {
        return NULL;
    }

    /* Pop the root of the list and set the next node as the root */
    node = ll->root;
    ll->root = node->next;

    return node;
}

int push_isll ( ISLL * ll, int n ) {
    ISLL_NODE * node = NULL;

    /* Check the input */
    if ( NULL==ll ) {
        return 1;
    }

    /* Allocate a new node */
    node = calloc(1,sizeof(*node));
    if ( NULL==node ) {
        return 2;
    }

    /* Set the value and push it onto the list */
    node->val = n;
    if ( ll->root ) {
        node->next = ll->root;
    } 
    ll->root = node;

    return 0;
}

/* Inserts a value after the first value less than cmp */
int isll_insert_after ( ISLL * ll, int val, int cmp ) {
    ISLL_NODE * node = NULL;
    ISLL_NODE * nnode = NULL;

    if ( NULL==ll ) {
        return 1;
    }

    if ( NULL==ll->root ) {
        return push_isll(ll,val);
    }

    node = ll->root;
    nnode = calloc(1,sizeof(*nnode));
    if ( NULL==nnode ) {
        return 2;
    }
    nnode->val = val;
    while ( node ) {
        if ( node->val < cmp || NULL==node->next ) {
            nnode->next = node->next;
            node->next = nnode;
            return 0;
        }
        node = node->next;
    }
    return 0; /* Should never get here */
}

int isll_insert_before ( ISLL * ll, int val, int cmp ) {
    ISLL_NODE * node = NULL;
    ISLL_NODE * nnode = NULL;

    if ( NULL==ll ) {
        return 1;
    }

    if ( NULL==ll->root || cmp < ll->root->val ) {
        return push_isll(ll,val);
    }

    node = ll->root;
    nnode = calloc(1,sizeof(*node));
    nnode->val = val;
    while ( node ) {
        if ( NULL==node->next ) {
            node->next = nnode;
            return 0;
        }
        if ( cmp < node->next->val ) {
            nnode->next = node->next;
            node->next = nnode;
            return 0;
        }
        node = node->next;
    }
    return 0; /* Should never get here */
}

/* -------------------------------------------------------------------------- */
void print_idll ( const char * label, IDLL * ll ) {
    IDLL_NODE * root = NULL;
    IDLL_NODE * cnode = NULL;

    if ( NULL==ll || NULL==ll->root ) {
        printf("%s_list = NULL\n",label);
        return;
    }
    root = ll->root;
    printf("%s_circular_list = %d",label,root->val);
    cnode = root->flink;

    while ( cnode!=root ) {
        printf(" -> %d",cnode->val);
        cnode = cnode->flink;
        if ( cnode==root ) {
            break;
        }
    }
    printf(" ->\n");
}

void destroy_idll ( IDLL * ll, int free_ill ) {
    IDLL_NODE * root = NULL;
    IDLL_NODE * cnode = NULL;
    IDLL_NODE * nnode = NULL;

    if ( NULL==ll ) {
        return;
    }
    root = ll->root;
    cnode = ll->root;
    if ( free_ill ) {
        free(ll);
    }
    while ( 1 ) { 
        nnode = cnode->flink;
        free(cnode);
        if ( nnode==root ) {
            break;
        }
        cnode = nnode;
    }
}

IDLL * create_simple_idll ( int n ) {
    IDLL * ll = calloc(1,sizeof(*ll));
    IDLL_NODE * node = NULL;
    int k;

    if ( NULL==ll ) {
        return NULL;
    }

    for ( k=n; k>0; --k ) {
        if ( push_idll(ll,k) ) {
            destroy_idll(ll,1);
            return NULL;
        }
    }

    return ll;
}

IDLL * create_random_idll ( int n ) {
    IDLL * ll = calloc(1,sizeof(*ll));
    int k,rnd;

    /* check memory allocation */
    if ( NULL==ll ) {
        return NULL;
    }

    /* Seed random number generator */
    srand(time(NULL));
    for ( k=0; k<n; ++k ) {
        /* Create a random value less than 1000 and push it onto the list */
        rnd = (rand() & 0x7fffffff) % 1000;
        if ( push_idll(ll,rnd) ) {
            destroy_idll(ll,1);
            return NULL;
        }
    }

    return ll;
}

IDLL_NODE * pop_idll ( IDLL * ll ) {
    IDLL_NODE * node = NULL;

    if ( NULL==ll || NULL==ll->root ) {
        return NULL;
    }
    
    node = ll->root;
    if ( ll->root->blink == ll->root ) {
        ll->root = NULL;
    } else {
        ll->root = node->flink;
        ll->root->blink = node->blink;
    }
    node->flink = node;
    node->blink = node;

    return node;
}

int push_idll ( IDLL * ll, int n ) {
    IDLL_NODE * root = NULL;
    IDLL_NODE * node = NULL;

    if ( NULL==ll ) {
        return 1;
    }

    node = calloc(1,sizeof(*node));
    if ( NULL==node ) {
        return 2;
    }

    /* Insert new node as root */
    node->val = n;
    if ( NULL==ll->root ) {
        node->blink = node;
        node->flink = node;
        ll->root = node;
        return 0;
    }

    root = ll->root;

    /* Add note as root */
    node->flink = root;
    node->blink = root->blink;

    /* Adjust forward and backwards links */
    node->blink->flink = node;
    node->flink->blink = node;

    ll->root = node;

    return 0;
}

int rotate_idll ( IDLL * ll, int n ) {
    IDLL_NODE * node = NULL;
    int cnt=0;

    if ( NULL==ll || NULL==ll->root ) {
        return 1;
    }

    node = ll->root;
    for ( cnt=0; cnt<n; ++cnt ) {
        node = node->flink;
    }

    ll->root = node;

    return 0;
}

/* ----------------------------------------------------------------- */
/*                            UNIT TESTS                             */
void unit_test_simple_create ( int argc, char ** argv ) { 
    ISLL * ll = NULL;
    int n = 5;

    if ( 1<argc ) {
        n = atoi(argv[1]);
    }

    ll = create_simple_isll(n); 
    print_isll(__FUNCTION__,ll);
    destroy_isll(ll,1);
}

void unit_test_random_create ( int argc, char ** argv ) {
    ISLL * ll = NULL;
    int n = 5;

    if ( 1<argc ) {
        n = atoi(argv[1]);
    }

    ll = create_random_isll(n);
    print_isll(__FUNCTION__,ll);
    destroy_isll(ll,1);
}

void unit_test_insert_after ( int argc, char ** argv ) {
    int n = 5, val = 8, cmp = 2;
    ISLL * ll = create_simple_isll(n);

    if ( NULL==ll ) {
        err_print("List creation failure\n");
        exit(1);
    }

    print_isll(__FUNCTION__,ll);
    if ( isll_insert_after(ll,val,cmp) ) {
        err_print("Insertion failure\n");
        exit(1);
    }
    print_isll(__FUNCTION__,ll);
    destroy_isll(ll,1);
}

void unit_test_insert_before ( int argc, char ** argv ) {
    int n = 5, val = 8, cmp = 2;
    ISLL * ll = create_simple_isll(n);

    if ( NULL==ll ) {
        err_print("List creation failure\n");
        exit(1);
    }

    print_isll(__FUNCTION__,ll);
    if ( isll_insert_before(ll,val,cmp) ) {
        err_print("Insertion failure\n");
        exit(1);
    }
    print_isll(__FUNCTION__,ll);
    destroy_isll(ll,1);
}

/* ------------------------------------------------------- */

void unit_test_double_print ( void ) {
    IDLL ll = { NULL };
    IDLL_NODE n1 = { 1, NULL, NULL } ;
    IDLL_NODE n2 = { 2, NULL, NULL } ;
    IDLL_NODE n3 = { 3, NULL, NULL } ;
    IDLL_NODE n4 = { 4, NULL, NULL } ;
    IDLL_NODE n5 = { 5, NULL, NULL } ;

    ll.root = &n1;

    n1.blink = &n5;
    n1.flink = &n2;

    n2.blink = &n1;
    n2.flink = &n3;

    n3.blink = &n2;
    n3.flink = &n4;

    n4.blink = &n3;
    n4.flink = &n5;

    n5.blink = &n4;
    n5.flink = &n1;

    print_idll(__FUNCTION__,&ll);
}

void unit_test_double_push ( void ) {
    IDLL * ll = calloc(1,sizeof(*ll));
    
    push_idll(ll,5);
    push_idll(ll,4);
    push_idll(ll,3);
    push_idll(ll,2);
    push_idll(ll,1);

    print_idll(__FUNCTION__,ll);
    destroy_idll(ll,1);
}

void unit_test_double_create ( void ) {
    IDLL * ll = NULL;
    int n = 5;

    ll = create_simple_idll(n); 
    print_idll(__FUNCTION__,ll);
    destroy_idll(ll,1);
}

void unit_test_double_create_random ( void ) {
    IDLL * ll = NULL;
    int n = 5;

    ll = create_random_idll(n); 
    print_idll(__FUNCTION__,ll);
    destroy_idll(ll,1);
}

void unit_test_double_rotate ( void ) {
    IDLL * ll = NULL;
    int n = 8;

    ll = create_simple_idll(n); 
    print_idll(__FUNCTION__,ll);
    rotate_idll(ll,4); 
    print_idll("Rotated_by_4",ll);
    destroy_idll(ll,1);

    printf("\n\n");

    ll = calloc(1,sizeof(*ll));
    push_idll(ll,9);
    push_idll(ll,8);
    push_idll(ll,7);
    push_idll(ll,4);
    push_idll(ll,2);
    print_idll(__FUNCTION__,ll);
    rotate_idll(ll,3); 
    print_idll("Rotated_by_4",ll);
    destroy_idll(ll,1);

}









