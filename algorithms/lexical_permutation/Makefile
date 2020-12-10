PROJ=lex_perm_test

CC=gcc

OBJ=../../common/common.o lex_perm.o

CFLAGS=-I ../../common

.PHONY:$(PROJ)

$(PROJ): $(OBJ)
	$(CC) -g -o $(PROJ) $(PROJ).c $(OBJ) $ $(CFLAGS)

clean: 
	rm $(PROJ) $(OBJ) $(PROJ)
