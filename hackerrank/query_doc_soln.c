#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>

#include "../common/print_statements.h"

#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

char * copy_text ( char * text ) {
    int slen = strlen(text)+1;
    char * ttext = calloc(slen,sizeof(*ttext));
    snprintf(ttext,slen,"%s",text);
    return ttext;
}

int count_delim ( char * text, char * delim ) {
    char * ttext = copy_text(text);
    int dcnt = 0;
    char * tok = strtok(ttext,delim);

    while ( tok ) {
        dcnt++;
        tok = strtok(NULL,delim);
    }

    free(ttext);
    return dcnt;
}

int get_token ( char * token, int tlen, int k, char * text, int slen, char delim ) {
    int idx = 0;
    memset(token,0,tlen);

    for ( ; idx<tlen && k<slen; ++k ) {
        if ( delim==text[k] ) {
            return k+1;
        }
        token[idx++] = text[k];
    }
    return k;
}

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return document[n-1][m-1][k-1];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    return document[m-1][k-1];
}

char*** kth_paragraph(char**** document, int k) {
    return document[k-1];
}

char ** get_sentence ( char * text ) {
    char * delim = " ";
    int w,k,
        slen = strlen(text),
        wcnt = count_delim(text,delim);
    char word[MAX_CHARACTERS];
    char ** sent= calloc(wcnt,sizeof(*sent));

    for ( k=0, w=0; w<wcnt && k<slen; ++w ) {
        k = get_token(word,MAX_CHARACTERS,k,text,slen,delim[0]);
        sent[w] = copy_text(word);
    }

    return sent;
}

char *** get_paragraph ( char * text ) {
    char * delim = ".";
    int s,k,
        slen = strlen(text),
        scnt = count_delim(text,delim);
    char sent[MAX_CHARACTERS];
    char *** para = calloc(scnt,sizeof(*para));

    for ( k=0,s=0; s<scnt && k<slen; ++s ) {
        k = get_token(sent,MAX_CHARACTERS,k,text,slen,delim[0]);
        para[s] = get_sentence(sent);
    }

    return para;
}

char**** get_document(char* text) {
    char * delim = "\n";
    int k,p,
        slen = strlen(text),
        pcnt = count_delim(text,delim); 
    char para[MAX_CHARACTERS];
    char **** doc = calloc(pcnt,sizeof(*doc));

    for ( k=0,p=0; p<pcnt && k<slen; ++p ) {
        k = get_token(para,MAX_CHARACTERS,k,text,slen,delim[0]);
        doc[p] = get_paragraph(para);
    }

    return NULL;
}

/* ---------------------------------------------------------------- */

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

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

/* ---------------------------------------------------------------- */
int main_mine ( int argc, char ** argv );
int main_orig ( );
/* ---------------------------------------------------------------- */
int main ( int argc, char ** argv ) {
    //main_mine(argc,argv);
    main_orig();
}

/* ---------------------------------------------------------------- */
void setup_text ( char * text, int len ) {
    int sz = snprintf(text,len,"Learning C is fun.\n");
    text += sz;
    len -= sz;
    snprintf(text,len,"Learning pointers is more fun.It is good to have pointers.");
    
}

#define DSZ 1024
int main_mine ( int argc, char ** argv ) {
    char text[DSZ] = {0};
    char**** document = NULL;

    setup_text(text,DSZ);
    document = get_document(text);

    return 0;
}

/* ---------------------------------------------------------------- */

int main_orig() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
    return 0;
}
