/*
https://www.hackerrank.com/challenges/dynamic-array-in-c/problem
 */
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

/*
 * This stores the total number of books in each shelf.
 */
int* total_number_of_books;

/*
 * This stores the total number of pages in each book of each shelf.
 * The rows represent the shelves and the columns represent the books.
 */
int** total_number_of_pages;

int main()
{
    int total_number_of_shelves;
    printf("The number of shelves:\n");
    scanf("%d", &total_number_of_shelves);
    total_number_of_books = calloc(total_number_of_shelves,sizeof(int));
    total_number_of_pages = calloc(total_number_of_shelves,sizeof(int*));
    
    int total_number_of_queries;
    printf("The number of queries:\n");
    scanf("%d", &total_number_of_queries);
    
    while (total_number_of_queries--) {
        int type_of_query;
        scanf("%d", &type_of_query);
        
        if (type_of_query == 1) {
            /*
             * Process the query of first type here.
             */
            int x, y;
            scanf("%d %d", &x, &y);
            if ( NULL==total_number_of_pages[x] ) {
                printf("Allocating shelf %d.\n",x);
                total_number_of_pages[x] = calloc(1100,sizeof(int));
            }
            total_number_of_pages[x][total_number_of_books[x]++] = y;
            printf("Shelf %d has %d books\n",x,total_number_of_books[x]);
        } else if (type_of_query == 2) {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%d\n", *(*(total_number_of_pages + x) + y));
        } else {
            int x;
            scanf("%d", &x);
            printf("%d\n", *(total_number_of_books + x));
        }
    }

    if (total_number_of_books) {
        free(total_number_of_books);
    }
    
    for (int i = 0; i < total_number_of_shelves; i++) {
        if (*(total_number_of_pages + i)) {
            free(*(total_number_of_pages + i));
        }
    }
    
    if (total_number_of_pages) {
        free(total_number_of_pages);
    }
    
    return 0;
}
