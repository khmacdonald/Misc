#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem

I am printing 'YES' here, but the site says the Expected Output is 'YES', 
but it still says I am returning the wrong answer.
 */

char* readline();

// Complete the isValid function below.

// Please either make the string static or allocate on the heap. For example,
// static char str[] = "hello world";
// return str;
//
// OR
//
// char* str = "hello world";
// return str;
//
/*
    Valid strings:
        1. Each character occurs the same number of times.
        2. If one character can be removed to satisfy 1. the string is valid.
 */
char* isValid(char* s) {
    static char * ret[2] = { "YES" , "NO" };
    int count[256] = {0};
    int slen = strlen(s);
    int max = 0, min = slen+1, mncnt=0, mxcnt=0,k;

    for ( k=0; k<slen; ++k ) {
        /* Count the numer of times a character occurs.  */
        count[s[k]]++; 
    }

    for ( k=0; k<256; ++k ) {
        if ( 0==count[k] ) {
            continue;
        }
        max = ( max < count[k] ) ? count[k] : max;
        min = ( min > count[k] ) ? count[k] : min;
    }

    if ( max==min ) {
        /* All characters occur the same number of times */
        return ret[0];
    }

    /* 
        Handle special cases.  
        First count the number of characters that are maxes and mins.
     */
    for ( k=0; k<256; ++k ) {
        if ( count[k] ) {
            printf("'%c' -> %d\n",k,count[k]);
            if ( max==count[k] ) {
                mxcnt++;
            } else {
                mncnt++;
            }
        }
    }

    printf("max = %d, mxcnt = %d, min = %d, mncnt = %d\n",
           max,mxcnt,min,mncnt);
    if ( 1==min && 1==mncnt ) {
        /* If one character occurs once, it can simply be removed */
        return ret[0];
    } else if ( 1==mxcnt && (1==(max-min)) ) {
        /* 
            If there is only one max occuring character, one of them can
            be removed to equalize the occurrence with the mins.
         */
        return ret[0];
    }
    printf("[%d] Here\n",__LINE__);
    return ret[1];
}

/* ------------------------------------------------------------------------ */

char * test_fail = "ibfdgaeadiaefgbhbdghhhbgdfgeiccbiehhfcggchgghadhdhagfbahhddgghbdehidbibaeaagaeeigffcebfbaieggabcfbiiedcabfihchdfabifahcbhagccbdfifhghcadfiadeeaheeddddiecaicbgigccageicehfdhdgafaddhffadigfhhcaedcedecafeacbdacgfgfeeibgaiffdehigebhhehiaahfidibccdcdagifgaihacihadecgifihbebffebdfbchbgigeccahgihbcbcaggebaaafgfedbfgagfediddghdgbgehhhifhgcedechahidcbchebheihaadbbbiaiccededchdagfhccfdefigfibifabeiaccghcegfbcghaefifbachebaacbhbfgfddeceababbacgffbagidebeadfihaefefegbghgddbbgddeehgfbhafbccidebgehifafgbghafacgfdccgifdcbbbidfifhdaibgigebigaedeaaiadegfefbhacgddhchgcbgcaeaieiegiffchbgbebgbehbbfcebciiagacaiechdigbgbghefcahgbhfibhedaeeiffebdiabcifgccdefabccdghehfibfiifdaicfedagahhdcbhbicdgibgcedieihcichadgchgbdcdagaihebbabhibcihicadgadfcihdheefbhffiageddhgahaidfdhhdbgciiaciegchiiebfbcbhaeagccfhbfhaddagnfieihghfbaggiffbbfbecgaiiidccdceadbbdfgigibgcgchafccdchgifdeieicbaididhfcfdedbhaadedfageigfdehgcdaecaebebebfcieaecfagfdieaefdiedbcadchabhebgehiidfcgahcdhcdhgchhiiheffiifeegcfdgbdeffhgeghdfhbfbifgidcafbfcd";
//YES

int main ( ) {
    char * answer = isValid(test_fail);

    printf("[%d] test_fail = %s\n",__LINE__,answer);

    return 0;
}

#define NSTRINGS 4
int main_old ( int argc, char ** argv ) {
    char * test_strings[NSTRINGS] = { "aabbcd", "aabbccddeefghi", 
                                      "abcdefghhgfedecba", test_fail };
    char * test_expect[NSTRINGS] = { "NO", "NO", "YES", "YES" };
    int k;

    for ( k=0; k<NSTRINGS; ++k ) {
        printf("[%d] string - '%s'\n",__LINE__,test_strings[k]);
        printf("     exp: %s\n",test_expect[k]);
        printf("          %s\n",isValid(test_strings[k]));
    }

    return 0;
}

/* ------------------------------------------------------------------------ */

#if 0
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = isValid(s);

    fprintf(fptr, "%s\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}
#endif
