
CC = gcc
CFLAGS = -g -Wall
CFLAGS2 = 'pkg-config --cflags gtk+-3.0'
CFLAGS3 = 'pkg-config --libs gtk+-3.0´ 
SRC = hannoi.c Pila.c Pila.h
OBJ = hannoi.c


# Reglas explicitas

all: $(OBJ)
	$(CC) $(CFLAGS) -o hannoi $(OBJ)
clean:
	$(RM) $(OBJ) main

# Reglas implicitas

Pila.o: Pila.c Pila.h
Proyecto.o: hannoi.c Pila.h
#// Compiler gcc `pkg-config --cflags gtk+-3.0` -o hannoi hannoi.c `pkg-config --libs gtk+-3.0`
