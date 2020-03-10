#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

#define print_here printf("[%d] Here\n",__LINE__)

// Complete the checkMagazine function below.
void checkMagazine_old(int magazine_count, char** magazine, int note_count, char** note) {

    // ---------------------------------
    //          Below is my code
    // ---------------------------------
#define DSZ (1<<15)
#define WSZ 8
    struct word_count {
        char word[WSZ]; 
        int count;
    };
    struct word_count word_table[DSZ] = {0};
    int k,m,used=0;
    int found = 0;

    // Set up word count for magazine
    for ( k=0; k<magazine_count; ++k ) {
        for ( m=0; m<DSZ; ++m ) {
            if ( 0==word_table[m].count ) {
                snprintf(word_table[m].word,WSZ,"%s",magazine[k]);
                word_table[m].count++;
                used++;
                break;
            }
            if ( 0==strncmp(word_table[m].word,magazine[k],WSZ) ) {
                word_table[m].count++;
                break;
            }
        }
    }
    //printf("[%d] used = %d\n",__LINE__,used);

    for ( k=0; k<note_count; ++k ) {
        found = 0;
        for ( m=0; m<used; ++m ) {
            if ( 0==strncmp(word_table[m].word,note[k],WSZ) ) {
                if ( word_table[m].count>0 ) {
                    word_table[m].count--;
                    found = 1;
                    break;
                } else {
                    printf("No\n");
                    return;
                }
            }
        }
        if ( !found ) {
            printf("No\n");
            return;
        }
    }
    printf("Yes\n");

    // ---------------------------------
    //          Above is my code
    // ---------------------------------

}

// ------------------------------------------------------------------
int fast_hash ( char * str ) {
    int mask = (1<<15)-1,k,hash = 0xbeef,tmp;

    for ( k=0; k<strlen(str); ++k ) {
        tmp = (int)str[k]-'0';
        hash = ((hash*10) + tmp) & mask;
    }

    hash = ((hash>>8) ^ hash) & 0xff;

    return hash;
}

#define WDSZ 8
struct node {
    struct node * next;
    char word[WDSZ];
    int count;
};

struct list {
    struct node * root;
    int count;
};

void add_node ( struct list * list, char * word ) {
    struct node * node = NULL;
    struct node * new_node = NULL;

    if ( NULL!=list->root ) {
        node = list->root;
        do {
            if ( 0==strncmp(node->word,word,WDSZ) ) {
                node->count++;
                return;
            }
            if ( NULL==node->next ) {
                break;
            }
            node = node->next;
        } while ( 1 );
    }
    new_node = (struct node*)calloc(1,sizeof(*new_node));
    snprintf(new_node->word,WDSZ,"%s",word);
    new_node->count++;
    if ( NULL==list->root ) {
        list->root = new_node;
    } else {
        node->next = new_node;
    }
    list->count++;
}

void build_dictionary ( struct list * list, int wcnt, char ** words ) {
    int k = 0,idx;

    for ( k=0; k<wcnt; ++k ) {
        idx = fast_hash(words[k]);
        add_node(&(list[idx]),words[k]);
    }
}

int is_in_dictionary ( struct list * list, char * word ) {
    struct node * node = NULL;

    printf("[%s]\n",word);
    if ( NULL==list->root ) {
        printf("    No root\n");
        return 0;
    }

    for ( node = list->root; NULL!=node->next; node = node->next ) {
        printf("    (%s) - ",node->word);
        if ( 0==strncmp(word,node->word,WDSZ) )
        {
            if ( 0==node->count ) {
                printf(" none left\n");   
                return 0;
            }
            printf(" found\n");
            node->count--;
            return 1;
        } else {
            printf(" not found\n");
        }
    }

    return 0;
}

// Complete the checkMagazine function below.
void checkMagazine(int magazine_count, char** magazine, int note_count, char** note) {
#define LISTSZ 256
    struct list list[LISTSZ] = {0};
    int k,hash;

    build_dictionary(list,magazine_count,magazine);

    for ( k=0; k<note_count; ++k ) {
        hash = fast_hash(note[k]);
        if ( !is_in_dictionary(&(list[hash]),note[k]) ) {
            printf("No\n");
            return;
        }
    }
    printf("Yes\n");
    return;
}
// ------------------------------------------------------------------

void test01() {
    char * magazine[6] = { "give", "me", "one", "grand", "today", "night" };
    char * note[4] = { "give", "one", "grand", "today" };

    checkMagazine(6,magazine,4,note);
}

void test02() {
    //line1 = "6 5"
    char * magazine[6] = {"two", "times", "three", "is", "not", "four" };
    char * note[5] = { "two", "times", "two", "is", "four" };
    checkMagazine(6,magazine,5,note);
}

void test03() {
    //line1 = "7 4"
    char * magazine[7] = { "ive", "got", "a", "lovely", "bunch", "of", "coconuts" };
    char * note[4] = { "ive", "got", "some", "coconuts" };
    checkMagazine(7,magazine,4,note);
}

int main() {
    printf("   Test 1\n");
    test01();
    printf("--------------------------\n");
    printf("   Test 2\n");
    test02();
    printf("--------------------------\n");
    printf("   Test 3\n");
    test03();

    return 0;
}

int orig_main()
{
    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
