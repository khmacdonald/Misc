#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "primes.h"

#define NUM_N 5

void proj ( int32_t argc, char * argv[] );

int32_t comma_count ( char * b, int32_t blen );
char *  read_file ( int32_t * len );
char *  str_2_ascii ( char * b, int32_t blen, int32_t * clen );
void    test_xor ( char * a, int32_t alen );
void    answer_xor ( char * a, int32_t alen );

void test ( int32_t argc, char * argv[] );
void dbg_print( char * b, int32_t n );

/* ---------------------------------------------------------------- */

int32_t main ( int32_t argc, char * argv[] )
{
    proj(argc,argv);
    return 0;
}

/* ---------------------------------------------------------------- */
void test ( int32_t argc, char * argv[] )
{
    int32_t a,b,c;

    a = 65;
    b = 42;
    c = a^b;
    printf("[%d] %d XOR %d = %d\n",__LINE__,a,b,c);

    a = 107;
    b = 42;
    c = a^b;
    printf("[%d] %d XOR %d = %d\n",__LINE__,a,b,c);

    return;
}
/* ---------------------------------------------------------------- */

void proj ( int32_t argc, char * argv[] )
{
    char * b  = NULL;
    int32_t blen = 0;
    char * c = NULL;
    int32_t clen = 0;

    b = read_file(&blen);
    if ( NULL==b )
    {
        goto END;
    }
    c = str_2_ascii(b,blen,&clen);
    if ( NULL==c )
    {
        goto END;
    }
    //test_xor(c,clen);
    answer_xor(c,clen);


END:
    if ( b )
    {
        free(b);
        b = NULL;
    }
    if ( c )
    {
        free(c);
        c = NULL;
    }
    return;
}

int32_t comma_count ( char * b, int32_t blen )
{
    int32_t cnt = 0,k;

    for ( k=0; k<blen; ++k )
    {
        if ( b[k]==',' )
        {
            cnt++;
        }
    }

    return cnt;
}

char * read_file ( int32_t * len )
{
    int32_t flen = 4096;
    char * fbytes = calloc(1,flen);
    int32_t sz;
    char fname[] = "p059_cipher.txt";
    FILE * fd = fopen(fname,"r");

    if ( NULL==fd || NULL==fbytes )
    {
        printf("[%d] ERROR: fd = %p, fbytes = %p\n",__LINE__,fd,fbytes);
        goto END;
    }
    sz = fread(fbytes,1,flen,fd);
    if ( sz==4096 )
    {
        printf("[%d] ERROR: could not open %s\n",__LINE__,fname);
        goto ERROR;
    }
    *len = sz;
    goto END;

ERROR:
    if ( fbytes )
    {
        free(fbytes);
        fbytes = NULL;
    }
END:
    if ( fd )
    {
        fclose(fd);
        fd = NULL;
    }
    return fbytes;
}

char num_2_byte ( char * n )
{
    char c=0;
    int32_t k,len = strlen(n);

    for ( k=0; k<len && k<NUM_N; ++k )
    {
        c = c*10+n[k]-'0';
    }

    return c;
}

char * str_2_ascii ( char * b, int32_t blen, int32_t * clen )
{
    char num[NUM_N];
    char * a = NULL;
    int32_t alen = 0,ccnt = comma_count(b,blen);;
    int32_t nidx = 0, aidx=0, k;
    

    blen = strlen(b);
    *clen = ccnt+1;
    a = calloc(1,ccnt+1);
    if ( NULL==a )
    {
        printf("[%d] ERROR: could not allocate space\n",__LINE__);
        goto END;
    }

    memset(num,0,NUM_N);
    for ( k=0; k<blen; ++k )
    {
        if ( b[k]==',' || k==(blen-1) )
        {
            a[aidx++] = num_2_byte(num);
            nidx = 0;
            memset(num,0,NUM_N);
        }
        else
        {
            num[nidx++] = b[k];
        }
    }

    *clen = aidx;
    goto END;

ERROR:
    if ( a )
    {
        free(a);
        a = NULL;
    }
END:
    return a;
}

