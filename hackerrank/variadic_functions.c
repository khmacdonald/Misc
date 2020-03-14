#include <stdarg.h>
#include <stdio.h>

int sum ( int count, ... ) {
    int sum = 0,k;
    va_list(args);
    va_start(args,count);

    for ( k=0; k<count; ++k ) {
        sum += va_arg(args,int);
    }
    va_end(args);

    return sum;
}

int main ( ) { 
    printf("sum = %d\n",sum(5,1,2,3,4,5));
    return 0;
}
