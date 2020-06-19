#include <stdio.h>

#include "linked_list.h"

int main ( int argc, char ** argv ) {

    char * delim = "----------------------------------------";

    printf("\n%s\n\n",delim);

    ll_unit_test_remove_node();

    printf("\n%s\n\n",delim);

    return 0;
}
