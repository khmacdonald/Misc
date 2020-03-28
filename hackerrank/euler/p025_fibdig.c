#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MXDIG (1<<13)  // 8192
typedef struct _big {
    int d[MXDIG];
    int used;
} big_t[1];

/* -------------------------- */
/*         PROTOTYPES         */

void big_add ( big_t c, big_t a, big_t b );
void big_set ( big_t a, int x );
void big_zero ( big_t a );

void solve ( int * arr, int n );
int max_num ( int * arr, int n );

/* -------------------------- */

/* -------------------------- */
/*           MAIN             */
int main() {
    /* 
     * Enter your code here. Read 
     * input from STDIN. Print output to STDOUT 
     */    
    int n,k,tmp;
    int * arr = NULL;

    /* Get the number of tests */
    scanf("%d",&n); 
    arr = calloc(n,sizeof(*arr));

    /* Get the tests */
    for ( k=0; k<n; ++k ) {
        scanf("%d",&tmp);
        arr[k] = tmp;
    }

    /* Solve problem */
    solve(arr,n);

    return 0;
}
/* -------------------------- */

/* -------------------------- */
/*         DEFINITIONS        */

void solve ( int * arr, int n ) {
    big_t a,b,c;
    big_t *a0=&a, *a1=&b, *a2=&c, *tmp=NULL; /* Use pointers */
    int cused = 2,fidx=2,mx,k;
    int ndig[5001];

    memset(ndig,0,5001*sizeof(ndig[0]));    /* Zero out array */
    mx = max_num(arr,n);                    /* Get max test */

    big_set(a,1);   /* First Fibonacci number */
    big_set(b,1);   /* Second Fibonacci number */

    /* Compute the Fibonacci sequence to the largest test */
    while ( cused<=mx ) {
        /* Keep track of the Fibonacci number */
        fidx++;

        /* Get next Fibonacci number */
        big_add(*a2,*a0,*a1);
        if ( cused==(*a2)->used ) {
            /* Capture the first Fibonacci number 
               with a given number of digits */
            ndig[cused] = fidx;
            cused++;
        }

        /*  Set up pointers to compute the next Fibonacci number */
        tmp = a0;
        a0 = a1;
        a1 = a2;
        a2 = tmp;
    }

    /* Print out the Fibonacci index for each test */
    for ( k=0; k<n; ++k ) {
        printf("%d\n",ndig[arr[k]]);
    }
}

/* Get the max number in an integer array */
int max_num ( int * arr, int n ) {
    int k,mx = arr[0];
    
    for ( k=1; k<n; ++k ) {
        if ( arr[k] > mx ) {
            mx = arr[k];
        }
    }

    return mx;
}

/* 
 * Add two large numberes 
 * c = a + b
 */
void big_add ( big_t c, big_t a, big_t b ) {
    int mxused = (a->used > b->used ) ? a->used : b->used;
    int tmp,k,carry = 0;

    /* Add digit by digit */
    for ( k=0; k<mxused; ++k ) {
        tmp = a->d[k] + b->d[k] + carry;
        c->d[k] = tmp % 10;
        carry = tmp / 10;
    }

    /* If there is a carry, add a digit and set it to carry */
    if ( carry ) {
        c->d[mxused] = carry;
        mxused++;
    }
    c->used = mxused;
}

/* Zeros the big integer and sets the low digit */
void big_set ( big_t a, int x ) {
    big_zero(a);
    a[0].d[0] = x % 10; /* The array is only digits */
    a[0].used = 1;      /* The number of digits in the big integer */
}

/* Sets the big integer to zero */
void big_zero ( big_t a ) {
    int k;

    for ( k=0; k<MXDIG; ++k ) {
        a[0].d[k] = 0;
    }
    a[0].used = 0;
}

/* -------------------------- */
