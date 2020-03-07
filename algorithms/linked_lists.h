#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef enum { LL_BEFORE, LL_NEXT, LL_SAME } ll_choice_t;
typedef ll_choice_t (*ll_cmp_t)(void*,void*);

struct singly_linked_node {
    void * key;
    void * value;
    struct singly_linked_node * next;
};
typedef struct singly_linked_node * pSLINKED_NODE;

struct singly_linked_list {
    ll_cmp_t cmp;
    pSLINKED_NODE root;
};
typedef struct singly_linked_list * pSLINKED_LIST;

/**
 */
pSLINKED_NODE sll_new_node ( void * key, void * value );

/**
 */
pSLINKED_LIST sll_new_list ( void * key, void * value, ll_cmp_t cmp );

/**
 */
int sll_insert_node ( pSLINKED_LIST list, pSLINKED_NODE node );

/**
 */
pSLINKED_NODE sll_find_node ( pSLINKED_LIST list, void * key );

#endif
