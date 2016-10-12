#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int32_t print_corners ( int32_t n );

/* ---------------------------------------------------------------- */


int32_t main ( int32_t argc, char * argv[] )
{
    int32_t n;

    if ( 2!=argc )
    {
        printf("Usage: %s <odd integer>\n",argv[0]);
        goto END;
    }

    n = strtol(argv[1],NULL,10);
    printf("n = %d\n",n);
    if ( !(1&n) )
    {
        printf("ERROR: %d is not odd\n",n);
        goto END;
    }

    print_corners(n);

END:
    return 0;
}


/* ---------------------------------------------------------------- */

int32_t print_corners ( int32_t n )
{
    int32_t c = 1;
    int32_t n2 = n*n;
    int32_t idx = 2;
    int32_t m;
    int32_t sum = c;
    
    printf("1\n");
    while ( c<n2 )
    {
        printf("%5d -> ",idx);
        for ( m=0; m<4; m++ )
        {
            c += idx;
            sum += c;
            printf("%5d ",c);
        }
        printf("\n");
        idx += 2;
    }
    printf("sum = %d\n",sum);

    return 0;
}

















