/*
 * Pila.c
 * Por: Dr. V�ctor Alberto G�mez P�rez
 * Universidad de la Sierra Sur
 */

#include <stdio.h>
#include "Pila.h"

void PilaVacia (Pila *a) {
     a->tope=-1;
}
     
int EsVacia (Pila *a) {
     if (a -> tope == -1)
          return 1;
     else
          return 0;  
}
     
int Cima (Pila *a) {
     if (!EsVacia(a))
         return a->arreglo[a->tope];
     else{
          printf("Error de subdesbordamiento UNDERFLOW\n");
          return -9999;
     }
}


void Push (int x, Pila *a) { 
     if (!EsLlena(a)) {
          a -> tope++;
          a -> arreglo[a->tope] = x; 
     }
      else
          printf("Error de desbordamiento OVERFLOW\n");
     }
     
int Pop (Pila *a) {
     int aux;
     if (EsVacia(a)) {
         printf("Error de subdesbordamiento UNDERFLOW\n");
         return -9999;
     }
     else {
          aux = a -> arreglo[a->tope];
          a -> tope--;
          return aux;
     }    
}

int EsLlena (Pila *a) {
       if (a -> tope == MAX -1)        
          return 1;
       else
           return 0;  
}
