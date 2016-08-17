#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Assumes p is unallocated.
 * Returns the number of primes found between 2 and n inclusive.
 * 
 */
int32_t sieve ( int32_t ** p, int32_t n )
{
    int32_t * primes=NULL;
    int32_t * tmp=(int32_t*)malloc((n+1)*sizeof(int32_t));
    int32_t k,m,idx,cnt=0;

    /* Set all numbers to 1 */
    for ( k=0; k<n+1; k++ )
    {
        tmp[k]=1;
    }

    /* Set non-prime numbers to 0 */
    tmp[0] = 0;
    tmp[1] = 0;
    for ( k=2; k<n+1; ++k )
    {
        if ( 1==tmp[k] ) /* k is prime */
        {
            cnt++;  /* Count the number of primes found */
            m = k+k;
            while(m<n+1)
            {
                tmp[m]=0; /* Set all multiples (composites) of k 0 */
                m += k;
            }
        }
    }
    primes = (int32_t*)malloc(cnt*sizeof(int32_t)); /* Holds all the primes */
    idx=0;
    for ( k=2; k<n+1 && idx<cnt; ++k )
    {
        if ( 1==tmp[k] )
        {
            primes[idx++] = k; /* Fill up p with the prime numbers marked in tmp */
        }
    }
    free(tmp);
    tmp=NULL;

    *p = primes;
    return cnt; /* Return the number of primes found */
}

int main ( int32_t argc, char * argv[] )
{
    int32_t * primes = NULL;
    int32_t num_primes = 0;
    int32_t n=10,k;
    FILE * fd=NULL;

    if ( 3!=argc )
    {
        printf("Usage: %s <number>\n",argv[0]);
        goto end;
    }

    n = strtol(argv[1],NULL,10);
    printf("  *** Sieving ***\n");
    num_primes = sieve(&primes,n);

    printf("There are %d primes less than %d\n",num_primes,n);
    fd = fopen(argv[2],"w");
    if ( NULL==fd )
    {
        fprintf(stderr,"Could not open %s\n",argv[2]);
        goto end;
    }
    for ( k=0; k<num_primes; ++k )
    {
        fprintf(fd,"%6d, ",primes[k]);
        if ( 0==((k+1)%8) )
        {
            fprintf(fd,"\n");
        }
    }
    fprintf(fd,"\n");

end:
    if ( primes )
    {
        free(primes);
        primes=NULL;
    }
    if ( fd )
    {
        fclose(fd);
        fd = NULL;
    }

    return 0;
}












