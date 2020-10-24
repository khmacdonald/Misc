/*
 * This is only for ASCII text processing.
 */

#ifndef TEXT_PROCESSOR_H
#define TEXT_PROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Delimited text data structure.
 * This will be dynamically allocated.  Make sure to
 * free the memory by using the provided destructor.
 */
struct text_delim_parse { 
    char delim;         /* The delimiter */
    int nelements;      /* The number of strings delimited */
    char * root;        /* Root of the delimited string */
    char ** elements;   /* The delimited strings */
};

typedef struct text_delim_parse * pTEXT_DELIM;

/*
 * Parses a text into an array of delimited string elements.
 */
pTEXT_DELIM
delimited_text_parser ( 
        char * text,        /* The text to parse */
        char delimiter );   /* The delimiter for texting */

void _destroy_delimited_text_parser ( pTEXT_DELIM td );
#define destroy_delimited_text_parser(TD) do { \
    if ( TD ) { \
        _destroy_delimited_text_parser(TD); \
        TD = NULL; \
    } \
} while(0)

#endif
