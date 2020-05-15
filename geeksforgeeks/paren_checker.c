/*
https://practice.geeksforgeeks.org/problems/parenthesis-checker/0

Check to make sure a string of {, }, [, ], (, and ) is balanced.  
For example, [()]{}{[()()]()} is balanced, but [(]) is not.
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char c;
    struct node * next;
};

struct LL  {
    struct node * root;
};
void print_list ( struct LL * ll ) ;
void push ( struct LL * LL, char c ) ;
void pop ( struct LL * LL ) ;


void test_case ( char * str ) ;

/* ------------------------------------------- */

int main ( int argc, char ** argv ) {
    char * str1 = "[()]{}{[()()]()}";
    char * str2 = "[(])";

    if ( 1<argc ) {
        test_case(argv[1]);
    } else {
        test_case(str1);
        test_case(str2);
    }

    return 0;
}

/* ------------------------------------------- */

int is_open_bracket ( char c ) {
    if ( '['==c || '{'==c || '('==c ) {
        return 1;
    }
    return 0;
}

int is_closed_bracket ( char c ) {
    if ( ']'==c || '}'==c || ')'==c ) {
        return 1;
    }
    return 0;
}

int is_match ( char c1, char c2 ) {
    if ( ']'==c1 && '['==c2 ) {
        return 1;
    } else if ( '}'==c1 && '{'==c2) {
        return 1;
    } else if ( ')'==c1 && '('==c2) {
        return 1;
    }
    return 0;
}

void test_case ( char * str ) {
    struct LL ll = {NULL};
    int k,slen = strlen(str);
    int unbalanced = 0;

    printf("    **** Test ****\n\n");
    printf("Test string: \"%s\"\n",str);
    for ( k=0; k<slen; ++k ) {
        if ( is_open_bracket(str[k]) ) {
            push(&ll,str[k]);
        } else if ( is_closed_bracket(str[k]) ) {
            if ( NULL!=ll.root && is_match(str[k],ll.root->c) ) {
                pop(&ll);
            } else {
                //printf("\nUnbalanced (%d,%c)\n",k,str[k]);
                unbalanced = 1;
                goto END;
            }
        }
    }

END:
    if ( NULL!=ll.root || unbalanced ) {
        printf("    -> Unbalanced\n");
    } else {
        printf("    -> Balanced\n");
    }

    printf("\n\n");
}

/* ------------------------------------------- */

void print_list ( struct LL * ll ) {
    struct node * node = ll->root;
    int k;

    printf("List = ");
    if ( NULL==node ) {
        printf("NULL\n");
        return;
    }
    for ( k=0; NULL!=node; ++k ) {
        if ( 0==k ) {
            printf("%c",node->c);
        } else {
            printf(" -> %c",node->c);
        }
        node = node->next;
    }
    printf("\n");
}
void push ( struct LL * LL, char c ) {
    struct node * node = calloc(1,sizeof(*node));

    node->c = c; 
    node->next = LL->root;
    LL->root = node;
}

void pop ( struct LL * LL ) {
    struct node * node = LL->root;

    if ( node ) {
        LL->root = node->next;
        free(node);
    }
}

