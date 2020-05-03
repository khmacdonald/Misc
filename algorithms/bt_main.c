/*
gcc -c binary_search_tree.c
gcc bt_main.c -o bt_main binary_search_tree.o -I .
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "binary_search_tree.h"
#include "../common/print_statements.h"
#include "../math/brand.h"


pBINARY_NODE create_random_binary_tree ( int size ) ;

int main ( int argc, char ** argv ) {
    int n = 16;         /* The number of nodes */
    pBINARY_NODE root = NULL;

    if ( 1<argc ) {
        n = atoi(argv[1]);
    }

    root = create_random_binary_tree(n); 
    binary_tree_print(root);

    return 0;
}

bt_child_t int_cmp ( void * a, void * b ) {
    int aa = *((int*)a);
    int bb = *((int*)b);
    char * dbg_str = "invalid";
    bt_child_t ret = BT_INVALID;

    if ( aa>bb ) {
        dbg_str = "right";
        ret = BT_RIGHT;
        //return BT_RIGHT;
    } else if ( aa<bb ) {
        dbg_str = "left";
        ret = BT_LEFT;
        //return BT_LEFT;
    } else if ( aa==bb ) {
        dbg_str = "same";
        ret = BT_SAME;
        //return BT_SAME;
    }

    dbg_print("aa = %d, bb = %d, ret = %s\n",aa,bb,dbg_str);

    return ret;
}

pBINARY_NODE create_random_binary_tree ( int size ) {
    pBINARY_NODE root = NULL;
    pBINARY_NODE node = NULL;
    int m, insert = 0;
    uint32_t n;
    uint32_t * num;
    brand_t b;

    //brand_seed_init(b);
    brand_init(b,0xbadfeef);
    num = calloc(1,sizeof(*num));
    n = brand_next(b);
    *num = (n & 0xff);
    root = binary_tree_init(num,num,int_cmp);
    if ( NULL==root ) {
        exit(1);
    }

    size--;
    while ( size>=4 ) {
        n = brand_next(b);
        for ( m=0; m<4; ++m ) {
            num = calloc(1,sizeof(*num));
            *num = (n>>(8*m)) & 0xff;
            //dbg_print("Inserting %u\n",*num);
            if ( 0==binary_tree_insert(root,num,num) ) {
                insert++;
            }
        }
        size -= 4;
    }
    for ( m=0; m<size; ++m ) {
        num = calloc(1,sizeof(*num));
        *num = (n>>(8*m)) & 0xff;
        //dbg_print("Inserting %u\n",*num);
        if ( 0==binary_tree_insert(root,num,num) ) {
            insert++;
        }
    }

    printf("[%d] Inserted %d\n",__LINE__,insert);
    return root;
}
