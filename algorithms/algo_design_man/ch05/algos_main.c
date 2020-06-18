/*
Used to test various algorithms. 
Author functions downloaded found at ../../../skiena_algorist
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../common/print_statements.h" /* Formatted print wrappers */

/* Algorithms to test */
#include "ch05_graphs.h"    


int main ( int argc, char ** argv ) {

    unit_test_find_cycles(argc,argv);

    return 0;
}

