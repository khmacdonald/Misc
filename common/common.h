#ifndef MY_COMMON_H
#define MY_COMMON_H

#include <stdint.h>

int * c_random_array ( int n, int positive, int mod ) ;
uint8_t * c_random_byte_array ( int n ) ;

void c_print_array_bytes ( uint8_t * b, int n, int new_line ) ;
void c_print_array_int ( int * b, int n, int new_line ) ;
void c_print_array_int_lbl ( char * label, int * b, int n, int new_line ) ;

void c_reverse_bytes ( uint8_t * b, int n ) ;

void c_print_formated_integer ( FILE * fd, int x ) ;

/* Unit tests */
void c_unit_test_random_array ( int argc, char ** argv ) ; 

void c_unit_test_array_bytes ( int argc, char ** argv ) ; 
void c_unit_test_array_int ( int argc, char ** argv ) ; 
void c_unit_test_array_int_lbl ( int argc, char ** argv ) ; 

void c_unit_test_reverse_bytes ( int argc, char ** argv ) ; 

void c_unit_test_print_formated_integer ( int argc, char ** argv ) ; 

#endif
