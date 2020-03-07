#include <stdlib.h>

#include "binary_search_tree.h"

pBINARY_NODE binary_tree_init ( void * key, void * value, bt_cmp_t cmp ) {
    pBINARY_NODE root = calloc(1,sizeof(*root));  /* Allocate root node */

    if ( NULL==root ) {
        return NULL;
    }

    root->key   = key;      /* Set root key */
    root->value = value;    /* Set root value */
    root->cmp   = cmp;      /* Set comparison function */
    root->right = NULL;     /* NULL right child */
    root->left  = NULL;     /* NULL left child */

    return root;
}

int binary_tree_insert ( pBINARY_NODE root, void * key, void * value ) {
    bt_child_t choice = BT_INVALID;
    pBINARY_NODE child = NULL;
    pBINARY_NODE new_child = NULL;

    if ( NULL==root || NULL==root->cmp ) {
        return 1; /* Validate arguments */
    }

    /* Find which way the key gets inserted */
    choice = root->cmp(root->key,key); 
    if ( BT_LEFT==choice ) {
        child = root->left;
    } else if ( BT_RIGHT==choice ) {
        child = root->right;
    } else {
        return 2; /* Invalid key or key already exists */
    }

    /* If at a leave, add key and value to tree */
    if ( NULL==child ) {
        new_child = binary_tree_init(key,value,root->cmp);
        if ( BT_LEFT==choice ) {
            root->left = new_child;
        } else if ( BT_RIGHT==choice ) {
            root->right = new_child;
        } 
    } else {
        /* Not at a leaf, so recurse */
        binary_tree_insert(child,key,value);
    }
   
    return 0;
}

pBINARY_NODE binary_tree_search ( pBINARY_NODE root, void * key ) {
    bt_child_t choice = BT_INVALID;

    if ( NULL==root || NULL==root->cmp ) {
        return NULL; /* Validate arguments */
    }

    choice = root->cmp(root->key,key); 
    if ( BT_SAME==choice ) {
        return root;
    } else if ( BT_RIGHT==choice ) {
        return binary_tree_search(root->right,key);
    } else if ( BT_LEFT==choice ) {
        return binary_tree_search(root->left,key);
    }

    return NULL;
}

