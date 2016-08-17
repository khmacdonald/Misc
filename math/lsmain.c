#include <stdio.h>

#include "brand.h"
#include "khm_common.h"
#include "least_squares.h"

void print_points ( pLSP p, int32_t n );
void print_point ( pLSP p );

#define NUM_POINTS      16
int main ( int argc, char * argv[] )
{
    pLS ls = new_ls();
    LSP p[NUM_POINTS] = {0};
    brand_t ctx;
    int32_t k;
    lsel x = 0.0,m,b;
    lsel m0 = 1.0, b0 = 5.0;
    lsel x0 = 5.0, y0 = 105.0;
    
#if 0
    memset(p,0,NUM_POINTS*sizeof(p[0]));
    if ( ls )
    {
        info_print("Allocation complete");
    }

    delete_ls(ls);
#endif
    brand_seed_init(ctx);
    generate_random_line(p,NUM_POINTS,m0,b0,x0,y0);
    print_points(p,NUM_POINTS);
    add_ls_points(ls,p,NUM_POINTS);
    best_line(&m,&b,ls);

    printf("m = %f, b = %f\n",m,b);

    return 0;
}

void print_points ( pLSP p, int32_t n )
{
    int32_t k;

    if ( NULL==p || n<1 )
    {
        goto END;
    }

    for ( k=0; k<n; ++k )
    {
        print_point(&p[k]);
        printf("\n");
    }

END:
    return;
}

void print_point ( pLSP p )
{
    if ( NULL==p )
    {
        goto END;
    }

    printf("(%f,%f)",p->x,p->y);

END:
    return;
}







