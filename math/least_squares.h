#ifndef LEAST_SQUARES_H
#define LEAST_SQUARES_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "khm_common.h"
#include "brand.h"

typedef float lsel;

struct _ls_point
{
    lsel x;
    lsel y;
};

struct _ls
{
    int32_t n;
    lsel sum_x;
    lsel sum_y;
    lsel sum_x2;
    lsel sum_y2;
    lsel sum_xy;
};

typedef struct _ls_point    LSP;
typedef struct _ls_point * pLSP;

typedef struct _ls    LS;
typedef struct _ls * pLS;

#define delete_ls(L) if (L) { free(L); (L)=NULL; }

pLS         new_ls( void );
void        zero_ls ( pLS ls );
khm_error_t add_ls_points ( pLS ls, pLSP p, int32_t psz );
khm_error_t best_line ( lsel * m, lsel * b, pLS ls );
/*
 * Generate n points on a line defined by y = mx+b, with points between
 * x and y, perturbed by standard normal gaussian in 2 dimensions.  In 
 * particular, (x,y) is divided into equal n points, and for each x in 
 * that set, y is computed using y=mx+b, then two random gaussian numbers
 * are generated and added to this set.
 */
khm_error_t generate_random_line ( pLSP p, int32_t n, lsel m, lsel b, lsel x, lsel y );

#endif
