
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int * shuffle ( int n ) ;

#if 0
int main ( int argc, char ** argv ) {
    int n = 10,k;
    int * arr = NULL;

    if ( 1<argc ) {
        n = atoi(argv[1]);
    }

    arr = shuffle(n);

    printf("arr = { %d",arr[0]);
    for ( k=1; k<n; ++k ) {
        printf(", %d",arr[k]);
    }
    printf(" }\n");

    free(arr);
    return 0;
}
#endif

struct node { 
    int val;
    int key;
    struct node * next;
};

struct ll { 
    struct node * root;
};

void insert_node ( struct ll * LL, struct node * node ) {
    struct node * cnode = NULL;

    if ( NULL==LL->root ) {
        LL->root = node;
        return;
    }
    if ( LL->root->key < node->key ) {
        node->next = LL->root;
        LL->root = node;
        return;
    }
    cnode = LL->root;
    
    while ( cnode ) {
        if ( NULL==cnode->next ) {
            cnode->next = node;
            return;
        }
        if ( cnode->key < node->key && node->key < cnode->next->key ) {
            node->next = cnode->next;
            cnode->next = node;
            return;
        }
        cnode = cnode->next;
    }
    return;
}

int * shuffle ( int n ) {
    int k,rnd;
    int * arr = NULL;
    struct ll LL;
    struct node * node = NULL;
    struct node * cnode = NULL;

    LL.root = NULL;
    srand(time(NULL));

    for ( k=0; k<n; ++k ) {
        rnd = rand();
        node = calloc(1,sizeof(*node));
        node->val = k+1;
        node->key = rnd;
        node->next = NULL;
        insert_node(&LL,node);
    }
    arr = calloc(n,sizeof(*arr));
    cnode = LL.root;
    for ( k=0; k<n; ++k ) {
        arr[k] = cnode->val;
        node = cnode->next;
        free(cnode);
        cnode = node;
    }

    return arr;
}












