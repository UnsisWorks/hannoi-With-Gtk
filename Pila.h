/*
 * Pila.h
 * Por: Dr. V�ctor Alberto G�mez P�rez
 * Universidad de la Sierra Sur
 */
#include <stdio.h>
#define MAX 10


typedef struct {
    int arreglo[MAX];
    int tope;
} Pila;

void PilaVacia (Pila *a);
int EsVacia (Pila *a);
int Cima (Pila *a);
void Push (int x, Pila *a);
int Pop (Pila *a); 
int EsLlena(Pila *a);
