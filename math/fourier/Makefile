PROJ=lsmain

CC=gcc

OBJ=common.o 
#OBJ=least_squares.o khm_common.o 

CFLAGS=-I /Users/khmacdonald/code/common  -lm

#	$(CC) -g -o $(PROJ) $(PROJ).c $(OBJ) $ $(CFLAGS)
$(PROJ): $(OBJ)
	$(CC) -c src/fourier.c -I include

clean: 
	rm $(PROJ) $(OBJ)

