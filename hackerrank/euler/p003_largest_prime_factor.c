#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ISPRIME (1<<20)         /* >10**6 */
int is_prime[ISPRIME] = {0};    /* If is_prime[k] is 1, then k is prime */

/* ---------------------------------------------------------------- */
/*                           PROTOTYPES                             */

long get_next_prime ( long n );         /* Gets the next prime larger than n */
void largest_prime_factor ( long n );   /* Gets the largest prime factor of n */
void set_is_prime();                    /* Set up is_prime array */

/* ---------------------------------------------------------------- */

/* ---------------------------------------------------------------- */
/*                              MAIN                                */
int main ( ) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    int t;
    set_is_prime();
    scanf("%d",&t);
    for ( int a0 = 0; a0<t; a0++ ) {
        long n;
        scanf("%ld",&n);
        largest_prime_factor(n);
    }
    return 0;
}

/* ---------------------------------------------------------------- */

void set_is_prime() {
    int k,cprime;

    is_prime[0] = 0; /* 0 and 1 are not prime */
    is_prime[1] = 0;
    for ( k=2; k<ISPRIME; ++k ) {
        is_prime[k] = 1; /* All primes are 2 or greater */
    }
    cprime = 2; /* Start with 2 */
    while ( 1 ) {
        k = cprime+cprime;
        for ( ; k<ISPRIME; k+=cprime ) {
            is_prime[k] = 0; /* zero out all multiples of the current prime */
        }
        while ( cprime<ISPRIME ) {
            cprime++;
            if ( is_prime[cprime] ) { /* Get the next prime in the array */
                break;
            }
        }
        if ( cprime>=ISPRIME ) {
            break;
        }
    }
    return;
}

/* ---------------------------------------------------------------- */
/*                           DEFINITIONS                            */

long get_next_prime ( long n ) {
    n++;
    while ( n<ISPRIME ) {
        /* If n is composite is_prime[n] equals 0.  If prime equals 1. */ 
        if ( is_prime[n] ) { 
            return n; /* n is a prime */
        }
        n++; /* n is not a prime, so try the next candidate */
    }
    return -1; /* No prime found less than (2**20) */
}

void largest_prime_factor ( long n ) {
    long pc = 2; /* prime candidate */
    long np, mxp=1; /* next prime and max prime */

    while ( 1 ) {
        if ( 0==(n%pc) ) {      /* pc divides n */
            if ( mxp<pc ) {
                mxp = pc;       /* pc is now a candidate for the largest prime factor */
            }
            do {
                n = n/pc;
            } while ( 0==(n%pc));   /* In case n = (pc**k)*b */
        }
        np = get_next_prime(pc);    /* Try the next prime */
        /*
         * Since we have the constraint that the original n is less than or equal to 10**12,
         * we know that if n is composite, it will have a prime factor less than 10**6.  If
         * there are not more primes less than 10**6, np is -1.  
         * 
         * The current n has had smaller prime factors divided out, so if np*np>n, we have 
         * divided out all primes, so the resultant n is either 1 or the largest prime.
         */
        if ( (-1==np) || ((np*np)>n) ) {    
            if ( n>mxp ) {
                mxp = n;
            }
            printf("%ld\n",mxp); /* Print the largest prime factor */
            return;
        }
        pc = np;
    }
END:
    return;
}

/* ---------------------------------------------------------------- */
