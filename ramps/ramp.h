#ifndef RAMP_H
#define RAMP_H

#include <inttypes.h>

typedef double real_t;

struct ramp_model_real {
    uint64_t n_ints;
    uint64_t ngroups;
    uint64_t nrows;
    uint64_t ncols;

    uint64_t image_size;
    uint64_t group_size;
    uint64_t total_size;

    real_t * data;
};

typedef struct ramp_model_real    RAMP_MODEL_R;
typedef struct ramp_model_real * pRAMP_MODEL_R;

void print_ramp_model_real(pRAMP_MODEL_R ramp);

int set_ramp_model_real(
    pRAMP_MODEL_R ramp, real_t val,
    uint64_t n_int, uint64_t group, uint64_t row, uint64_t col);

int get_ramp_model_real(
    real_t * val, pRAMP_MODEL_R ramp, 
    uint64_t n_int, uint64_t group, uint64_t row, uint64_t col);


#endif
