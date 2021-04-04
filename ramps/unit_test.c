#include <stdlib.h>

#include "unit_test.h"

pRAMP_MODEL_R zero_ramp_model_real(
    uint64_t n_ints, uint64_t ngroups, uint64_t nrows, uint64_t ncols)
{
    real_t * data = NULL;
    pRAMP_MODEL_R ramp = (pRAMP_MODEL_R)calloc(1,sizeof(*ramp)); 

    ramp->n_ints    = n_ints;
    ramp->ngroups   = ngroups;
    ramp->nrows     = nrows;
    ramp->ncols     = ncols;

    ramp->image_size = ramp->nrows * ramp->ncols;
    ramp->group_size = ramp->ngroups * ramp->image_size;
    ramp->total_size = ramp->n_ints * ramp->group_size;

    data = (real_t*)calloc(ramp->total_size, sizeof(*data));
    ramp->data = data;

    return ramp;
}
