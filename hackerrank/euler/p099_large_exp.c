#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lineprint printf("[%d] Here\n",__LINE__);

typedef struct base_exp {
    long base;
    long exp;
    double key;
} be;
/* ------------------------------------------------------------ */
/*                         PROTOTYPES                           */

void be_print( be * b, int n ) {
    int k;

    for ( k=0; k<n; ++k ) {
        printf("[%d] %ld %ld: %lf\n",k,b[k].base,b[k].exp,b[k].key);
    }
}

be * get_input ( int n ) {
    be * b = calloc(n,sizeof(*b));
    int k;
    long base, exp;

    for ( k=0; k<n; ++k ) {
        scanf("%ld %ld",&base,&exp);
        b[k].base = base;
        b[k].exp = exp;
    }
    printf("[%d] b = %p\n",__LINE__,b);
    return b;
}

double key ( be b ) {
    double e = (double)b.exp;
    double d = (double)b.base;
    double k = e * log(d);

    return k;
}

int be_cmp ( const void * a, const void * b ) { 
    be * aa = (be*)a;
    be * bb = (be*)b;

    if ( aa->key > bb->key ) {
        return 1;
    } else if ( aa->key < bb->key ) {
        return -1;
    }
    return 0;
}

void print_max ( be * b, int n, int K ) {
    int k;

    for ( k=0; k<n; ++k ) {
        b[k].key = key(b[k]);
    }

    qsort(b,n,sizeof(b[0]),be_cmp);

    printf("%ld %ld\n",b[K-1].base,b[K-1].exp);
}

/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */
/*                            MAIN                              */
int main() {
    be b[3] = { {4L, 7L}, {3L, 7L}, {2L, 11L} };
    print_max(b,3,2);

    return 0;
}

int main_orig() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    int n,K;
    be * b = NULL;

    scanf("%d",&n);
    b = get_input(n);
    scanf("%d",&K);
    print_max(b,n,K);

    return 0;
}
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */
/*                         DEFINITIONS                          */

/* ------------------------------------------------------------ */
