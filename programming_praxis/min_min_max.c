#include <stdio.h>
#include <stdlib.h>

struct _mmm
{
    int min;
    int min_min;
    int max;
};

typedef struct _mmm    MMM;
typedef struct _mmm * pMMM;

/*
 */
int cmp ( const void * a, const void * b );

/*
 * m[in,out] - array to be filled in
 * a[in] - array of integers
 * n[in] - length of array
 */
int find_mmm ( pMMM m, int * a, int n );

/*
 */
void dbg_p_array ( int * a, int n );

/* ********************************************************** */
int main ( int argc, char * argv[] )
{
    int a[5] = { -1, 4, 5, -23, 24 };

    dbg_p_array(a,5);
    printf("\n");
    qsort(a,5,sizeof(a[0]),cmp);
    dbg_p_array(a,5);
    printf("\n");

    return 0;
}
/* ********************************************************** */

int cmp ( const void * a, const void * b )
{
    return ( *(int*)a - *(int*)b );
}

int find_mmm ( pMMM m, int * a, int n )
{
    int ret = 0;
    int k,mn,mm,mx;

    mn = a[0];
    mm = a[0];
    mx = a[0];

    for ( k=1; k<n; ++k )
    {
        if ( mn<a[k] )
        {
            mn = a[k];
        }
        if ( mx>a[k] )
        {
            mx = a[k];
        }
    }

END:
    return ret;
}

void dbg_p_array ( int * a, int n )
{
    int k;

    if ( NULL==a )
    {
        goto END;
    }
    for ( k=0; k<n; ++k )
    {
        printf("%d ",a[k]);
    }
END:
    return;
}


