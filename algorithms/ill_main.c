#include <stdio.h>
#include <stdlib.h>

#include "int_ll.h"
#include "../common/print_statements.h"

void unit_test_simple_create ( int argc, char ** argv ) ;
void unit_test_random_create ( int argc, char ** argv ) ;
void unit_test_insert_after ( int argc, char ** argv ) ;
void unit_test_insert_before ( int argc, char ** argv ) ;

void unit_test_double_print ( void ) ;
void unit_test_double_push ( void ) ;
void unit_test_double_create ( void ) ;
void unit_test_double_create_random ( void ) ;

/* ------------------------------------------------------- */
int main ( int argc, char ** argv ) { 

    unit_test_double_create_random();

    return 0;
}
/* ------------------------------------------------------- */

void unit_test_simple_create ( int argc, char ** argv ) { 
    ISLL * ll = NULL;
    int n = 5;

    if ( 1<argc ) {
        n = atoi(argv[1]);
    }

    ll = create_simple_isll(n); 
    print_isll(__FUNCTION__,ll);
    destroy_isll(ll);
}

void unit_test_random_create ( int argc, char ** argv ) {
    ISLL * ll = NULL;
    int n = 5;

    if ( 1<argc ) {
        n = atoi(argv[1]);
    }

    ll = create_random_isll(n);
    print_isll(__FUNCTION__,ll);
    destroy_isll(ll);
}

void unit_test_insert_after ( int argc, char ** argv ) {
    int n = 5, val = 8, cmp = 2;
    ISLL * ll = create_simple_isll(n);

    if ( NULL==ll ) {
        err_print("List creation failure\n");
        exit(1);
    }

    print_isll(__FUNCTION__,ll);
    if ( isll_insert_after(ll,val,cmp) ) {
        err_print("Insertion failure\n");
        exit(1);
    }
    print_isll(__FUNCTION__,ll);
    destroy_isll(ll);
}

void unit_test_insert_before ( int argc, char ** argv ) {
    int n = 5, val = 8, cmp = 2;
    ISLL * ll = create_simple_isll(n);

    if ( NULL==ll ) {
        err_print("List creation failure\n");
        exit(1);
    }

    print_isll(__FUNCTION__,ll);
    if ( isll_insert_before(ll,val,cmp) ) {
        err_print("Insertion failure\n");
        exit(1);
    }
    print_isll(__FUNCTION__,ll);
    destroy_isll(ll);
}

/* ------------------------------------------------------- */

void unit_test_double_print ( void ) {
    IDLL ll = { NULL };
    IDLL_NODE n1 = { 1, NULL, NULL } ;
    IDLL_NODE n2 = { 2, NULL, NULL } ;
    IDLL_NODE n3 = { 3, NULL, NULL } ;
    IDLL_NODE n4 = { 4, NULL, NULL } ;
    IDLL_NODE n5 = { 5, NULL, NULL } ;

    ll.root = &n1;

    n1.blink = &n5;
    n1.flink = &n2;

    n2.blink = &n1;
    n2.flink = &n3;

    n3.blink = &n2;
    n3.flink = &n4;

    n4.blink = &n3;
    n4.flink = &n5;

    n5.blink = &n4;
    n5.flink = &n1;

    print_idll(__FUNCTION__,&ll);
}

void unit_test_double_push ( void ) {
    IDLL * ll = calloc(1,sizeof(*ll));
    
    push_idll(ll,5);
    push_idll(ll,4);
    push_idll(ll,3);
    push_idll(ll,2);
    push_idll(ll,1);

    print_idll(__FUNCTION__,ll);
    destroy_idll(ll);
}

void unit_test_double_create ( void ) {
    IDLL * ll = NULL;
    int n = 5;

    ll = create_simple_idll(n); 
    print_idll(__FUNCTION__,ll);
    destroy_idll(ll);
}

void unit_test_double_create_random ( void ) {
    IDLL * ll = NULL;
    int n = 5;

    ll = create_random_idll(n); 
    print_idll(__FUNCTION__,ll);
    destroy_idll(ll);
}









