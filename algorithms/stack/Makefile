PROJ=main

COMMON=../../common
LLIST=../linked_lists

CC=gcc

OBJ=stack.o $(LLIST)/linked_list.o

CFLAGS=-I $(COMMON) -I $(LLIST)

.PHONY:$(PROJ)

$(PROJ): $(OBJ)
	$(CC) -g -o $(PROJ) $(PROJ).c $(OBJ) $ $(CFLAGS)

clean: 
	rm $(PROJ) $(OBJ)
