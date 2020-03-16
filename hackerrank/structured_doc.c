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

void get_sentences ( struct paragraph * para, char * ptext ) {
    int k;
    int sidx,pidx=0;
    int scnt=para->sentence_count;
    int plen=strlen(ptext);
    char sent[1024];


    dbg_print("paragraph: (%d) %s\n",para->sentence_count,ptext);
    for ( k=0; k<scnt; ++k ) {
        sidx = 0;
        memset(sent,0,1024);
        while ( pidx<plen && '.'!=ptext[pidx] ) {
            sent[sidx++] = ptext[pidx];
            pidx++;
        }
        pidx++;
        dbg_print("Sentence: %s\n",sent);
    }

    return;
}

void get_paragraphs ( struct document * doc, char * text ) {
    int k,m,pcnt = doc->paragraph_count,scnt;
    char para[1024];
    int pidx = 0, tidx = 0, dlen = strlen(text);;
    struct paragraph * cpara;

    for ( k=0; k<pcnt && tidx<dlen; ++k ) {
        pidx = 0;
        memset(para,0,1024);
        while ( tidx<dlen && '\n'!=text[tidx] ) {
            para[pidx++] = text[tidx];
            tidx++;
        }
        scnt = count_sentences(para);
        doc->data[k].sentence_count = scnt;
        doc->data[k].data = (struct sentence*)calloc(scnt,sizeof(struct sentence));
        cpara = &doc->data[k];
        get_sentences(cpara,para);
        tidx++;
    }

    return;
}

struct document get_document(char* text) {
    struct document ret;

    ret.paragraph_count = count_paragraphs(text);
    ret.data = (struct paragraph*)calloc(2,sizeof(*(ret.data)));
    get_paragraphs(&ret,text);

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

    struct document Doc = get_document(doc);

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












