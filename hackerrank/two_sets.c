/*
https://www.hackerrank.com/challenges/between-two-sets/problem
 */

#include <stdio.h>

typedef void (*test_t)(void);

#define NTEST 1
int getTotalX(int a_count, int* a, int b_count, int* b) ;

void test01 ( ) ;

/* ---------------------------------------- */

int main ( ) {
    int k;
    test_t tests[NTEST] = { test01 };

    printf("\n\n");
    for ( k=0; k<NTEST; ++k ) {
        tests[k]();
        if ( k<NTEST-1 ) {
            printf("--------------------------------\n");
        }
    }

    printf("\n\n");

    return 0;
}

/* ---------------------------------------- */
void test01 ( ) {
    int n = 2, m = 3;
    int a[2] = { 2, 4 };
    int b[3] = { 16, 32, 96 };

    getTotalX(n,a,m,b);
}

void print_arr ( char * label, int sz, int * arr ) {
    int k;

    printf("%s = { %d",label,arr[0]);
    for ( k=1; k<sz; ++k ) {
        printf(", %d",arr[k]);
    }
    printf(" }\n");
    return;
}

int gcd ( int a, int b ) {
    if ( 0==a ) {
        return b;
    }
    return gcd(b%a,a);
}
int lcm ( int a, int b ) {
    return a * b / gcd(a,b);
}

int array_lcm ( int sz, int * arr ) {
    int l = 0,k;

    if ( 1==sz ) {
        return arr[0];
    }
    l = lcm(arr[0],arr[1]);
    for ( k=2; k<sz; ++k ) {
        l = lcm(l,arr[k]);
    }

    return l;
}

int max_int ( int sz, int * a ) {
    int k,max = a[0];

    for ( k=1; k<sz; ++k ) {
        if ( max < a[k] ) {
            max = a[k];
        }
    }
    return max;
}

int min_int ( int sz, int * a ) {
    int k,min = a[0];

    for ( k=1; k<sz; ++k ) {
        if ( min > a[k] ) {
            min = a[k];
        }
    }
    return min;
}

int array_gcd ( int sz, int * a ) {
    int g = 0,k;

    if ( 1==sz ) {
        return a[0];
    }
    g = gcd(a[0],a[1]);
    for ( k=0; k<sz; ++k ) {
        g = gcd(g,a[k]);
    }
    return g;
}

int getTotalX(int a_count, int* a, int b_count, int* b) {
    int count=0;
    int L, G, max, min, start, k;

    printf("\n");
    printf("a_count = %d, b_count = %d\n",a_count,b_count);
    print_arr("a",a_count,a);
    print_arr("b",b_count,b);

    L = array_lcm(a_count,a);
    G = array_gcd(b_count,b);
    max = max_int(a_count,a);
    min = min_int(b_count,b);
    printf("Least common mulitples of a = %d\n",L);
    //start = (L==max) ? L+L : L;
    start = L;
    printf("start = %d\n",start);

    while ( start <= G ) {
        if ( 0==(G%start) ) {
            printf("    %d\n",start);
            count++;
        }
        start += L;
    }

    printf("count = %d\n",count);

    printf("\n");

    return count;
}
