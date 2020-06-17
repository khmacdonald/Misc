PROJ=algos_main

CC=gcc

OBJ=ch05_graphs.o utils/queue.o algos_common.o

CFLAGS=-g -I . -I ./utils/

.PHONY:$(PROJ)

$(PROJ): $(OBJ)
	$(CC) -g -o $(PROJ) $(PROJ).c $(OBJ) $ $(CFLAGS)

clean: 
	rm $(PROJ) $(OBJ) *.o
