#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/print_statements.h"

/* ------------------------------------------------------------------ */
/*                           Prototypes                               */
int easy_factorial ( int x );

int find_sigdig ( int * dig, int sz );
int get_dig ( int * dig, int dsz, int x );

void big_init ( int * dig, int sz );
int big_factorial ( int * dig, int sz, int x );
int big_multiply ( int * dig, int sz, int x );
void big_print ( int * dig, int sz );
void big_print_raw ( int * dig, int sz );
void big_print_str ( char * s, int ssz, int * dig, int sz );
/* ------------------------------------------------------------------ */

#define MAX_DIG (1<<16)
/* ------------------------------------------------------------------ */
/*                              Test                                  */
int test_big_print ( int argc, char ** argv );
int test_big_multiply ( int argc, char ** argv );
int test_big_factorial ( int argc, char ** argv );

/* ------------------------------------------------------------------ */
/*                              Main                                  */

int main ( int argc, char ** argv ) {
    //test_big_print(argc,argv);
    //test_big_multiply(argc,argv);
    //test_big_factorial(argc,argv);
    int n = 6,sum=0,k,sigdig;
    int dig[MAX_DIG] = {0};

    dig[0] = 1;

    if ( 1<argc ) {
        n = atoi(argv[1]); 
    }

    big_factorial(dig,MAX_DIG,n);
    printf("big_factorial(%d) = ",n);
    big_print(dig,MAX_DIG);
    printf("\n");

    sigdig = find_sigdig(dig,MAX_DIG);
    for ( k=0; k<sigdig+1; ++k ) {
        sum += dig[k];
    }
    printf("    factorial(%d) has %d digits.\n",n,sigdig);
    printf("    Sum of digits of factorial(%d) = %d.\n",n,sum);

    return 0;
}

/* ------------------------------------------------------------------ */
int test_big_print ( int argc, char ** argv ) {
    int d=101, sz;
    int dig[MAX_DIG];

    if ( 1<argc ) {
        d = atoi(argv[1]);
    }

    sz = get_dig(dig,MAX_DIG,d);
    
    dbg_print("%d has %d digits\n",d,sz);
    dbg_print("big_print = ");
    big_print(dig,MAX_DIG);
    printf("\n");

    return 0;
}

int test_big_multiply ( int argc, char ** argv ) {
    int n=6,d=101, sz;
    int dig[MAX_DIG];

    if ( 1<argc ) {
        n = atoi(argv[1]);
    }
    if ( 2<argc ) {
        d = atoi(argv[2]);
    }
    dbg_print("%d * %d = %d\n",n,d,n*d);

    sz = get_dig(dig,MAX_DIG,d);
    big_multiply(dig,MAX_DIG,n);
    dbg_print("big_mulitply done: ");
    //big_print_raw(dig,10);

    big_print(dig,MAX_DIG);
    printf("\n");

    return 0;
}


int test_big_factorial ( int argc, char ** argv ) {
    int n = 6,f;
    int dig[MAX_DIG] = {0};
    dig[0] = 1;

    if ( 1<argc ) {
        n = atoi(argv[1]); 
    }

    f = easy_factorial(n);
    printf("factorial(%d) = %d\n",n,f);

    big_factorial(dig,MAX_DIG,n);
    printf("big_factorial(%d) = ",n);
    big_print(dig,MAX_DIG);
    printf("\n");

    return 0;
}

/* ------------------------------------------------------------------ */
int easy_factorial ( int x ) {
    int ret = 1;

    if ( x<0 ) {
        printf("Error: Cannot compute factorial(%d).\n",x);
        printf("    Exiting....\n");
        exit(1);
    }

    if ( x<2 ) {
        return 1;
    }
    return x * easy_factorial(x-1);
}

int get_dig ( int * dig, int dsz, int x ) {
    int k, sz=0;
    if ( x<0 ) {
        err_print_exit(1,"%d is not positive.",x);
    }
    memset(dig,0,dsz*sizeof(dig[0]));
    while ( x>0 && sz<dsz ) {
        dig[sz++] = x % 10;
        x /= 10;
    }

    return sz;
}

void big_init ( int * dig, int sz ) {
    memset(dig,8,sz*sizeof(dig[0]));
    dig[0] = 1;
}

int big_factorial ( int * dig, int sz, int x ) {

    if ( x<0 ) {
        err_print_exit(0,"Cannot compute factorial(%d).\n",x);
    }

    if ( x<2 ) {
        memset(dig,0,sz * sizeof(dig[0]));
        dig[0] = 1;
        return 0;
    }

    big_factorial(dig,sz,x-1);
    big_multiply(dig,sz,x);

    return 0;
}

int big_multiply ( int * dig, int sz, int x ) {
    int ret = 0, 
        carry = 0,
        sigdig,tmp,k;

    for ( k=0; k<sz; ++k ) {
        tmp = carry + dig[k] * x;
        dig[k] = tmp % 10;
        carry = tmp / 10;
    }

    return ret;
}

void big_print ( int * dig, int sz ) {
    char * s = calloc(1,sz+1);

    big_print_str(s,sz+1,dig,sz);
    printf("%s",s);

    free(s);
    s = NULL;

    return;
}

void big_print_raw ( int * dig, int sz ) {
    int k=0; 

    dbg_print(" ");
    for ( k=sz; k>=0; --k ) {
        printf("%d ",dig[k]);
    }
    printf("\n");
}

int find_sigdig ( int * dig, int sz ) {
    int k = sz-1;

    while ( k>=0 ) {
        if ( dig[k] ) {
            return k;
        }
        k--;
    }
    return -1;
}

void big_print_str ( char * s, int ssz, int * dig, int sz ) {
    int sigdig,k;

    sigdig = find_sigdig(dig,sz);
    if ( -1==sigdig ) {
        snprintf(s,ssz,"0");
        return;
    }

    for ( k=0; k<sigdig+1; ++k ) {
        s[sigdig-k] = dig[k] + '0';
    }
    return;
}