void print_xor ( FILE * fd, char * b, int32_t n, int32_t k1, int32_t k2, int32_t k3 )
{
    int32_t k;
    fprintf(fd,"[%d](%d,%d,%d)  ",__LINE__,k1,k2,k3);
    for ( k=0; k<n; ++k )
    {
        if ( isprint(b[k]) )
        {
            fprintf(fd,"%c",b[k]);
        }
        else
        {
            fprintf(fd,".");
        }
    }
    fprintf(fd,"\n");
}

void answer_xor ( char * a, int32_t alen )
{
    char key[3] = { 103, 111, 100 };
    int32_t m;
    char * b = calloc(1,alen);
    int32_t sum = 0;

    if ( NULL==b )
    {
        goto END;
    }

    for ( m=0; m<alen; m+=3 )
    {
        if ( m+3>alen )
        {
            break;
        }

        b[m]   = a[m]   ^ key[0];
        sum += ((int32_t)b[m] ) & 0xff;
        b[m+1] = a[m+1] ^ key[1];
        sum += ((int32_t)b[m+1] ) & 0xff;
        b[m+2] = a[m+2] ^ key[2];
        sum += ((int32_t)b[m+2] ) & 0xff;
    }
    if ( 0<alen-m )
    {
        b[m]   = a[m]   ^ key[0];
        sum += ((int32_t)b[m] ) & 0xff;
    }
    if ( 1<alen-m )
    {
        b[m+1] = a[m+1] ^ key[1];
        sum += ((int32_t)b[m+1] ) & 0xff;
    }
    if ( 2<alen-m )
    {
        b[m+2] = a[m+2] ^ key[2];
        sum += ((int32_t)b[m+2] ) & 0xff;
    }
    printf("[%d] (%d,%d) %s\n",__LINE__,alen,m,b);
    printf("[%d] Sum = %d\n",__LINE__,sum);

END:
    return;
}

void test_xor ( char * a, int32_t alen )
{
    int32_t k1, k2, k3;
    int32_t l1=97, l2=97, l3=97;
    int32_t m1=123, m2=123, m3=123;
    char key[3];
    char fname[] = "p059_output.txt";
    FILE * fd = fopen(fname,"w");
    char * b = calloc(1,alen);
    int32_t m,amx=alen;
    int32_t bad_count = 0;

    if ( NULL==fd || NULL==b )
    {
        printf("[%d] ERROR: fd = %p, b = %p\n",__LINE__,fd,b);
    }

    for ( k1=l1; k1<m1; ++k1 )
    {
        printf("k1 = %3d\r",k1);
        for ( k2=l1; k2<m2; ++k2 )
        {
            for ( k3=l1; k3<m3; ++k3 )
            {
                key[0] = (char)k1;
                key[1] = (char)k2;
                key[2] = (char)k3;
                memset(b,0,alen);
                for ( m=0; m<amx; m+=3 )
                {
                    if ( m+3>alen )
                    {
                        break;
                    }
                    b[m]   = a[m]   ^ key[0];
                    b[m+1] = a[m+1] ^ key[1];
                    b[m+2] = a[m+2] ^ key[2];
                    if ( !(isprint(b[m]) && isprint(b[m+1]) && isprint(b[m+2])) )
                    {
                        goto NEXT;
                    }
                }
                print_xor(fd,b,amx,k1,k2,k3);
NEXT:
                m = 1;
            }
        }
    }
    printf("\n");

END:
    if (fd)
    {
        fclose(fd);
        fd = NULL;
    }
    if ( b )
    {
        free(b);
        b = NULL;
    }
}

void dbg_print( char * b, int32_t n )
{
    int32_t k;

    for ( k=0; k<n; ++k )
    {
        printf("%d ",b[k]);
    }
    printf("\n");
    return;
}













