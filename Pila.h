/*
 * Pila.h
 * Por: Dr. V�ctor Alberto G�mez P�rez
 * Universidad de la Sierra Sur
 */
#include <stdio.h>
#include <gtk/gtk.h>

#define MAXI 8
typedef struct {
    int arreglo[MAXI];
    int tope;
} Pila;

void PilaVacia (Pila *a);
int EsVacia (Pila *a);
int Cima (Pila *a);
void Push (int x, Pila *a);
int Pop (Pila *a); 
int EsLlena(Pila *a);
