#include "common.h"

/* ---------------------------------------------------------------- */
/*                         STATIC FUNCTIONS                         */

static int32_t get_x_size ( sz_t sz );
static void     print_x_2_str ( char * str, int32_t slen, uint32_t x, int32_t sz_x );

/* ---------------------------------------------------------------- */

char * c_err_msg ( c_error_t err )
{
    static char * msg[c_end] = {
        "success",
        "failure",
        "bad arguments",
        "no memory",
        "null pointer"
    };
    static char invalid[] = "invalid error";
    char * ret = invalid;

    if ( err<c_end )
    {
        ret = msg[err];
    }
    return ret;
}

c_error_t c_get_random_array( uint8_t * arr, int32_t len )
{
    c_error_t ret = c_success;
    uint32_t rnd;
    int32_t k,q,r;
    uint8_t * p;
    struct timeval _t;
    uint32_t seed;

    if ( NULL==arr )
    {
        /* NULL pointer error */
        ret = c_null;
        goto END;
    }
    if ( len<1 )
    {
        /* len is invalid */
        ret = c_badargs;
        goto END;
    }
    
    gettimeofday(&_t,NULL);
    seed = (uint32_t)_t.tv_sec ^ (uint32_t)_t.tv_usec;
    srand(seed);

    q = len/sizeof(rnd);    /* The number of bytes as a multiple of sizeof(rnd) */
    r = len % sizeof(rnd);  /* The remainder bytes after the largest multiple of sizeof(rnd) */
     
    p = arr;
    for ( k=0; k<q; k++ )
    {
        /* Fill out the largest number of bytes as a multiple of sizeof(rnd) */
        rnd = rand();
        memcpy(p,&rnd,sizeof(rnd));
        p += sizeof(rnd);
    }

    if ( r )
    {
        /* The remaining number of bytes in the array */
        rnd = rand();
        memcpy(p,&rnd,r);
    }
END:
    return ret;
}

void c_print_arr_2_str ( char * str, int32_t slen, uint8_t * arr, int32_t alen )
{
    int32_t k,idx;
    uint8_t nibble;
    char nb[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

    memset(str,0,slen);

    for ( k=0, idx=0; idx<slen-4 && k<alen; k++, idx+=3 )
    {
        str[idx]   = nb[arr[k]&0x0f];
        str[idx+1] = nb[(arr[k]>>4)&0x0f];
        str[idx+2] = ' ';
    }
}

void c_print_int_bin_2_str ( char * str, int32_t slen, uint32_t x, sz_t sz )
{
    int32_t k,sz_x;

    if ( NULL==str )
    {
        printf("ERROR: Bad arguments in %s at %d\n",__FUNCTION__,__LINE__);
        goto END;
    }

    sz_x = get_x_size(sz);   /* Get the number of bites associated with sz */
    memset(str,0,slen);
    print_x_2_str(str,slen,x,sz_x);  /* Print bites to a string */

END:
    return;
}

/* ---------------------------------------------------------------- */
/*                         STATIC FUNCTIONS                         */

static int32_t get_x_size ( sz_t sz )
{
    int32_t ret=0;

    /* Returns the number of bits associated with each size */
    switch (sz)
    {
        case _sz8:
            ret = 8;
            break;
        case _sz16:
            ret = 16;
            break;
        case _sz32:
            ret = 32;
            break;
        case _sz64:
            ret = 64;
            break;
    }
    return ret;
}

static void print_x_2_str ( char * str, int32_t slen, uint32_t x, int32_t sz_x )
{
    int32_t k;

    for ( k=0; k<sz_x && k<slen-1; ++k )
    {
        /* Prints a 'X' for 1 and a '.' for 0 with the most significant
           bit being on the left. */ 
        if ( (x>>(sz_x-1-k)) & 1 )
        {
            str[k] = 'X';
        }
        else
        {
            str[k] = '.';
        }
    }
}












































