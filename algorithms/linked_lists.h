#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/**
 * @brief Linked list node comparison values. 
 */
typedef enum { LL_BEFORE, LL_NEXT, LL_SAME } ll_choice_t;

/**
 * @brief Linked list node comparison function. 
 */
typedef ll_choice_t (*ll_cmp_t)(void*,void*); 

/**
 * @brief Singly linked list node.
 */
struct singly_linked_node {
    void * key;                         /**< Node key */
    void * value;                       /**< Node value */
    struct singly_linked_node * next;   /**< Next node */
};

/**
 * @brief Pointer to a singly linked list node.
 */
typedef struct singly_linked_node * pSLINKED_NODE; 

/**
 * @brief Singly linked list data structure.
 */
struct singly_linked_list {
    ll_cmp_t cmp;       /**< Node comparison function. */
    pSLINKED_NODE root; /**< Root of list. */
};

/**
 * @brief Pointer to a singly linked list.
 */
typedef struct singly_linked_list * pSLINKED_LIST;

/**
 * @brief Creates a singly linked list node with key and value.
 *
 * @param key[in] - The key for the node.
 * @param value[in] - The value of the node.
 *
 * @return Pointer to a dynamically allocated node.
 * @return NULL - Upon failure (memory allocation failure).
 */
pSLINKED_NODE sll_new_node ( void * key, void * value );

/**
 * @brief Creates a singly linked list with the root node having key and value.
 *
 * @param key[in] - The key for the node.
 * @param value[in] - The value of the node.
 * @param cmp[in] - The node comparison function.
 *
 * @return Pointer to a dynamically allocated node.
 * @return NULL if failed.
 */
pSLINKED_LIST sll_new_list ( void * key, void * value, ll_cmp_t cmp );

/**
 * @brief Inserts a node into a list using the list key comparison function..
 *
 * @param list[in] - The singly linked list.
 * @param node[in] - The node to be inserted.
 *
 * @return 0 upon successful insertion.
 * @return 1 if failure (bad arguments).
 */
int sll_insert_node ( pSLINKED_LIST list, pSLINKED_NODE node );

/**
 * @brief Find a node in the list using a key (uses list comparison function)..
 *
 * @param list[in] - The list in which to find the node.
 * @param key[in] - The key for the node.
 *
 * @return Pointer to the node with matching key.
 * @return NULL if no node in the list matches the key.
 */
pSLINKED_NODE sll_find_node ( pSLINKED_LIST list, void * key );

/**
 * @brief Removes the node matching the key from the list.
 *
 * @param destroy_list[in] - The list had only one element and it was removed.
 * @param list[in] - The list from which to remove a node.
 * @param key[in] - The key for the node.
 *
 * @return Pointer to the removed node.
 * @return NULL if no node found with key.
 */
pSLINKED_NODE sll_remove_node ( int * destroy_list,pSLINKED_LIST list, void * key );

/**
 * @brief Destroys all nodes in a list, then destroys the list.
 * 
 * @param list[in] - Pointer to a pointer of a linked list.
 * @param destroy_node[in] - function needed to destroy the value/data of a node.
 */
void sll_destroy_list ( pSLINKED_LIST * list, void (*destroy_node)(pSLINKED_NODE) );

int sll_push ( pSLINKED_LIST list, void * value );
pSLINKED_NODE sll_pop( pSLINKED_LIST list, int * destroy_list);

/**
 * @brief Doubly (implemented as circularly) linked list node.
 */
struct doubly_linked_node {
    ll_cmp_t cmp;                       /**< Node key comparison function */
    void * key;                         /**< Node key */
    void * value;                       /**< Node value */
    struct doubly_linked_node * flink;  /**< Next node */
    struct doubly_linked_node * blink;  /**< Next node */
};

/**
 * @brief Doubly linked list data structure, which is just a node.
 */
typedef struct doubly_linked_node * pDLINKED_NODE;

/**
 *
 */
pDLINKED_NODE dll_node_new ( void * key, void * value, ll_cmp_t cmp );

/**
 *
 */
int dll_insert ( pDLINKED_NODE root, void * key, void * value );


#endif

























