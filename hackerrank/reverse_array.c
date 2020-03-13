#include <stdio.h>
#include <stdlib.h>

void print_arr ( int * arr, int n, int new_line ) { 
    int k;

    if ( n<1 ) {
        return;
    }

    printf("(%d",arr[0]);
    for ( k=1; k<n; ++k ) {
        printf(", %d",arr[k]);
    }
    printf(")");
    if ( new_line ) {
        printf("\n");
    }
}

void rev_arr ( int * arr, int n ) {
    int half = n/2,k;
    int tmp;

    //printf("half = %d\n",half);
    //print_arr(arr,n,1);
    for ( k=0; k<half; ++k ) {
        if ( arr[k]!=arr[n-1-k] ) {
            //printf("[%d] Swapping %d and %d\n",k,arr[k],arr[n-1-k]);
            tmp = arr[k];
            arr[k] = arr[n-1-k];
            arr[n-1-k] = tmp;
        }
    }
    //print_arr(arr,n,1);
}

void test ( char * test_name, int * arr, int n ) {
    printf("\n%s: ",test_name);
    print_arr(arr,n,0);
    rev_arr(arr,n);
    printf(" -> ");
    print_arr(arr,n,1);
    printf("\n");
}

int main ( ) {
    int arr01[6] = { 16, 13, 7, 2, 1, 12 };
    int arr02[7] = { 1, 13, 15, 20, 12, 13, 2 };
    int arr03[8] = { 15, 5, 16, 15, 17, 11, 5, 11 };
    
    test("test 1",arr01,6);
    test("test 2",arr02,7);
    test("test 3",arr03,8);

    return 0;
}

int main_orig()
{
    int num, *arr, i;
    
    scanf("%d", &num);
    arr = (int*) malloc(num * sizeof(int));
    for(i = 0; i < num; i++) {
        scanf("%d", arr + i);
    }


    /* Write the logic to reverse the array. */

    for(i = 0; i < num; i++)
        printf("%d ", *(arr + i));

    return 0;
}
