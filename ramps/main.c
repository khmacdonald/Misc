#include <stdio.h>

#include "ramp.h"
#include "unit_test.h"

int main ( int argc, char ** argv ) {
    pRAMP_MODEL_R ramp = zero_ramp_model_real(1, 2, 2, 2);

    print_ramp_model_real(ramp);
    if ( set_ramp_model_real(ramp, 1.0, 0, 0, 0, 0) ) {
        printf("Bad set\n");
    } else {
        printf("Good set\n");
    }
    print_ramp_model_real(ramp);

    return 0;
}
