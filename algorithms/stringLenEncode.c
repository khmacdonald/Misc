#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * stringLenEncode ( char * str ) ;

int main ( int argc, char ** argv ) {
    char a[32] = {0};
    char * new_string = NULL;

    snprintf(a,32,"aaabbccca");

    if ( 1<argc ) {
        printf("Encoding '%s'\n",argv[1]);
        new_string = stringLenEncode(argv[1]); 
    } else {
        printf("Encoding '%s'\n",a);
        new_string = stringLenEncode(a);
    }
    if ( new_string ) {
        printf("Encoded: %s\n",new_string);
        free(new_string);
        new_string = NULL;
    } else {
        printf("Encoding failed\n");
    }

    return 0;
}

char * stringLenEncode ( char * str ) {
    int slen = strlen(str);
    char * tmpString = calloc(2*slen+1,1); /* Worst case scenario */
    char * tstr = tmpString;
    int tlen = 2*slen+1;
    char * nString = NULL;
    int nlen;
    char k,cChar;
    int cCount,sz,one_more=0;

    if ( NULL==tmpString ) {
        return NULL;
    }

    /* Start with the first character */
    cChar = str[0];
    cCount = 1;
    k = 1;
    while ( k<slen ) {
        one_more = 0;
        while ( k<slen && cChar==str[k] ) {
            cCount++;
            k++;
        }
        /* cCount is the number of times cChar exists in this area of the string */
        sz = snprintf(tstr,tlen,"%d%c",cCount,cChar);
        tstr += sz; /* Keep track of the location of where you can print next */
        tlen -= sz;
        if ( k<slen && tlen>0 ) {
            one_more = 1;
            cChar = str[k]; /* A new character has been found, so note it */
            k++;            /* Go to the next string */
            cCount = 1;     /* There is at least 1 character left */
        } else {
            break;
        }
    }
    if ( one_more ) {
        snprintf(tstr,tlen,"%d%c",cCount,cChar);
    }

    nlen = strlen(tmpString)+1;
    if ( nlen < tlen ) {
        nString = calloc(nlen,1); /* Resize string for compression */
        if ( NULL==nString ) {
            free(tmpString);
        }
        snprintf(nString,nlen,"%s",tmpString);
        free(tmpString);
    } else {
        nString = tmpString; /* Worst case achieved */
    }

    return nString;
}
