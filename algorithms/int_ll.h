#ifndef INTEGER_LINKED_LIST_H
#define INTEGER_LINKED_LIST_H

/* Integer singly linked list */
struct _isll_node {
    int val;
    struct _isll_node * next;
};
typedef struct _isll_node ISLL_NODE;

struct _isll {
    struct _isll_node * root;
};
typedef struct _isll ISLL;

/* 
 * Create an integer singly linked list with root set as the value
 * of the root.
 */
ISLL * create_isll ( int root ) ;

/* Creates a linked list with each value 1-n in order. */
ISLL * create_simple_isll ( int n ) ;

/* Creates a random linked list */
ISLL * create_random_isll ( int n ) ;

/* Destroys all allocated memory associated with the linked list. */
void destroy_isll ( ISLL * ll ) ;

/* Prints the linked list. */
void print_isll ( const char * label, ISLL * ll ) ;

/* Insert 'val' into a linked list after the first value less than 'cmp'. */
int isll_insert_after ( ISLL * ll, int val, int cmp ) ;

/* Insert 'val' into a linked list before the first value greater than 'cmp'. */
int isll_insert_before ( ISLL * ll, int val, int cmp ) ;

/* Pop the root off a list */
ISLL_NODE * pop_isll ( ISLL * ll ) ;

/* Push a value onto a list */
int push_isll ( ISLL * ll, int n ) ;

/* -------------------------------------------------------------------------- */

/* Doubly linked list */
struct _idll_node { 
    int val;
    struct _idll_node * blink;
    struct _idll_node * flink;
};
typedef struct _idll_node IDLL_NODE;

struct _idll {
    struct _idll_node * root;
};
typedef struct _idll IDLL;

/* Deallocates all dynamically allocated memory */
void destroy_idll ( IDLL * ll ) ;

/* Prints the linked list. */
void print_idll ( const char * label, IDLL * ll ) ;

/* Creates a doubly linked list with each value 1-n in order. */
IDLL * create_simple_idll ( int n ) ;

/* Creates a doubly linked list with random values */
IDLL * create_random_idll ( int n ) ;

/* Pop the root off a list */
IDLL_NODE * pop_idll ( IDLL * ll ) ;

/* Push a value onto a list */
int push_idll ( IDLL * ll, int n ) ;



#endif
