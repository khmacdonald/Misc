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

void destroy_list ( pSLINKED_LIST * p_list, void (*destroy_node)(pSLINKED_NODE) ) {
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
        destroy_node(cnode);
        cnode = next;
    }
}






















