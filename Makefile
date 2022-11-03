# La siguiente no es necesariamente requerida, se agrega para
# mostrar como funciona.

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
CFLAGSEND = `pkg-config --libs gtk+-3.0`
SRC = hannoi.c Pila.c Pila.h
OBJ = hannoi.o Pila.o


# Reglas explicitas

all: $(OBJ)
	$(CC) $(CFLAGS) -o hannoi hannoi.c $(CFLAGSEND)
clean:
	$(RM) $(OBJ) main

# Reglas implicitas

Pila.o: Pila.c Pila.h
hannoi.o: hannoi.c Pila.h
