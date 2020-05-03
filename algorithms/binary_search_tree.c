#include <stdlib.h>
#include <strings.h>

#include "binary_search_tree.h"

#include "../common/print_statements.h"

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
        dbg_print("root = %p, cmp = %p",root,root->cmp);
        return 1; /* Validate arguments */
    }

    /* Find which way the key gets inserted */
    choice = root->cmp(root->key,key); 
    if ( BT_LEFT==choice ) {
        child = root->left;
    } else if ( BT_RIGHT==choice ) {
        child = root->right;
    } else {
        dbg_print("Invalid key\n");
        return 2; /* Invalid key or key already exists */
    }

    /* If at a leaf, add key and value to tree */
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

/* ------------------------------------------------------- */

#define GET_INT(P) *((int*)(P))
#define MAX_LEVEL   128
#define STRSZ       16
struct node_ll { 
    int parent, value;
    char str[STRSZ];
    struct node_ll * next;
};

static void fill_ll ( 
        pBINARY_NODE node, 
        pBINARY_NODE parent, 
        bt_child_t lr,
        struct node_ll ** levels,
        int level ) {
    struct node_ll * lvl;
    struct node_ll * new_ll;

    if ( NULL==node || level>=MAX_LEVEL ) {
        return;
    }
    new_ll = calloc(1,sizeof(*new_ll));
    new_ll->parent = GET_INT(parent->value);
    new_ll->value  = GET_INT(node->value);
    if ( BT_LEFT==lr ) {
        snprintf(new_ll->str,STRSZ,"Left");
    } else {
        snprintf(new_ll->str,STRSZ,"Right");
    }
    lvl = levels[level];
    if ( NULL==lvl ) {
        levels[level] = new_ll;
    } else {
        while ( NULL!=lvl->next ) {
            lvl = lvl->next;
        }
        lvl->next = new_ll;
    }
    fill_ll(node->left,node,BT_LEFT,levels,level+1);
    fill_ll(node->right,node,BT_RIGHT,levels,level+1);

}

void binary_tree_print ( pBINARY_NODE root ) {
    struct node_ll * levels[MAX_LEVEL];
    int level = 0,k;
    struct node_ll * lvl;
    struct node_ll * nlvl;

    memset(levels,0,MAX_LEVEL*sizeof(levels[0]));
    fill_ll(root->left,root,BT_LEFT,levels,0);
    fill_ll(root->right,root,BT_RIGHT,levels,0);

    printf("    Root = %d\n",GET_INT(root->value));
    for ( k=0; k<MAX_LEVEL && NULL!=levels[k]; ++k ) {
        lvl = levels[k];
        printf("Level %d: ",k+1);
        while ( lvl ) {
            nlvl = lvl->next;
            printf("(%d %s %d) ",lvl->parent,lvl->str,lvl->value);
            free(lvl);
            lvl = nlvl;
        }
        printf("\n");
    }

    return;
}
