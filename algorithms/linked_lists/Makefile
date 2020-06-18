PROJ=main

COMMON=../../common

CC=gcc

OBJ=linked_list.o

CFLAGS=-I $(COMMON)

.PHONY:$(PROJ)

$(PROJ): $(OBJ)
	$(CC) -g -o $(PROJ) $(PROJ).c $(OBJ) $ $(CFLAGS)

clean: 
	rm $(PROJ) $(OBJ)
