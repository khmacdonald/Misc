#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int beautifulBinaryString(char* b) {
    int slen = strlen(b);
    int count = 0;
    int k;

    for ( k=0; k<slen-3; ) {
        //printf("[%d] k = %d, b = %s\n",__LINE__,k,b+k);
        if ( '0'==b[k] && '1'==b[k+1] && '0'==b[k+2]) {
            count++;
            k += 3;
        } else {
            k++;
        }
    }
    return count;
}


void test01() {
    char * s1 = "0101010";
    int count = beautifulBinaryString(s1);

    printf("s1 = %s\n",s1);
    printf("count = %d\n",count);
}

void test02() {
    char * s1 = "0100101010";
    int count = beautifulBinaryString(s1);

    printf("s1 = %s\n",s1);
    printf("count = %d\n",count);
}

void test03() {
    char * s1 = "01100";
    int count = beautifulBinaryString(s1);

    printf("s1 = %s\n",s1);
    printf("count = %d\n",count);
}

void test04() {
    char * s1 = "0100101010100010110100100110110100011100111110101001011001110111110000101011011111011001111100011101";
    int count = beautifulBinaryString(s1);
    int expected = 10;

    printf("s1 = %s\n",s1);
    printf("count = %d\n",count);
    printf("expected = %d\n",expected);
}

void test05() {
    char * s1 = "100110110011111101110100011011101000011010111001001011010010110010111011100000000100011111100101010";
    int count = beautifulBinaryString(s1);
    int expected = 11;

    printf("s1 = %s\n",s1);
    printf("count = %d\n",count);
    printf("expected = %d\n",expected);
}




int main ( ) {
    char * delim = "------------------------------------------------";
    test01();
    printf("%s\n",delim);
    test02();
    printf("%s\n",delim);
    test03();
    printf("%s\n",delim);
    test04();
    printf("%s\n",delim);
    test05();
}

