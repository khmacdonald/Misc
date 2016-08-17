#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bit_twiddle.h"
#include "print_statements.h"

int32_t test02 ( int32_t ac, char * av[] );
int32_t test03 ( int32_t ac, char * av[] );
int32_t test04 ( int32_t ac, char * av[] );

int32_t main ( int32_t argc, char * argv[] )
{
    test04(argc,argv);
    return 0;
}

int32_t test04 ( int32_t ac, char * av[] )
{
    uint64_t y = 0x10L;
    int32_t k,cnt;

    print_hex(y);
    printf(" has \n");
    for ( k=0; k<=64; ++k )
    {
        cnt = leading_zeros_n(y,k);
        printf("%d leading bits in the first %d bits\n",cnt,k); 
    }

    return 0;
}

int32_t test03 ( int32_t ac, char * av[] )
{
    uint64_t x=2346, n = 6, cnt;

    if ( 2<=ac )
    {
        x = strtoll(av[1],NULL,10);
    }
    if ( 3<=ac )
    {
        n = strtoll(av[2],NULL,10);
    }
    cnt = bit_count(x,n);
    printf("The first %llu bits of %10llu -> ",n,x);
    print_bits(x,n);
    printf("\n    contains %llu ones.\n",cnt);

    return 0;
}

int32_t test02 ( int32_t ac, char * av[] )
{
    int32_t k,rk,n=7,lim;

    if ( 2==ac )
    {
        n = strtol(av[1],NULL,10);
        if ( n>16 )
        {
            err_print("n = %d is too large.  n is set to 7\n",n);
            n = 7;
        }
    }

    lim = (1<<n);
    for ( k=0; k<lim; ++k ) 
    {
        rk = bit_reverse(k,n);
        printf("[%5d] ",k);
        print_bits(k,n);
        printf(" -> ");
        print_bits(rk,n);
        printf("\n");
    }

END:
    return 0;
}

int32_t test01 ( int32_t argc, char * argv[] )
{
    uint64_t x = 23,y;
    int32_t n=5;

    if ( 2<=argc )
    {
        dbg_print("Here");
        n = strtol(argv[1],NULL,10);
    }
    if ( 3==argc )
    {
        dbg_print("Here");
        x = strtoll(argv[2],NULL,10);
    }

    y = bit_reverse(x,n);
    printf("n = %d\n",n);
    printf("x = %llu -> ",x);
    print_bits(x,n);
    printf("\n");
    printf("y = %llu -> ",y);
    print_bits(y,n);
    printf("\n");

    return 0;
}
