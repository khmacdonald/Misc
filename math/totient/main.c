#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print_statements.h"
#include "phi.h"

int32_t main_primes ( int32_t argc, char * argv[] );
int32_t main_real ( int32_t argc, char * argv[] );
int32_t main_euler0070 ( int32_t argc, char * argv[] );

int32_t is_perm ( uint32_t a, uint32_t b );

int32_t main ( int32_t argc, char * argv[] )
{
    main_euler0070(argc,argv);
}

int32_t is_perm ( uint32_t a, uint32_t b )
{
    int32_t ret = 1;
    uint32_t ua[10], ub[10];
    uint32_t tmp,k;
    uint32_t aa=a, bb=b;

    memset(ua,0,10*sizeof(ua[0]));
    memset(ub,0,10*sizeof(ub[0]));

    while ( a>0 )
    {
        tmp = a % 10;
        ua[tmp]++;
        a = a/10;
    }

    while ( b>0 )
    {
        tmp = b % 10;
        ub[tmp]++;
        b = b/10;
    }
    for ( tmp = 0; tmp<10; ++tmp )
    {
        if ( ua[tmp]!=ub[tmp] )
        {
            ret = 0;
            goto END;
        }
    }
END:
    return ret;
}

int32_t main_euler0070 ( int32_t argc, char * argv[] )
{
    int32_t k;
    double rmin = 100000000000.0,ratio;
    uint32_t tn, n_min;

    //for ( k=2; k<10000000; ++k )
    for ( k=2; k<1000000; ++k )
    {
        printf("%u\r",k);
        tn = phi(k);
        if ( is_perm(k,tn) )
        {
            ratio = ((double)k)/((double)tn);
            if (ratio<rmin)
            {
                rmin = ratio;
                n_min = k;
            }
        }
    }
    printf("\n");
    info_print("%u -> ratio = %f\n",n_min,rmin);

    return 0;
}

int32_t main_real ( int32_t argc, char * argv[] )
{
    uint32_t n = 1024,sq,tn;

    if ( 2<=argc )
    {
        n = strtol(argv[1],NULL,10);
    }
    tn = phi(n);

    info_print("phi(%u) = %u\n",n,tn);

    return 0;
}

int32_t main_primes ( int32_t argc, char * argv[] )
{
    int32_t k,tot=0,idx=0;
    FILE * ofd = NULL;
    char lb_define[] = "SMALL_PRIME_SZ";

    if ( 2!=argc )
    {
        info_print("Usage: %s <out file>\n",argv[0]);
        goto END;
    }

    ofd = fopen(argv[1],"w");
    if ( NULL==ofd )
    {
        err_print("Could not open %s\n",argv[1]);
        goto END;
    }
    for ( k=0; k<PRIME_SIZE; ++k )
    {
        if ( prime_array[k] )
            tot++;
    }
    fprintf(ofd,"#define %s %d\n",lb_define,tot);
    fprintf(ofd,"uint32_t small_primes[%s] = \n{\n    ",lb_define);
    for ( k=0; k<PRIME_SIZE; ++k )
    {
        if ( prime_array[k] )
        {
            fprintf(ofd,"%10d, ",k);
            if ( 0==((idx+1)%8) )
            {
                fprintf(ofd,"\n    ");
            }
            idx++;
        }
    }
    fprintf(ofd,"\n};");
    fclose(ofd);
    ofd = NULL;
    info_print("idx = %d\n",idx);

END:
    return 0;
}
