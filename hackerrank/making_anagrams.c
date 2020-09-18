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

void count_letters ( int * alpha, char * s ) {
    int slen = strlen(s),k,c;
    memset(alpha,0,26*sizeof(alpha[0]));
    
    for ( k=0; k<slen; ++k ) {
        c = s[k]-'a';
        alpha[c]++;
    }
}
// Complete the makingAnagrams function below.
int makingAnagrams(char* s1, char* s2) {
    int a1[26];
    int a2[26];
    int k, tot=0, d;

    count_letters(a1,s1);
    count_letters(a2,s2);

    for ( k=0; k<26; ++k ) {
        if ( a1[k]>a2[k] ) {
            d = a1[k] - a2[k];
        } else if ( a1[k]<a2[k] ){
            d = a2[k] - a1[k];
        } else {
            d = 0;
        }
        tot += d;
    }
    return tot;
}

void test01() {
    char * s1 = "cde";
    char * s2 = "abc";
    int diff = makingAnagrams(s1,s2);

    printf("s1 = %s\n",s1);
    printf("s2 = %s\n",s2);
    printf("diff = %d\n",diff);
}

void test02() {
    char * s1 = "absdjkvuahdakejfnfauhdsaavasdlkj";
    char * s2 = "djfladfhiawasdkjvalskufhafablsdkashlahdfa";
    int diff = makingAnagrams(s1,s2);

    printf("s1 = %s\n",s1);
    printf("s2 = %s\n",s2);
    printf("diff = %d\n",diff);
}


int main ( ) {
    char * delim = "------------------------------------------------";
    test01();
    printf("%s\n",delim);
    test02();
}

#if 0
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s1 = readline();

    char* s2 = readline();

    int result = makingAnagrams(s1, s2);

    fprintf(fptr, "%d\n", result);

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
