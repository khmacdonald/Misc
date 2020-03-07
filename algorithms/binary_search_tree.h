#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdio.h>

typedef enum { BT_RIGHT, BT_LEFT, BT_INVALID, BT_SAME } bt_child_t;
typedef bt_child_t (*bt_cmp_t)(void*,void*);

/**
 */
struct binary_node {
    void * key;                 /**< Key for binary node */
    void * value;               /**< Value of the node */
    bt_cmp_t cmp;    /**< Comparison function */
    struct binary_node * right; /**< Right child */
    struct binary_node * left;  /**< Left child */
};

typedef struct binary_node    BINARY_NODE;
typedef struct binary_node * pBINARY_NODE;

pBINARY_NODE binary_tree_init ( void * key, void * value, bt_cmp_t cmp );
int binary_tree_insert ( pBINARY_NODE root, void * key, void * value );
pBINARY_NODE binary_tree_search ( pBINARY_NODE root, void * key );


#endif
