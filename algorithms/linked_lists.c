#include <stdlib.h>

#include "linked_lists.h"

#
pSLINKED_NODE sll_new_node ( void * key, void * value ) {
    pSLINKED_NODE node = calloc(1,sizeof(*node));
    if ( NULL==node ) {
        return NULL;
    }

    node->key   = key;
    node->value = value;
    node->next  = NULL;

    return 0;
}

pSLINKED_LIST sll_new_list ( void * key, void * value, ll_cmp_t cmp ) {
    pSLINKED_LIST list = NULL;
    pSLINKED_NODE node = sll_new_node(key,value);
    if ( NULL==node ) {
        return NULL;
    }

    list = calloc(1,sizeof(*list));
    if ( NULL==list ) {
        free(node);
    }

    list->root = node;
    list->cmp = cmp;

    return 0;
}

int insert_node_not_as_root ( 
        pSLINKED_NODE cnode, 
        pSLINKED_NODE node, 
        ll_cmp_t cmp ) {
    pSLINKED_NODE next;

    while ( cnode ) {
        if ( NULL==cnode->next ) {
            /* Insert node as a leaf */
            cnode->next = node;
            node->next = NULL;
            return 0;
        }
        if ( LL_NEXT!=cmp(next,node) )
        {
            /* Insert node between current node and next node */
            node->next = cnode->next;
            cnode->next = node;
            return 0;
        }
        cnode = next;
    }

    return 0;
}

int sll_insert_node ( 
        pSLINKED_LIST list, 
        pSLINKED_NODE node ) {
    if ( NULL==list || NULL==list->cmp || NULL==node ) {
        return 1;
    }

    if ( LL_NEXT!=list->cmp(list->root,node) )
    {
        node->next = list->root;
        list->root = node;
        return 0;
    }

    return insert_node_not_as_root(list->root,node,list->cmp);
}

pSLINKED_NODE sll_find_node ( pSLINKED_LIST list, void * key ) {
    pSLINKED_NODE cnode = NULL;

    if ( NULL==list || NULL==list->cmp || NULL==list->root ) {
        return NULL;
    }

    cnode = list->root;
    while ( cnode ) {
        if ( LL_SAME==list->cmp(cnode->key,key) ) {
            return cnode;
        }
        cnode = cnode->next;
    }

    return NULL;
}

static pSLINKED_NODE remove_root ( int * destroy_list, pSLINKED_LIST list ) {
    pSLINKED_NODE cnode = list->root;
    if ( NULL==list->root->next ) {
        /* list has only size of 1, so removing it empties it. */ 
        *destroy_list = 1; 
    } else {
        /* Remove the root */
        list->root = cnode->next;
    }
    return cnode;
}

static pSLINKED_NODE remove_non_root_node ( pSLINKED_LIST list, void * key ) {
    pSLINKED_NODE cnode = list->root;

    while ( NULL!=cnode ) {
        if ( NULL==cnode->next ) {
            break;  /* No node found */
        }
        if ( LL_SAME==list->cmp(cnode->next->key,key) ) {
            cnode->next = cnode->next->next;
            return cnode->next;
        }
    }

    return NULL;
}

pSLINKED_NODE sll_remove_node ( 
        int * destroy_list,
        pSLINKED_LIST list, 
        void * key ) {

    if ( NULL==list || NULL==destroy_list) {
        return NULL;
    }

    *destroy_list = 0;
    if ( LL_SAME==list->cmp(list->root->key,key) ) {
        return remove_root(destroy_list,list);
    }

    return remove_non_root_node(list,key);;
}

void sll_destroy_list ( pSLINKED_LIST * p_list, void (*destroy_node)(pSLINKED_NODE) ) {
    pSLINKED_NODE cnode = NULL, next = NULL;
    pSLINKED_LIST list = NULL;;

    if ( NULL==p_list ) {
        return;
    }
    list = *p_list;
    *p_list = NULL;
    if ( NULL==list ) {
        return;
    }
    cnode = list->root;
    free(list);
    while ( cnode ) {
        next = cnode->next;
        destroy_node(cnode->value);
        free(cnode);
        cnode = next;
    }
}

int sll_push ( pSLINKED_LIST list, void * value ) {
    pSLINKED_NODE new_root = NULL, old_root;
    if ( NULL==list ) {
        return 1;
    }

    old_root = list->root;
    new_root = calloc(1,sizeof(*new_root));
    if ( NULL==new_root ) {
        return 2;
    }

    new_root->value = value;

    new_root->next = old_root;
    list->root = new_root;

    return 0;
}

pSLINKED_NODE sll_pop( pSLINKED_LIST list, int * destroy_list) {
    pSLINKED_NODE node = NULL;
    if ( NULL==list ) {
        return NULL;
    }

    *destroy_list = 0;
    node =  list->root;
    if ( NULL==node->next ) {
        *destroy_list = 1;
    }
    list->root = node->next;

    return node;
}

pDLINKED_NODE dll_node_new ( void * key, void * value, ll_cmp_t cmp ) {
    pDLINKED_NODE node = calloc(1,sizeof(*node)); 
    if ( NULL==node ) {
        return NULL;
    }

    node->key   = key;
    node->value = value;
    node->cmp   = cmp;

    /* Initialize as a circular linked list with only one element. */
    node->flink = node;
    node->blink = node;

    return node;
}

static int dll_insert_next ( pDLINKED_NODE cnode, pDLINKED_NODE node ) {
    /* 
     * Adjust the new node forward and backward link to put the
     * new node between the cnode and the next node.
     */
    node->blink = cnode;
    node->flink = cnode->flink;

    /* 
     * Adjust the forward link of the current node and the backwards
     * link of the next node.
     */
    cnode->flink->blink = node;
    cnode->flink = node;

    return 0;
}

int dll_insert_node ( pDLINKED_NODE cnode, pDLINKED_NODE node ) {
    pDLINKED_NODE last = cnode->flink;

    /* TODO */

    return 0;
}

int dll_insert ( pDLINKED_NODE root, void * key, void * value ) {
    pDLINKED_NODE node = NULL;

    if ( NULL==root ) {
        return 1;
    }

    node = dll_node_new(key,value,root->cmp);
    if ( NULL==node ) {
        return 2;
    }
    /* 
     * Insert just after root if:
     * 1. Size of list is 1.
     * 2. No comparison function.
     */
    if ( root->flink==root->blink ||            
         NULL==root->cmp ) {
        return dll_insert_next(root,node);
    }

    return dll_insert_node(root,node);;
}





















