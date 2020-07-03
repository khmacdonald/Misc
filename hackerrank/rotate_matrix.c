/*
 https://www.hackerrank.com/challenges/matrix-rotation-algo/problem

 Executes correctly, just not fast enough.
 */

 #include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

void print_matrix ( int row, int col, int ** mat ) {
    int k, m;
    for ( k=0; k<row; ++k ) {
        for ( m=0; m<col; ++m ) {
            printf("%4d ",mat[k][m]);
        }
        printf("\n");
    }
}

/* Counter clockwise outer ring by 1, then recurse to the next inner ring */
void shift_1_rec ( int rstart, int rlen, int cstart, int clen,
                   int row, int col, int ** mat ) {
    int k, tmp, r, c;

    if ( rlen<=1 || clen<=1 ) {
        return;
    }
    if ( rstart+rlen > row || cstart+clen > col ) {
        printf("[%d] Error: out of bounds indices\n",__LINE__);
        exit(1);
    }

    tmp = mat[rstart][cstart];
    /* Shift first row */
    for ( k=1; k<clen; ++k ) {
        r = rstart;
        c = cstart+k-1;
        mat[r][c] = mat[r][c+1];
    }

    /* Shift last column */
    for ( k=1; k<rlen; ++k ) {
        r = rstart+k-1;
        c = cstart+clen-1;
        mat[r][c] = mat[r+1][c];
    }

    /* Shift last row */
    for ( k=clen-1; k>0; k-- ) {
        r = rstart+rlen-1;
        c = cstart+k;
        mat[r][c] = mat[r][c-1];
    }
    //print_matrix(row,col,mat);

    /* Shift first column */
    for ( k=rlen-1; k>0; k-- ) {
        r = rstart+k;
        c = cstart;
        mat[r][c] = mat[r-1][c];
    }

    /* Add tmp back */
    mat[rstart+1][cstart] = tmp;
    shift_1_rec(rstart+1,rlen-2,cstart+1,clen-2,row,col,mat);

}

void print_ring ( int ring_len, int * ring ) {
    int k;
    printf("ring = ");
    for ( k=0; k<ring_len; ++k ) {
        printf("%d ",ring[k]);
    }
    printf("\n");
}

void get_ring ( int ring_len, int * ring,
                int rstart, int rlen, int cstart, int clen, 
                int ** mat, int s ) {
    int k, idx = 0;

    for ( k=0; k<clen; ++k ) {  /* Get first row */
        ring[idx++] = mat[rstart][cstart+k];
    }
    for ( k=1; k<rlen-1; ++k ) { /* Get last column */
        ring[idx++] = mat[rstart+k][cstart+clen-1];
    }
    for ( k=clen-1; k>=0; --k ) { /* Get bottom row */
        ring[idx++] = mat[rstart+rlen-1][cstart+k];
    }
    for ( k=rlen-2; k>0; --k ) { /* Get first column */
        ring[idx++] = mat[rstart+k][cstart];
    }
}

void shift_ring ( int ring_len, int * ring,
                  int rstart, int rlen, int cstart, int clen, 
                  int ** mat, int s ) {
    int k,idx=0;

    for ( k=0; k<clen; ++k ) { /* Get first row */
        mat[rstart][cstart+k] = ring[(idx+s) % ring_len];
        idx++;
    }
    for ( k=1; k<rlen-1; ++k ) { /* Get last column */
        mat[rstart+k][cstart+clen-1] = ring[(idx+s) % ring_len];
        idx++;
    }
    for ( k=clen-1; k>=0; --k ) { /* Get bottom row */
        mat[rstart+rlen-1][cstart+k] = ring[(idx+s) % ring_len];
        idx++;
    }
    for ( k=rlen-2; k>0; --k ) { /* Get first column */
        mat[rstart+k][cstart] = ring[(idx+s) % ring_len];
        idx++;
    }
}

