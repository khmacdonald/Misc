#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


/* ---------------------------------------------------------------- */
/*                           PROTOTYPES                             */

void print_grid ( int grid[9][9] );
void print_grid_euler ( int grid[9][9] );

void read_grid ( int grid[9][9] );
void read_row ( int row[9] );
void zero_grid ( int grid[9][9] );

int n_possible ( int grid[9][9], int x, int y, int n ); 
void solve ( int grid[9][9] ) ;

/* ---------------------------------------------------------------- */
void test_grid ( int grid[9][9] );
/* ---------------------------------------------------------------- */

/* ---------------------------------------------------------------- */
/*                              MAIN                                */

int main() {
    int grid[9][9] = {0};

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    test_grid(grid);
    solve(grid);

    return 0;
}

/* ---------------------------------------------------------------- */


/* ---------------------------------------------------------------- */
/*                           DEFINITIONS                            */

/* A pretty print function */
void print_grid ( int grid[9][9] ) {
    int r, c;
    char * rdelim = "|-------+-------+-------|";
    char * boarder= "|-----------------------|";

    printf("%s\n",boarder);
    for ( r=0; r<9; ++r ) {
        printf("| ");
        for ( c=0; c<9; ++c ) {
            printf("%d ",grid[r][c]);
            if ( 2==c || 5==c ) {
                printf("| ");
            }
        }
        printf("|\n");
        if ( 2==r || 5==r ) {
            printf("%s\n",rdelim);
        }
    }
    printf("%s\n",boarder);
}

/* Hackerrank Euler project print format */
void print_grid_euler ( int grid[9][9] ) {
    int row, col;

    for ( row=0; row<9; ++row ) {
        for ( col=0; col<9; ++col ) {
            printf("%d",grid[row][col]);
        }
        printf("\n");
    }
    return;
}

/* Reads a Sudoku puzzle row by row */
void read_grid ( int grid[9][9] ) {
    int row=0;

    zero_grid(grid);
    for ( row=0; row<9; ++row ) {
        read_row(grid[row]); /* Read in a row at a time */
    }
    return;
}

/* Read each row of a sudoku puzzle */
void read_row ( int row[9] ) {
    char c,col;

    for ( col=0; col<9; ++col ) {
        c = fgetc(stdin);
        row[col] = c-'0'; /* Read in a character at a time */
    }
    c = fgetc(stdin); /* Get the '\n' end of line character */
    return;
}

/* Zeros a grid.  It's essentially an initialization function */
void zero_grid ( int grid[9][9] ) {
    int row,col;

    for ( row=0; row<9; ++row ) {
        for ( col=0; col<9; ++col ) {
            grid[row][col] = 0;
        }
    }

    return;
}

/* A recursive solve of sudoku puzzles */
void solve ( int grid[9][9] ) {
    int r,c,n;

    for ( r=0; r<9; ++r ) {          
        for ( c=0; c<9; ++c ) {
            if ( 0==grid[r][c] )    /* Check grid for unknown entries */
            {
                for ( n=1; n<10; ++n ) {
                    /* For each n, check to see if that value can be placed in that location */
                    if ( n_possible(grid,r,c,n) ) {
                        grid[r][c] = n; /* Try n */
                        solve(grid);    /* Recurse */
                        grid[r][c] = 0; /* Check another n */
                    }
                } /* for n */
                return; /* If no n is possible, return */
            } /* if 0 */
        } /* for c */
    } /* for r */
    /* 
     * If here, all locations in the grid are non-zero, therefore, the
     * puzzle is solved.
     */
    //printf("    **** Solved **** \n");
    //print_grid(grid);
    print_grid_euler(grid);
    exit(0);
}

int n_in_row ( int grid[9][9], int x, int n ) {
    int k;

    for ( k=0; k<9; ++k ) {
        if ( n==grid[x][k] ) { /* Checks to see if n already exists in row x */
            return 1;
        }
    }

    return 0;
}

int n_in_col ( int grid[9][9], int x, int n ) {
    int k;

    for ( k=0; k<9; ++k ) {
        if ( n==grid[k][x] ) { /* Checks to see if n already exists in column x */
            return 1;
        }
    }

    return 0;
}

/* Determine if x is in [0,1,2],[3,4,5], or [6,7,8] */
int block_number ( int x ) {
    if ( 0<=x && x<3 ) {
        return 0;
    } else if ( 3<=x && x<6 ) {
        return 3;
    } else {
        return 6;
    }
}

int n_in_block ( int grid[9][9], int x, int y, int n ) {
    int row = block_number(x);
    int col = block_number(y);
    int r,c;;

    for ( r=0; r<3; ++r ) {
        for ( c=0; c<3; ++c ) {
            if ( n==grid[row+r][col+c] ) { /* Checks to see if n already exists in grid block */
                return 1;
            }
        }
    }
    return 0;
}

int n_possible ( int grid[9][9], int x, int y, int n ) {
    if ( n_in_row(grid,x,n) ||  
         n_in_col(grid,y,n) || 
         n_in_block(grid,x,y,n) ) {
        /* 
         * If n is already in row x, column y, or the block 
         * containing x, y, n is not possible at (x,y).
         */
        return 0; 
    }
    return 1;
}







/* ---------------------------------------------------------------- */
/* Prevents command line input each binary invocation */
void test_grid ( int grid[9][9] ) {
    int row, col;
    char * cgrid[9] = {
        "123456780",
        "456780123",
        "780123456",
        "234567801",
        "567801234",
        "801234567",
        "345678012",
        "678012345",
        "012345678"
    };

    for ( row=0; row<9; ++row ) {
        for ( col=0; col<9; ++col ) {
            grid[row][col] = cgrid[row][col] - '0';
        }
    }

    return;
}

