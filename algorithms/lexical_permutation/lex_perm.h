#ifndef LEX_PERM_H
#define LEX_PERM_H

typedef enum { NEXT_PERMUTATION, LAST_PERMUTATION } perm_t;

unsigned int lex_factorial(unsigned int n);
perm_t next_lex_perm(int n, int * a);

#endif
