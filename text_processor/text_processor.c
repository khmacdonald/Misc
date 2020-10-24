

#include "text_processor.h"


/* ------------------------- */
/*     STATIC PROTOTYPES     */
pTEXT_DELIM td_alloc( char * text, char delimiter );
/* ------------------------- */

/* ------------------------- */
/*      API DEFINITIONS      */
pTEXT_DELIM
delimited_text_parser ( 
        char * text,        
        char delimiter )  {  
    pTEXT_DELIM td = NULL;

    td = td_alloc(text,delimiter);
    if ( NULL==td ) {
        return NULL;
    }
    return td;
}

void _destroy_delimited_text_parser ( pTEXT_DELIM td ) {
    if ( td ) {
        if ( td->root ) {
            free(td->root);
        } 
        memset(td,0,sizeof(*td));
        free(td);
    }
}
/* ------------------------- */

/* ------------------------- */
/*     STATIC DEFINITIONS    */
pTEXT_DELIM td_alloc( char * text, char delimiter ) {
    int tlen = 0;
    pTEXT_DELIM td = NULL;

    /* Check valid pointer.  Also check valid delimiter */
    if ( NULL==text || delimiter<9 || 126<delimiter ) {
        return NULL;
    }

    td = calloc(1,sizeof(*td));
    if ( NULL==td ) {
        return NULL;
    }
    tlen = strlen(text);
    td->root = calloc(tlen+1,sizeof(text[0]));
    if ( NULL==td->root ) {
        free(td);
        td = NULL;
        return NULL;
    }

    return td;
}

/* ------------------------- */
