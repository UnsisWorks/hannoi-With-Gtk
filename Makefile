# La siguiente no es necesariamente requerida, se agrega para
# mostrar como funciona.

CC = gcc
CFLAGS = -g -Wall
SRC = Proyecto.c Pila.c Pila.h
OBJ = Proyecto.o Pila.o


# Reglas explicitas

all: $(OBJ)
	$(CC) $(CFLAGS) -o Proyecto $(OBJ)
clean:
	$(RM) $(OBJ) main

# Reglas implicitas

Pila.o: Pila.c Pila.h
Proyecto.o: Proyecto.c Pila.h
