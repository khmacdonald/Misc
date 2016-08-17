#include "quaternion.h"

void q_print( Q q )
{
    if ( q )
    {
        printf("(%f,%f,%f,%f)",q->a,q->b,q->c,q->d);
    }
}

void q_print_label ( Q q, char * x )
{
    printf("%s = ",x);
    q_print(q);
    printf("\n");
}

void q_init ( Q q )
{
    q->a = 0.0;
    q->b = 0.0;
    q->c = 0.0;
    q->d = 0.0;
}

void q_set_1 ( Q q )
{
    q->a = 1.0;
    q->b = 0.0;
    q->c = 0.0;
    q->d = 0.0;
}

void q_set_i ( Q q )
{
    q->a = 0.0;
    q->b = 1.0;
    q->c = 0.0;
    q->d = 0.0;
}

void q_set_j ( Q q )
{
    q->a = 0.0;
    q->b = 0.0;
    q->c = 1.0;
    q->d = 0.0;
}

void q_set_k ( Q q )
{
    q->a = 0.0;
    q->b = 0.0;
    q->c = 0.0;
    q->d = 1.0;
}

void q_set( Q q, qel_t a, qel_t b, qel_t c, qel_t d )
{
    q->a = a;
    q->b = b;
    q->c = c;
    q->d = d;
}

void q_add( Q a, Q x, Q y )
{
    a->a = x->a + y->a;
    a->b = x->b + y->b;
    a->c = x->c + y->c;
    a->d = x->d + y->d;
}

void q_sub( Q a, Q x, Q y )
{
    a->a = x->a - y->a;
    a->b = x->b - y->b;
    a->c = x->c - y->c;
    a->d = x->d - y->d;
}

void q_mul ( Q a, Q x, Q y )
{
    a->a = (x->a*y->a) - (x->b*y->b) - (x->c*y->c) + (x->d*y->d);
    a->b = (x->a*y->b) + (x->b*y->a) + (x->c*y->d) - (x->d*y->c); 
    a->c = (x->a*y->c) - (x->b*y->d) + (x->c*y->a) + (x->d*y->b); 
    a->d = (x->a*y->d) + (x->b*y->c) - (x->c*y->b) + (x->d*y->a); 
}

void q_div ( Q a, Q x, Q y )
{
    Q inv;
    /* Doesn't seem to work.  Will need to better understand inversion */

    if ( q_is_zero(y) )
    {
        return;
    }
    q_inv(inv,y);
    q_mul(a,x,inv);
}

void q_inv ( Q a, Q x )
{
    qel_t den = x->a*x->a + x->b*x->b + x->c*x->c + x->d*x->d;

    if ( 0==den )
    {
        return;
    }
    a->a = x->a/den;
    a->b = -x->b/den;
    a->c = -x->c/den;
    a->d = -x->d/den;
}

int q_is_zero ( Q x )
{
    int ret=0;

    if ( 0==x->a && 0==x->b && 0==x->c && 0==x->d )
    {
        ret=1;
    }

    return ret;
}




