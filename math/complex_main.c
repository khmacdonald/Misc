#include <stdint.h>
#include <stdio.h>

#include "khm_common.h"
#include "complex.h"

int32_t main ( int32_t argc, char * argv[] )
{
    complex_t x,y,z;

    complex_init(x,1.0,0.0);
    complex_init(y,0.0,1.0);
    complex_mul(z,y,y);

    complex_exp(z,y,10);
    dbg_print("exp of");
    dbg_complex_print(y);
    dbg_print("is");
    dbg_complex_print(z);

    return 0;
}
