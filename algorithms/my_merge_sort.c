/*
gcc ./my_merge_sort.c -o ./my_merge_sort ./math/brand.o -I ./math
 */

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "math/brand.h"

#define N_MAX 100

void printby3 ( int n )
{
    int n1=1000,n2=n1*n1,n3=n2*n1,n4=n3*n1;
    if ( 0==n ) {
        printf("0");
        return;
    }
    if ( n<1 ) {
        n = -1*n;
        printf("-");
    }
    if (n<n1) {
        printf("%d",n);
    } else if ( n < n2) {
        printf("%d %03d",n/n1,n%n1);
    } else if ( n < n3 ) {
        printf("%d %03d %03d",n/n2,(n/n1)%n1,n%n1);
    } else {
        printf("%d %03d %03d %03d",n/n3,(n/n2)%n1,(n/n1)%n1,n%n1);
    }
}

void get_random_array ( int * arr, int n )
{
    brand_t ctx;

    brand_seed_init(ctx);
    brand_array((uint32_t*)arr,n,ctx);

    return;
}

int get_array_size ( int argc, char ** argv )
{
    int n = 10;

    if ( 1<argc )
    {
        n = atoi(argv[1]);
    }
    printf("n = %d\n",n);
    if ( n > N_MAX )
    {
        printf("Error: %d must be less than %d\nExiting....\n",n,N_MAX);
        exit(0);
    }

    return n;
}

void print_array_int ( int * arr, int n )
{
    int k;

    if ( n<1 )
    {
        return;
    }

    //printf("(%d",arr[0]);
    printf("(");
    printby3(arr[0]);
    for ( k=1; k<n; k++ )
    {
        //printf(", %d",arr[k]);
        printf(", ");
        printby3(arr[k]);
    }
    printf(")\n");
}

/* ------------------------------------------------------------ */

void my_merge ( int * a, int na, int * b, int nb )
{
    int n = na+nb,aidx=0,bidx=0,xidx=0;;
    int * x = calloc(n,sizeof(*x));

    printf("a - ");
    print_array_int(a,na);
    printf("b - ");
    print_array_int(b,nb);

    for ( ; aidx<na && bidx<nb; ) {
        if (a[aidx]<b[aidx]) {
            x[xidx] = a[aidx++];
        } else {
            x[xidx] = b[bidx++];
        }
        xidx++;
    }
    printf("   x - ");
    print_array_int(x,xidx);
    if ( aidx<na )
    {
        printf("  ---> a\n");
        //memcpy(x+xidx,a+aidx,(n-aidx));
        for ( ; xidx<n; xidx++ ) {
            x[xidx] = a[aidx++];
        }
    }
    else if ( bidx<nb )
    {
        printf("  ---> b\n");
        memcpy(x+xidx,b+bidx,(n-bidx));
    }
    memcpy(a,x,n);
    printf("x - ");
    print_array_int(x,n);
    printf("\n");

    free(x);
}

void my_merge_sort ( int * arr, int n )
{
    int tmp, half = n/2;
    static int level = 0;

    level++;

    if ( 1==n )
    {
        goto END;
    }
    else if ( 2==n )
    {
        if ( arr[0]>arr[1])
        {
            tmp = arr[0];
            arr[0] = arr[1];
            arr[1] = tmp;
        }
        goto END;
    }

    my_merge_sort(arr     ,half);
    my_merge_sort(arr+half,n-half);
    my_merge(arr,half,arr+half,n-half);

END:
    level--;
}

/* ------------------------------------------------------------ */

int test ( int argc, char ** argv )
{
#if 0
    int n = get_array_size(argc,argv);;
    int * arr = calloc(n,sizeof(*arr));
    get_random_array(arr,n);
#else
    int n = 10;
    int arr[10] = { 22618140,   -909592085, 1162036952, 443137326, 
                    1304359808, -148493500, 832324335, 
                    -490408695,  661469413, 1770620669 };
#endif

    setlocale(LC_NUMERIC, "");
    print_array_int(arr,n);
    printf("\n\n    Recursion:\n");
    my_merge_sort(arr,n);
    print_array_int(arr,n);
    printf("\n\n");

#if 0
    if ( arr )
    {
        free(arr);
    }
#endif

    return 0;
}

void test_printby3 ( int n )
{
    printf("n  = 0x%08x == %d == ",(uint32_t)n,n);
    printby3(n);
    printf("\n");
}

int main ( int argc, char ** argv )
{
    int x = 0;
#if 0
    test_printby3(-58);
    test_printby3(58);
    test_printby3(588);
    test_printby3(1<<16);
    test_printby3(1<<24);
    test_printby3(1<<30);
#endif
    x = -45346;
    test_printby3(x);
    x = (1<<31)+1;
    test_printby3(x);
    x = (1<<31);
    test_printby3(x);

    return 0;
}
