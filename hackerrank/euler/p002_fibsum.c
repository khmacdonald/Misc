#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/* ---------------------------------------------------------------- */
/*                           PROTOTYPES                             */

/* ---------------------------------------------------------------- */
void even_fib( int ac, char ** av );

/* ---------------------------------------------------------------- */
/*                              MAIN                                */
int main ( int argc, char ** argv ) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    even_fib(argc,argv);

    return 0;
}
/* ---------------------------------------------------------------- */


/* ---------------------------------------------------------------- */
/*                           DEFINITIONS                            */

void even_fib( int ac, char ** av ) {
    long long n = 100;
    long long even_fib = 0;
    long long a0 = 0, a1 = 1, sum=0;
    long long tsum = 0;

    if ( 1<ac ) {
        n = atoll(av[1]);
    }

    do { 
        if ( 0==(sum&1) ) {
            tsum += sum;
        }
        sum = a0 + a1;
        a0 = a1;
        a1 = sum;
    } while ( sum<n );
    printf("%lld\n",tsum);

    return;
}

/* ---------------------------------------------------------------- */
