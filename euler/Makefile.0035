BIN=main
PROJ=p0027_quad_primes

CC=gcc

OBJ=primes.o prime_arrays.o
#OBJ=least_squares.o khm_common.o 

#CFLAGS=-I /Users/khmacdonald/code/common  -lm
#CFLAGS=-I /Users/khmacdonald/code/common  

$(PROJ): $(OBJ)
	$(CC) -g -o $(BIN) $(PROJ).c $(OBJ) $ $(CFLAGS)

clean: 
	rm $(PROJ) $(OBJ) $(BIN)

