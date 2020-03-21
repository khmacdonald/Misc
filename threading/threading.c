/*
gcc threading.c -o threading
 */

#include <pthread.h>
#include <stdio.h>

// thread function
void * tFunc ( void * args ) {
    while ( 1 ) {
        printf("I am %s\n",__FUNCTION__);
    }
}

int main ( void )  {
    pthread_t id;
    int ret;

    // creating thread
    ret = pthread_create(&id,NULL,tFunc,NULL);
    if ( 0==ret ) {
        printf("Thread successfully created\n");
    } else {
        printf("Thread not created\n");
        return 0;
    }

    while ( 1 ) {
        printf("I am main functin\n");
    }

    return 0;
}
