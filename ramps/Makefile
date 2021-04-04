PROJ=main

CC=gcc

OBJ=ramp.o unit_test.o

.PHONY=$(PROJ) $(OBJ)

$(PROJ): $(OBJ)
	$(CC) -g -o $(PROJ) $(PROJ).c $(OBJ)

.PHONY=clean
clean: 
	rm $(PROJ) $(OBJ)
