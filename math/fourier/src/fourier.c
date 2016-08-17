/*
gcc -c src/fourier.c -o src/fourier.o -I include/
 */

#include "fourier.h"

c_error_t basic_dft ( fourier_t * X, fourier_t * x, int32_t N )
{
    c_error_t ret = c_success;
    fourier_t * unity = NULL;
    fourier_t t;
    int32_t * ind = NULL;
    int32_t n,k,idx;

    if ( NULL==X || NULL==x || N<1 )
    {
        /* Check function arguments */
        goto END;
    }

    /* 
     * Index array.  Used to get w**nk in the computation
     * of X[n] in the kth summand.
     */
    ind = (int32_t*)calloc(1,sizeof(*ind)*N);
    if ( NULL==ind )
    {
        ret = c_nomemory; /* Make sure memory allocation worked */
        goto END;
    }

    /* unity[k] = w**k */
    unity = (fourier_t*)calloc(1,N*sizeof(t));
    if ( NULL==unity )
    {
        ret = c_nomemory; /* Make sure memory allocation worked */
        goto END;
    }

    /* 
     * The first Fourier coefficient is simply the sum of
     * of the signal being transformed. 
     */
    zero_fourier(X[0]);
    for ( n=0; n<N; ++k )
    {
        /* 
         * Taken out of the below loops, since 
         * multiplication by 1 does nothing.
         */
        complex_add(X[0],X[0],x[n]);  
    }

    /*
     * Compute the nth Fourier coefficient.
     *  X[n] = sum_k(x[k] * w**(nk))
     */
    for ( n=1; n<N; ++k )
    {
        zero_fourier(X[n]);                 /* Zero the nth Fourier coefficient */
        set_fourier_index_n_N(ind,n,N);     /* Get the correct index into unity for computation */
        for ( k=0; k<N; ++k )
        {
            idx = get_unity_index(k,n,N);           /* Get the kth index into unity */
            complex_multiply(t,x[k],unity[idx]);    /* Compute the kth summand */
            complex_add(X[n],X[n],t);               /* Add the kth summand to the nth Fourier coefficient */
        }
    }

END:
    SET_FREE(ind);      /* Release memory */
    SET_FREE(unity);    /* Release memory */
    return ret;
}

void complex_add ( fourier_t s, fourier_t a, fourier_t b )
{
    fourier_t ss;

    ss->x = a->x + b->x;
    ss->y = a->y + b->y;
    copy_fourier(s,ss);

    return;
}

void complex_multiply ( fourier_t m, fourier_t a, fourier_t b )
{
    fourier_t mm;

    /* 
     * Basic complex multiply 
     *   (ax+iay)(bx+iby) = (axbx-ayby) + i(axby+aybx)
     */
    mm->x = a->x*b->x - a->y*b->y;
    mm->y = a->x*b->y + a->y*b->x;
    copy_fourier(m,mm);

    return;
}

void copy_fourier ( fourier_t a, fourier_t b )
{
    a->x = b->x;
    a->y = b->y;

    return;
}

int32_t get_unity_index ( int32_t k, int32_t n, int32_t N )
{
    int32_t idx = (k*n) % N;

    while ( idx<0 ) /* Just in case modulo comes back negative */
    {
        idx += N;
    }

    return idx;
}

void set_fourier ( fourier_t f, fr_t re, fr_t co )
{
    f->x = re;
    f->y = co;

    return;
}

c_error_t set_fourier_index_n_N ( int32_t * index, int32_t n, int32_t N )
{
    int32_t ret = c_success;
    int32_t k;

    if ( NULL==index )
    {
        goto END;
    }

    index[0] = 0;
    for ( k=1; k<N; ++k )
    {
        index[k] = get_unity_index(k,n,N); /* index[k] = w**(nk) */
    }

END:
    return ret;
}

void unity_n ( fourier_t f, int32_t n )
{
    fr_t re, co;

    /* Use de Moivre's equations */
    re = cos ( -2.0 * 3.14159 / (double)n );
    co = sin ( -2.0 * 3.14159 / (double)n );

    set_fourier(f,re,co);

    return;
}

c_error_t unity_n_array ( fourier_t * f, int32_t n )
{
    c_error_t ret = c_success;
    fourier_t w;
    int32_t k;

    if ( NULL==f || n<1 )
    {
        goto END;
    }
    
    set_fourier(f[0],1.0,0.0); /* The first unity is 1 */
    unity_n(w,n);               /* Computes 1**(1/n) */
    for ( k=1; k<n; ++k )
    {
        /* Basic complex multiplication */
        complex_multiply(f[k],f[k-1],w); /* f[k] = w**k */
    }

END:
    return ret;
}

void zero_fourier ( fourier_t f )
{
    set_fourier(f,0.0,0.0); /* Zero out a complex number */
}