void shift_rings ( int ring_level, int row, int col, int ** mat, int s ) {
    int rstart = ring_level * 1;
    int rlen   = row - ring_level * 2;
    int cstart = ring_level * 1;
    int clen   = col - ring_level * 2;
    int ring_len = 2*rlen + 2*(clen-2);
    int * ring = NULL;

    if ( rlen<=1 || clen<=1 ) {
        return;
    }

    ring = calloc(ring_len,sizeof(*ring));

    get_ring(ring_len,ring,rstart,rlen,cstart,clen,mat,s);
    shift_ring(ring_len,ring,rstart,rlen,cstart,clen,mat,s);

    /* Recurse to next ring */
    shift_rings(ring_level+1,row,col,mat,s);

    free(ring);
}

void matrixRotation (int matrix_rows, int matrix_columns, int** matrix, int r) {
    shift_rings(0,matrix_rows,matrix_columns,matrix,r);
    printf("[%d] Rotated %d:\n",__LINE__,r);
    print_matrix(matrix_rows,matrix_columns,matrix);
}

/* Iteratively counter clockwise each ring a prescribed number of times */
void shift ( int row, int col, int ** mat, int s ) {
    /* Too slow */
    for ( ; s>0 ; s-- ) {
        shift_1_rec(0,row,0,col,row,col,mat);
    }
    return;
}

void matrixRotation_dep (int matrix_rows, int matrix_columns, int** matrix, int r) {
    shift(matrix_rows,matrix_columns,matrix,r);
    printf("[%d] Rotated %d:\n",__LINE__,r);
    print_matrix(matrix_rows,matrix_columns,matrix);
}

/* For testing */
int ** create_matrix ( int row, int col ) {
    int ** mat = calloc(row,sizeof(*mat));
    int k, m, idx = 1;

    for ( k=0; k<row; ++k ) {
        mat[k] = calloc(col,sizeof(*mat[k]));
        for ( m=0; m<col; ++m ) {
            mat[k][m] = idx++;
        }
    }
    return mat;
}

/* For debugging */
void destroy ( int row, int col, int ** mat ) {
    int k;

    for ( k=0; k<row; ++k ) {
        free(mat[k]);
    }
    free(mat);
}

void test_1_2 ( int s ) {
    int row = 4;
    int col = 4;
    int ** matrix = create_matrix(4,4);

    print_matrix(row,col,matrix);
    matrixRotation(row,col,matrix,s);
    destroy(row,col,matrix);
}

int main ( int argc, char ** argv ) {
    int r = 4, c = 4, s = 1;
    int ** mat = NULL;

    if ( 4!=argc ) {
        printf("Usage: %s <row> <col> <rotation>\n",argv[0]);
        exit(1);
    }
    r = atoi(argv[1]);
    c = atoi(argv[2]);
    s = atoi(argv[3]);
    mat = create_matrix(r,c);
    printf("    Original Matrix:\n");
    print_matrix(r,c,mat);
    matrixRotation(r,c,mat,s);
    destroy(r,c,mat);

    return 0;
}

#if 0
/* Execution code on website */
int main()
{
    char** mnr = split_string(rtrim(readline()));

    char* m_endptr;
    char* m_str = mnr[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mnr[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* r_endptr;
    char* r_str = mnr[2];
    int r = strtol(r_str, &r_endptr, 10);

    if (r_endptr == r_str || *r_endptr != '\0') { exit(EXIT_FAILURE); }

    int** matrix = malloc(m * sizeof(int*));

    for (int i = 0; i < m; i++) {
        *(matrix + i) = malloc(n * (sizeof(int)));

        char** matrix_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < n; j++) {
            char* matrix_item_endptr;
            char* matrix_item_str = *(matrix_item_temp + j);
            int matrix_item = strtol(matrix_item_str, &matrix_item_endptr, 10);

            if (matrix_item_endptr == matrix_item_str || *matrix_item_endptr != '\0') { exit(EXIT_FAILURE); }

            *(*(matrix + i) + j) = matrix_item;
        }
    }

    int matrix_rows = m;
    int matrix_columns = n;

    matrixRotation(matrix_rows, matrix_columns, matrix, r);

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

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
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
#endif
