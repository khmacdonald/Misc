#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "brand.h"
#include "print_macros.h"


int32_t test01 ( int32_t ac, char * av[] );
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
    uint32_t x = 0-1;
    uint32_t y = x-1;
    int32_t k;
    float a;

    for ( k=0; k<10; k++ )
    {
        a = (float)y/x;
        printf("a = %16.15f (%08x/%08x)\n",a,y,x);
        y -= 100;
    }

    return 0;
}

int32_t test03 ( int32_t ac, char * av[] )
{
    brand_t ctx;
    uint8_t  * a = NULL;
    int32_t alen=8;

    if ( 2==ac )
    {
        alen = strtol(av[1],NULL,10);
    }
    info_print("alen = %d",alen);
    a = calloc(1,alen);

    brand_seed_init(ctx);
    brand_byte_array(a,alen,ctx);
    print_array(a,alen);
    printf("\n");

    free(a);
    return 0;
}

int32_t test02 ( int32_t ac, char * av[] )
{
    brand_t ctx;
    int32_t k;
    uint32_t r;

    brand_seed_init(ctx);
    for ( k=0; k<10; ++k )
    {
        r = brand_next(ctx); 
        printf("[%d] %08x\n",k,r);
    }

    return 0;
}

int32_t test01 ( int32_t ac, char * av[] )
{
    brand_t ctx;
    int32_t k;
    uint32_t r,s;

    if ( 2==ac )
    {
        s = strtol(av[1],NULL,10);
    }

    brand_init(ctx,s);
    for ( k=0; k<10; ++k )
    {
        r = brand_next(ctx); 
        printf("[%d] %08x\n",k,r);
    }

    return 0;
}

