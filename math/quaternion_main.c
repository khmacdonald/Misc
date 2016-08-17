#include <stdio.h>

#include "quaternion.h"

int test_print ( void );
int test_div ( void );
int test_inv ( void );

int main ( int argc, char * argv[] )
{
    test_inv();
    return 0;
}

int test_inv ( void )
{
    Q x[4];
    Q inv;
    void (*func[4])( Q x ) = {q_set_1, q_set_i, q_set_j, q_set_k};
    char * label[4] = { "1", "i", "j", "k" };
    char l[64];
    int k;
    
    printf("\n\n");
    for ( k=0; k<4; ++k )
    {
        func[k](x[k]);
        q_inv(inv,x[k]);
        snprintf(l,64,"%s     ",label[k]);
        q_print_label(x[k],l);
        snprintf(l,64,"Inv(%s)",label[k]);
        q_print_label(inv,l);
        printf("\n\n");
    }

    return 0;
}

int test_print ( void )
{
    Q x;

    /* Set x and y to k */
    q_set_k(x);
    q_print_label(x,"x");

    return 0;
}

int test_div ( void )
{
    Q a,inv,x,y;

    /* Set x and y to k */
    q_set_k(x);
    q_print(x);
    printf("\n");

    q_set_k(y);
    q_print(y);
    printf("\n\n");

    /* Divide x by y */
    q_div(a,x,y);

    /* Print the outcome */
    q_print(x);
    printf(" / ");
    q_print(y);
    printf(" = ");
    q_print(a);
    printf("\n");

    return 0;
}
