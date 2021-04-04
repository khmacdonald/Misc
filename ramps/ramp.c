#include <stdio.h>

#include "ramp.h"

void print_ramp_model_real(pRAMP_MODEL_R ramp){
    uint64_t n, g, r, c, ni, ng, nr, nc;
    real_t val = 0.0;
    char * delim = "---------------------------------------------";

    if ( !ramp || !(ramp->data) ) {
        return;
    }
    printf("%s\n",delim);
    printf("%s\n",__FUNCTION__);
    printf("(%llu, %llu, %llu, %llu)\n", 
        ramp->n_ints, ramp->ngroups, ramp->nrows, ramp->ncols);

    printf("%s\n",delim);
    for ( n=0; n<ramp->n_ints; ++n ) {
        for ( g=0; g<ramp->ngroups; ++g ) {
            for ( r=0; r<ramp->nrows; ++r ) {
                printf("[");
                for ( c=0; c<ramp->nrows; ++c ) {
                    get_ramp_model_real(&val, ramp, n, g, r, c);
                    printf("%9.5f ",val);
                }
                printf("]\n");
            }
        }
        printf("%s\n",delim);
    }
}

int set_ramp_model_real(
    pRAMP_MODEL_R ramp, real_t val,
    uint64_t n_int, uint64_t group, uint64_t row, uint64_t col)
{
    uint64_t idx;

    if (!ramp || !(ramp->data)){
        return 1;
    }
    if ( n_int >= ramp->n_ints || group >= ramp->ngroups 
        || row >= ramp->nrows || col >= ramp->ncols ) {
        return 2;
    }

    idx = n_int * ramp->group_size
          + group * ramp->image_size
          + row * ramp->ncols
          * col;

    ramp->data[idx] = val;

    return 0;
}

int get_ramp_model_real(
    real_t * val, pRAMP_MODEL_R ramp, 
    uint64_t n_int, uint64_t group, uint64_t row, uint64_t col)
{
    uint64_t idx;
    if (!ramp || !(ramp->data)){
        return 1;
    }
    if ( n_int >= ramp->n_ints || group >= ramp->ngroups 
        || row >= ramp->nrows || col >= ramp->ncols ) {
        return 2;
    }

    idx = n_int * ramp->group_size
          + group * ramp->image_size
          + row * ramp->ncols
          * col;

    *val = ramp->data[idx];
    return 0;
}
