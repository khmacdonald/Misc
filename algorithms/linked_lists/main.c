#include <stdio.h>

#include "stack_queue.h"

int main ( int argc, char ** argv ) {

    char * delim = "----------------------------------------";

    printf("%s\n",delim);

    unit_test_print_q ( ) ;
    printf("%s\n",delim);

    unit_test_push_q ( ) ;
    printf("%s\n",delim);

    unit_test_pop_q ( ) ;
    printf("%s\n",delim);


    return 0;
}
