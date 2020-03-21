/* 
    Input format
The paragraph_count
The paragraphs of the document (each line is a single string of paragraphs).
The queries of the document (each line is a query, of 'q <options>')
1 -> 1 k
    Calls the function kth_paragraph
2 -> 2 k m
    Calls kth_sentence_in_mth_pararaph
2 -> 3 k m n
    Calls kth_word_in_mth_sentence_in_nth_pararaph
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../common/print_statements.h"

#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

int count_paragraphs ( char * text ) {
    int k, pcnt=0, slen = strlen(text);

    for ( k=0; k<slen; ++k ) {
        if ( '\n'==text[k] ) {
            pcnt++;
        }
    }

    return pcnt;
}

int count_sentences ( char * text ) {
    int k, scnt=0, slen=strlen(text);

    if ( slen<1 ) {
        return 0;
    }

    for ( k=0; k<slen; ++k ) {
        if ( '.'==text[k] ) {
            scnt++;
        }
    }

    return scnt;
}

int count_words ( char * text ) {
    int wcnt = 0;

    return wcnt;
}

void get_paragraph ( struct paragraph * para, char * text ) {
    dbg_print("Paragraph = %s\n",text);
    return;
}

struct document get_document(char* text) {
    int k,                      /* Dummy */
        pidx,tidx=0,            /* Paragraph and text index */
        tlen=strlen(text);;     /* Text length */
    char para[1024];            /* Paragraph text */
    struct document ret;        /* Document */

    /* Get the number of paragraphs in a document */
    ret.paragraph_count = count_paragraphs(text);

    /* Allocate the number of paragraphs for the document */
    ret.data = (struct paragraph*)calloc(2,sizeof(*(ret.data)));

    /* Get the paragraphs */
    for ( k=0; k<ret.paragraph_count; ++k ) {
        memset(para,0,1024);
        pidx=0;
        while ( 1 ) {
            /* A return or end of text indicates the end of a paragraph */
            if ( '\n'==text[tidx] || tlen-1==tidx ) {
                get_paragraph(&ret.data[k],para);
            }
            para[pidx++] = text[tidx];
            tidx++;
            if ( tlen==tidx ) {
                break;
            }
        }
    }

    return ret;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph (
        struct document Doc, 
        int k, 
        int m, 
        int n) {
    struct word ret;
    return ret;
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    struct sentence ret;
    return ret;
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    struct paragraph ret;
    return ret;
}


void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

/* ------------------------------------------------------------ */
#define LINESZ 1024
struct in_lines {
    char line[LINESZ];
    struct in_lines * next;
};
/* ------------------------------------------------------------ */
struct in_lines * input_lines ( char * infile );
void print_in_lines ( struct in_lines * ilines );
/* ------------------------------------------------------------ */
int main() {
    int k,in_idx,npara=0,nqueries=0;
    struct in_lines * ilines = input_lines("structured_doc.txt");
    struct in_lines * cline;
    char doc[1024];
    char * d = doc;
    int sz,dlen=1024;

    /* Get the number of paragraphs in the doc. */
    in_idx = atoi(ilines->line);
    dbg_print("in_idx = %d\n",in_idx);

    /* Get the doc. */
    memset(doc,0,1024);
    for ( k=0; k<in_idx; ++k ) {
        cline = ilines->next;
        if ( NULL==cline ) {
            err_print("Invalid line\n");
            return 1;
        }
        free(ilines);
        sz = snprintf(d,dlen,"%s",cline->line);
        d += sz;
        dlen -= sz;
        ilines = cline;
    }

    struct document Doc = get_document(doc); /* Process a document */

    printf("\n --------------- \n\n");
    /* Process queries */
    while ( 1 ) {
        cline = ilines->next;
        free(ilines);
        if ( NULL==cline ) {
            break;
        }
        dbg_print("%s",cline->line); /* Each line is a query */
        ilines = cline;
    }

    return 0;
}
/* ------------------------------------------------------------ */

struct in_lines * get_new ( FILE * fd ) {
    struct in_lines * nline = NULL;
    char * cl;
    char line[LINESZ];

    cl = fgets(line,LINESZ,fd);
    if ( NULL==cl ) {
        return NULL;
    }
    nline = (struct in_lines*)calloc(1,sizeof(*nline));
    snprintf(nline->line,LINESZ,"%s",line);
    nline->next = NULL;

    return nline;
}

struct in_lines * input_lines ( char * infile ) {
    struct in_lines * ret_lines = NULL;
    struct in_lines * cur_line = NULL;
    struct in_lines * new_line = NULL;
    FILE * fd = fopen(infile,"r");

    do {
        new_line = get_new(fd);
        if ( NULL==new_line ) {
            break;
        }
        if ( NULL==ret_lines ) {
            ret_lines = new_line;
            cur_line = ret_lines;
        } else {
            cur_line->next = new_line;
            cur_line = cur_line->next;
        }
    }while ( 1 );

    fclose(fd);
    return ret_lines;
}

void print_in_lines ( struct in_lines * ilines ) {
    while ( ilines ) {
        printf("%s",ilines->line);
        if ( '\n'!=ilines->line[strlen(ilines->line)-1] ) {
            printf("\n");
        }
        ilines = ilines->next;
    }
}












