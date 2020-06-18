PROJ=main

MY_COMMON=../../../common
ALGOS_COMMON=../common

CC=gcc

OBJ=graph.o ../common/queue.o algos_common.o

CFLAGS=-g -I . -I $(ALGOS_COMMON) -I $(MY_COMMON)

.PHONY:$(PROJ)

$(PROJ): $(OBJ)
	$(CC) -g -o $(PROJ) $(PROJ).c $(OBJ) $ $(CFLAGS)

clean: 
	rm $(PROJ) $(OBJ) *.o
