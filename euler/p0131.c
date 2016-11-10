#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "primes.h"
#include "print_statements.h"

uint64_t g_tcnt = 0;
uint64_t g_cnt = 0;

void proj ( void );
int32_t cat_prime_list ( pr_t * p );
pr_t cat_prime ( pr_t p1, pr_t p2 );
int32_t chk_2_prime ( pr_t p1, pr_t p2, int32_t k, int32_t m );

void test ( int32_t argc, char * argv[] );

/* ---------------------------------------------------------------- */

int32_t main ( int32_t argc, char * argv[] )
{
    proj();
    //test(argc,argv);

    return 0;
}

/* ---------------------------------------------------------------- */
void test ( int32_t argc, char * argv[] )
{
    return;
}
/* ---------------------------------------------------------------- */

int32_t chk_2_prime ( pr_t p1, pr_t p2, int32_t k, int32_t m )
{
    int32_t ret = 1;
    pr_t q1, q2;

    g_tcnt++;
    q1 = cat_prime(p1,p2);
    q2 = cat_prime(p2,p1);
    if ( is_prime(q1) && is_prime(q2) )
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    printf("[%d] g_tcnt = %10llu, g_cnt = %10llu, k = %6d, m = %6d\r",__LINE__,g_tcnt,g_cnt,k,m);

END:
    return ret;
}

pr_t cat_prime ( pr_t p1, pr_t p2 )
{
    char pstr[128];
    int32_t len,k;
    pr_t p = 0;

    memset(pstr,0,127);
    snprintf(pstr,127,"%llu%llu",p1,p2);
    len = strlen(pstr);

    for ( k=0; k<len; ++k )
    {
        p = p*10 + (pstr[k]-'0');
    }

    //info_print("p1 = %llu, p2 = %llu, p = %llu",p1,p2,p);

    return p;
}

void proj ( void )
{
    FILE * fd = fopen("p0060_output.txt","w");
    int32_t start;
    int32_t a,b,c,d,e;
    pr_t ma=0,mb=0,mc=0,md=0,me=0;
    int32_t amx=0, bmx=0, cmx=0, dmx=0, emx=0;
    pr_t p[5];
    pr_t sum,min_sum=100000000;
    clock_t t1, t2;
    double td;

    emx = 2500;
    dmx = emx-1;
    cmx = dmx-1;
    bmx = cmx-1;
    amx = bmx-1;
    start = 0;
    t1 = clock();
    for ( a=start; a<amx; ++a )
    {
        for ( b=a+1; b<bmx; ++b )
        {
            if ( (0==chk_2_prime(small_primes[a],small_primes[b],a,b)) ) 
            {
                continue;
            }
            for ( c=b+1; c<cmx; ++c )
            {
                if ( 0==chk_2_prime(small_primes[b],small_primes[c],b,c) ||
                     0==chk_2_prime(small_primes[a],small_primes[c],b,c) )
                {
                    continue;
                }
                for ( d=c+1; d<dmx; ++d )
                {
                    if ( 0==chk_2_prime(small_primes[c],small_primes[d],c,d) || 
                         0==chk_2_prime(small_primes[b],small_primes[d],c,d) ||
                         0==chk_2_prime(small_primes[a],small_primes[d],c,d) )
                    {
                        continue;
                    }
                    for ( e=d+1; e<emx; ++e )
                    {
                        if ( chk_2_prime(small_primes[d],small_primes[e],d,e) &&
                             chk_2_prime(small_primes[c],small_primes[e],d,e) &&
                             chk_2_prime(small_primes[b],small_primes[e],d,e) &&
                             chk_2_prime(small_primes[a],small_primes[e],d,e) )
                        {
                            g_cnt++;
                            sum = small_primes[a] + small_primes[b] + small_primes[c] + 
                                  small_primes[d] + small_primes[e]; 
                            fprintf(fd,"%10llu, %10llu, %10llu, %10llu, %10llu, sum = %llu\n",
                                        small_primes[a],small_primes[b],small_primes[c], 
                                        small_primes[d],small_primes[e],sum); 
                            printf("\n%10llu, %10llu, %10llu, %10llu, %10llu, sum = %llu\n",
                                        small_primes[a],small_primes[b],small_primes[c], 
                                        small_primes[d],small_primes[e],sum); 
                                        
                            if ( sum<min_sum )
                            {
                                min_sum = sum;
                                ma = small_primes[a];
                                mb = small_primes[b];
                                mc = small_primes[c];
                                md = small_primes[d];
                                me = small_primes[e];
                            }
                        }
                    } /* e */
                } /* d */
            } /* c */
        } /* b */
    } /* a */
    t2 = clock();
    td = ((double)(t2-t1)/(double)CLOCKS_PER_SEC);
    printf("\n");
    printf("[%d] %llu, %llu, %llu, %llu, %llu\n",__LINE__,ma,mb,mc,md,me);
    printf("[%d] Min Sum           = %llu\n",__LINE__,min_sum);
    printf("[%d] Total checks      = %llu\n",__LINE__,g_tcnt);
    printf("[%d] Total time        = %.3f\n",__LINE__,td);
    printf("[%d] Check per seconds = %.3f\n",__LINE__,(double)g_tcnt/td);

    fclose(fd);
    fd = NULL;

    return;
}

















