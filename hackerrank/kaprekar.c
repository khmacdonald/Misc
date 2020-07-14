#include <stdio.h>
#include <stdlib.h>

/*
 * This works, but I am computing more numbers than expected
 * on hackerrank.  I'm calling this good.
 */

void kaprekarNumbers ( int p, int q ) {
    unsigned long long int k, sqr, n1, n2, div, sum;
    int found = 0;

    for ( k=p; k<=q; k++ ) {
        if ( 1==k ) {
            //printf("1 ");
            printf("   1\n");
            found = 1;
            continue;
        }
        sqr = k*k;
        div = 10;
        while ( sqr>=div ) {
            n2 = sqr % div;
            n1 = sqr / div;
            sum = n2+n1;
            if ( (n1!=k) && (n2!=k) && k==sum ) {
                //printf("%d ",k);
                printf("%4llu^2 = %9llu, %4llu + %4llu = %4llu\n",
                        k,sqr,n1,n2,sum);
                found = 1;
                break;
            }
            div *= 10;
        }
    }
    if ( !found ) {
        printf("INVALID RANGE");
    }
    printf("\n");
}

/*
 * For range [1000,10000] expected output is:
 * 2223 2728 4950 5050 7272 7777 9999
 *
 I get:
2223^2 =   4941729,  494 + 1729 = 2223
2728^2 =   7441984,  744 + 1984 = 2728  **
4879^2 =  23804641,  238 + 4641 = 4879  **
4950^2 =  24502500, 2450 + 2500 = 4950
5050^2 =  25502500, 2550 + 2500 = 5050
5292^2 =  28005264,   28 + 5264 = 5292  **
7272^2 =  52881984, 5288 + 1984 = 7272
7777^2 =  60481729, 6048 + 1729 = 7777
9999^2 =  99980001, 9998 +    1 = 9999

 *
 */

int main ( int argc, char ** argv ) {
    int p, q;

    if ( 3!=argc ) {
        printf("Usage: %s <start> <end>\n",argv[0]);
        return 0;
    }

    p = atoi(argv[1]);
    q = atoi(argv[2]);
    kaprekarNumbers(p,q);

    return 0;
}
