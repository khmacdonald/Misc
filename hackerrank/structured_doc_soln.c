#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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

    return pcnt+2;
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
    int k;
    int wcnt = 0, slen = strlen(text);

    for ( k=0; k<slen; ++k ) {
        if ( ' '==text[k] ) {
            wcnt++;
        }
    }

    return wcnt+1; /* There is no space after the last word */
}

void get_sentence ( struct sentence * sent, char * text ) {
    int k;
    int wcnt = count_words(text),
        slen = strlen(text);
    char word[1024];
    char * new_word;
    int widx, sidx=0;

    /* Allocate memory for each word */
    sent->data = calloc(wcnt,sizeof(struct word));
    sent->word_count = wcnt;

    /* Get each word in the sentence */
    for ( k=0; k<wcnt; ++k ) {
        memset(word,0,1024);    /* Zero the word */
        widx=0;                 /* Start at the beginning of a word */
        while ( sidx<slen ) {
            if ( ' '==text[sidx] || '\0'==text[sidx+1] ) {
                if ( '\0'==text[sidx+1] ) {
                    word[widx++] = text[sidx];
                }
                /* Allocate each word */
                sent->data[k].data= calloc(1,strlen(word)+1);
                snprintf(sent->data[k].data,strlen(word)+1,"%s",word);
                sidx++;
                break;
            }
            word[widx++] = text[sidx];
            sidx++;
        }
    }
}

void get_paragraph ( struct paragraph * para, char * text ) {
    int k;                            /* Dummy */
    int scnt = count_sentences(text); /* Get the number of sentences in paragraph */
    char sent[1024];                  /* The current sentence */
    int sidx, tidx=0;                 /* The sentence and text index */

    /* Allocate the sentence data structures */
    para->data = calloc(scnt,sizeof(struct sentence));
    para->sentence_count = scnt;

    /* Get the sentences */
    for ( k=0; k<scnt; ++k ) {
        memset(sent,0,1024); /* Zero out the sentence */
        sidx = 0;            /* Start at the beginning of hte sentence */
        while ( tidx<strlen(text) ) {
            if ( '.'==text[tidx] ) {
                get_sentence(&para->data[k],sent);
                tidx++;
                break;
            }
            sent[sidx++] = text[tidx];
            tidx++;
        }
    }

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
    ret.data = (struct paragraph*)calloc(2,sizeof(struct paragraph));

    /* Get the paragraphs */
    for ( k=0; k<ret.paragraph_count && tidx<tlen; ++k ) {
        memset(para,0,1024); /* Zero out the sentence */
        pidx=0;              /* Start at the beginning of the sentence */
        while ( 1 ) {
            /* A return or end of text indicates the end of a paragraph */
            if ( '\n'==text[tidx] || tlen-1==tidx ) {
                get_paragraph(&ret.data[k],para);
                tidx++; /* Make sure to skip the return character */
                break;  /* Get the next sentence or processing finished */
            }
            para[pidx++] = text[tidx]; /* Capture the next character of the sentence */
            tidx++;
        }
    }

    return ret;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    struct word ret = Doc.data[n-1].data[m-1].data[k-1];
    return ret;

}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    struct sentence ret = Doc.data[m-1].data[k-1];
    return ret;

}

struct paragraph kth_paragraph(struct document Doc, int k) {
    struct paragraph ret = Doc.data[k-1];
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

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    printf("-------------------------\n");
    print_document(Doc);
    printf("\n");
    printf("-------------------------\n");

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}
