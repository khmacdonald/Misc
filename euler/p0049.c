#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "primes.h"
#include "print_statements.h"

int32_t check ( pr_t x );
void proj ( void );

void test ( int32_t argc, char * argv[] );

/* ---------------------------------------------------------------- */

int32_t main ( int32_t argc, char * argv[] )
{
    //proj();
    test(argc,argv);

    return 0;
}

/* ---------------------------------------------------------------- */
void test ( int32_t argc, char * argv[] )
{
    pr_t pr = 271;
    info_print("prime_array[%llu] = %d",pr,prime_array[pr]);
    if ( is_prime(pr) )
    {
        info_print("%llu is prime",pr);
    }
    else
    {
        info_print("%llu is not prime",pr);
    }
    return;
}
/* ---------------------------------------------------------------- */

void get_dig ( pr_t * d, pr_t pr )
{
    d[0] = pr % 10;
    pr   = pr / 10;
    d[1] = pr % 10;
    pr   = pr / 10;
    d[2] = pr % 10;
    pr   = pr / 10;
    d[3] = pr % 10;
    pr   = pr / 10;
}

pr_t perm_dig ( pr_t * p, int32_t a, int32_t b, int32_t c, int32_t d )
{
    pr_t ptest = p[d] * 1000 + p[c] * 100 + p[b] * 10 + p[a];
    return ptest;
}

#define CHK(X) if ( is_prime(X) ) \
    { \
        if ( 0==cnt ) \
        { \
            fprintf(fd,"%llu -> ",pr);\
        } \
        if ( cnt<3 ) \
        { \
            plist[cnt] = X; \
        } \
        cnt++; \
        fprintf(fd," %llu ",X);\
    }


int32_t check_perms ( pr_t * plist, pr_t pr, FILE * fd )
{
    int32_t ret=0,cnt=0;
    pr_t d[4],ptest;

    get_dig(d,pr);

    ptest = perm_dig(d,3,2,1,0);
    CHK(ptest);
    ptest = perm_dig(d,3,2,0,1);
    CHK(ptest);
    ptest = perm_dig(d,3,1,2,0);
    CHK(ptest);
    ptest = perm_dig(d,3,1,0,2);
    CHK(ptest);
    ptest = perm_dig(d,3,0,2,1);
    CHK(ptest);
    ptest = perm_dig(d,3,0,1,2);
    CHK(ptest);

    ptest = perm_dig(d,2,3,1,0);
    CHK(ptest);
    ptest = perm_dig(d,2,3,0,1);
    CHK(ptest);
    ptest = perm_dig(d,2,1,3,0);
    CHK(ptest);
    ptest = perm_dig(d,2,1,0,3);
    CHK(ptest);
    ptest = perm_dig(d,2,0,3,1);
    CHK(ptest);
    ptest = perm_dig(d,2,0,1,3);
    CHK(ptest);

    ptest = perm_dig(d,1,3,2,0);
    CHK(ptest);
    ptest = perm_dig(d,1,3,0,2);
    CHK(ptest);
    ptest = perm_dig(d,1,2,3,0);
    CHK(ptest);
    ptest = perm_dig(d,1,2,0,3);
    CHK(ptest);
    ptest = perm_dig(d,1,0,3,2);
    CHK(ptest);
    ptest = perm_dig(d,1,0,2,3);
    CHK(ptest);

    ptest = perm_dig(d,0,3,2,1);
    CHK(ptest);
    ptest = perm_dig(d,0,3,1,2);
    CHK(ptest);
    ptest = perm_dig(d,0,2,3,1);
    CHK(ptest);
    ptest = perm_dig(d,0,2,1,3);
    CHK(ptest);
    ptest = perm_dig(d,0,1,3,2);
    CHK(ptest);
    ptest = perm_dig(d,0,1,2,3);
    CHK(ptest);

    if ( cnt>0 )
    {
        fprintf(fd,"\n");
    }
    if ( cnt==3 )
    {
        ret = 1;
    }

    return ret;
}

void proj ( void )
{
    pr_t lo=999, hi=10000,pr;
    int32_t cnt = 0,k,pcnt=0;
    char fname[] = "p0049_out.txt";
    FILE * fd = fopen(fname,"w");
    pr_t plist[3];

    if ( NULL==fd )
    {
        err_print("Could not open %s",fname);
        goto END;
    }

    for ( k=0; k<SMALL_PRIME_SZ && small_primes[k]<hi; ++k )
    {
        pr = small_primes[k];
        if ( pr>lo )
        {
            cnt++;
            if ( check_perms(plist,pr,fd) )
            {
                pcnt++;
                info_print("%llu -> %llu %llu %llu",
                           pr,plist[0],plist[1],plist[2]);
            }
        }
    }

    info_print("cnt = %d",cnt);
    info_print("pcnt = %d",pcnt);
    fclose(fd);
    fd = NULL;

END:
    return;
}

















