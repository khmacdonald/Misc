PROJ=lsmain

CC=gcc

OBJ=brand.o least_squares.o khm_common.o 
#OBJ=least_squares.o khm_common.o 

CFLAGS=-I /Users/khmacdonald/code/common  -lm

$(PROJ): $(OBJ)
	$(CC) -g -o $(PROJ) $(PROJ).c $(OBJ) $ $(CFLAGS)

clean: 
	rm $(PROJ) $(OBJ)

