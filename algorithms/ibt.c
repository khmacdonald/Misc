#include <string.h>

#include "ibt.h"

static void print_tree_rec ( IBT_NODE * node, int level ) {
    if ( NULL==node ) {
        return;
    }

    printf("[Level %d]: parent-%d (",level,node->val);
    if ( node->lchild ) {
        printf("%d",node->lchild->val);
    } else {
        printf("nil");
    }
    printf(",");
    if ( node->rchild ) {
        printf("%d",node->rchild->val);
    } else {
        printf("nil");
    }
    printf(")\n");

    print_tree_rec(node->lchild,level+1);
    print_tree_rec(node->rchild,level+1);
}

void print_tree ( const char * label, IBT * tree ) {
    IBT_NODE * root;
    int level = 0;

    printf("%s_ibt",label);
    if ( NULL==tree || NULL==tree->root ) {
        printf(" = NULL\n");
        return;
    }

    root = tree->root;
    printf(" - root = %d\n",root->val);
    print_tree_rec(root,level+1);

    return;
}

void destroy_tree_rec ( IBT_NODE * node ) {
    if ( NULL==node ) {
        return;
    }
    destroy_tree_rec(node->lchild);
    destroy_tree_rec(node->rchild);
    memset(node,0,sizeof(*node));
    free(node);
    return;
}

void destroy_tree ( IBT * tree, int free_tree ) {
    if ( tree ) {
        if ( tree->root ) {
            destroy_tree_rec(tree->root);
            tree->root = NULL;
        }
        if ( free_tree ) {
            free(tree);
        }
    }
}

int ibt_add_node ( IBT * tree, int n ) {
    IBT_NODE * nnode = NULL;
    IBT_NODE * pnode = NULL;

    if ( NULL==tree ) {
        return 1;
    }
    nnode = calloc(1,sizeof(*nnode));
    nnode->val = n;
    if ( NULL==tree->root ) {
        tree->root = nnode;
        return 0;
    }

    pnode = tree->root;
    while ( 1 ) {
        if ( n < pnode->val ) {
            if ( NULL==pnode->lchild ) {
                nnode->parent = pnode;
                pnode->lchild = nnode;
                return 0;
            }
            pnode = pnode->lchild;
        } else {
            if ( NULL==pnode->rchild ) {
                nnode->parent = pnode;
                pnode->rchild = nnode;
                return 0;
            }
            pnode = pnode->rchild;
        }
    }

    return 0;
}

int ibt_random_tree ( IBT * tree, int n ) {
    if ( NULL==tree ) {
        return 1;
    }

    return 0;
}


/* ---------- Unit Tests ---------- */
void ibt_test_print_tree ( void ) {
    IBT_NODE n5 = { 5, NULL, NULL, NULL };
    IBT_NODE n4 = { 4, NULL, NULL, NULL };
    IBT_NODE n3 = { 3, NULL, NULL, NULL };
    IBT_NODE n2 = { 2, NULL, NULL, NULL };
    IBT_NODE n1 = { 1, NULL, NULL, NULL };
    IBT tree = { &n1 };

    n1.lchild = &n2;
    n1.rchild = &n3;

    n2.parent = &n1;
    n2.lchild = &n4;

    n3.parent = &n1;
    n3.rchild = &n5;

    n4.parent = &n2;
    n5.parent = &n3;

    print_tree(__FUNCTION__,&tree);
}

void ibt_test_add_node ( void ) {
    int k;
    IBT tree = { NULL };

    for ( k=0; k<10; ++k ) {
        if ( ibt_add_node(&tree,k) ) {
            printf("Could not add %d to the tree\n",k);
            exit(1);
        }
    }
    print_tree(__FUNCTION__,&tree);
    destroy_tree(&tree,0);

    ibt_add_node(&tree,50);
    ibt_add_node(&tree,30);
    ibt_add_node(&tree,80);
    ibt_add_node(&tree,40);
    ibt_add_node(&tree,20);
    ibt_add_node(&tree,70);
    ibt_add_node(&tree,90);
    print_tree(__FUNCTION__,&tree);
    destroy_tree(&tree,0);
}
