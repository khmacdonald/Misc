#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------- */

#define MAXDIG (1<<14)

struct val_idx { 
    long val;
    long idx;
    long sum;
};

/* ------------------------------------------- */

void big_init ( long * dig, int sz );
void big_mul ( long * dig, int sz, long x );
void big_print ( long * dig, int sz );

int cmp_val ( const void * aa, const void * bb );
int cmp_idx ( const void * aa, const void * bb );

void solve ( struct val_idx * vi, int n );

/* ------------------------------------------- */
void dbg_main ( ) ;
void main_test_dbg ( );
void main_solve( );
/* ------------------------------------------- */

int main ( ) {
    main_test_dbg ( );
    return 0;
}

/* ------------------------------------------- */

void main_test_dbg ( ) {
    struct val_idx vi[3] = {
        { 3L, 0L, 0L },
        { 6L, 1L, 0L },
        { 5L, 2L, 0L },
    };
    solve(vi,3);

    return;
}

void dbg_main ( )  {
    long dig[MAXDIG];

    big_init(dig,MAXDIG);
    big_print(dig,MAXDIG);
    printf("\n");

    big_mul(dig,MAXDIG,2);
    big_print(dig,MAXDIG);
    printf("\n");

    big_mul(dig,MAXDIG,3);
    big_print(dig,MAXDIG);
    printf("\n");

    big_mul(dig,MAXDIG,4);
    big_print(dig,MAXDIG);
    printf("\n");

    big_mul(dig,MAXDIG,4);
    big_print(dig,MAXDIG);
    printf("\n");


    return;
}

/* ------------------------------------------- */

void big_init ( long * dig, int sz ) {
     int k;

     dig[0] = 1L;
     for ( k=1; k<sz; ++k ) {
         dig[k] = 0L;
     }
     return;
}

void big_mul ( long * dig, int sz, long x ) {
    int ret = 0;
    long carry = 0,
        tmp,k;

    for ( k=0; k<sz; ++k ) {
        tmp = carry + dig[k] * x;
        dig[k] = tmp % 10;
        carry = tmp / 10;
    }

    return;
}

void big_print ( long * dig, int sz ) {
    int k=sz-1;

    while ( 0==dig[k] && k>=0 ) {
        k--;
    }
    if ( 0>k ) {
        printf("0");
        return;
    }
    for ( ; k>=0; k-- ) {
        printf("%d",(int)dig[k]);
    }
    return;
}


int cmp_val ( const void * aa, const void * bb ) {
    struct val_idx * a = (struct val_idx *)aa;
    struct val_idx * b = (struct val_idx *)bb;

    if ( a->val > b->val ) {
        return 1;
    } else if ( a->val < b->val ) {
        return -1;
    }
    return 0;
}

int cmp_idx ( const void * aa, const void * bb ) {
    struct val_idx * a = (struct val_idx *)aa;
    struct val_idx * b = (struct val_idx *)bb;

    if ( a->idx > b->idx ) {
        return 1;
    } else if ( a->idx < b->idx ) {
        return -1;
    }
    return 0;
}

long sum_dig ( long * dig, int n ) {
    int k;
    long sum = 0;

    for ( k=0; k<n; ++k ) {
        sum += dig[k];
    }

    return sum;
}

void solve ( struct val_idx * vi, int n ) {
    long start=1, end, k, x;
    long dig[MAXDIG];

    /* Sort in value order */
    qsort(vi,n,sizeof(vi[0]),cmp_val);

    /* Initialize dig */
    big_init(dig,MAXDIG);
    for ( k=0; k<n; ++k ) {
        end = vi[k].val;
        for ( x = start; x<=end; ++x ) {
            big_mul(dig,MAXDIG,x);
        }
        start = end+1;
        vi[k].sum = sum_dig(dig,MAXDIG);
    }

    /* Sort in value order */
    qsort(vi,n,sizeof(vi[0]),cmp_idx);

    /* Output */
    for ( k=0; k<n; ++k ) {
        //printf("[%d] val = %ld, sum = %ld\n",__LINE__,vi[k].val,vi[k].sum);
        printf("%ld\n",vi[k].sum);
    }

    return;
}
