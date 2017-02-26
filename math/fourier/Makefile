PROJ=main

CC=gcc

OBJ=src/common.o src/fourier.o

CFLAGS=-I include

$(PROJ): $(OBJ)
	$(CC) -g -o bin/$(PROJ) main/$(PROJ).c $(OBJ) $ $(CFLAGS)

clean: 
	rm $(PROJ) $(OBJ)

