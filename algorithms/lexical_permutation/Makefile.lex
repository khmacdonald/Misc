PROJ=lex_perm

CC=gcc

OBJ=../common/common.o

CFLAGS=-I ../common

.PHONY:$(PROJ)

$(PROJ): $(OBJ)
	$(CC) -g -o $(PROJ) $(PROJ).c $(OBJ) $ $(CFLAGS)

clean: 
	rm $(PROJ) $(OBJ)
