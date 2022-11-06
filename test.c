
#include <stdio.h>
#include <stdlib.h>
 
 
struct DISCO
{
 int ancho; // Contendrá el ancho, en intervalos impares, del disco.
 int altura; // Contiene el nivel en el que se encuentra ese disco.
};
 
struct NODO
{
 struct DISCO disc;
 struct NODO *puntero;
};
 
 
 
// FUNCIÓN QUE INTRODUCE UN NUMERO EN UNA PILA:
void insertaDatoEnLaPila( struct NODO **pila, int disco )
{
 /*
 Precondición:
 Se ha de recibir un doble puntero de tipo struct NODO para una pila, y un parámetro de tipo entero.
 Poscondición:
 Se introduce el número recibido en la pila.
 */
 
 
 // Se crea un puntero y se le asigna la dirección a la memoria necesaria para un nodo:
 struct NODO *temp = (struct NODO *) malloc(sizeof(struct NODO));
 
 
 // Si la pila no tiene nodos (NULL) la altura del disco que se va a introducir sera siempre de 1. Sin embargo si ya tiene nodos, la altura sera igual a la del nodo inferior +1.
 if( *pila == NULL )
 temp->disc.altura = 1;
 else
 temp->disc.altura = (*pila)->disc.altura + 1;
 
 temp->disc.ancho = disco;
 temp->puntero = *pila;
 *pila = temp;
 
};
 
 
 
// FUNCIÓN QUE EXTRAE EL PRIMER ELEMENTO DE LA PILA Y BORRA EL NODO VACIO:
int extraeDatoDeLaPila( struct NODO **pila, int *numNivel )
{
 /*
 Precondición:
 Se ha de recibir un doble puntero de tipo struct NODO para una pila.
 También un parámetro por referencia de tipo entero en el cual se guardara la altura en el que se encuentra el disco.
 Ese dato en el caso de la función mueveDisco() no sirve para nada, sin embargo es necesario desde la función imprimeTablero();
 Si la pila resultase NULL se devolverá, o mejor dicho, no se modificara el valor original que debería de ser 0.
 Poscondición:
 Se devuelve el primer parámetro de tipo entero almacenado en la pila, si esta vacía devuelve un 0.
 Devuelve por referencia la altura del disco.
 */
 
 
 struct NODO *siguiente;
 int resp;
 
 if( *pila == NULL )
 resp = 0;
 else
 {
 // Se copia el ancho a la variable que va a ser retornada por la función:
 *numNivel = (*pila)->disc.altura;
 resp = (*pila)->disc.ancho;
 
 
 // Se elimina el primer Nodo (el vaciado):
 siguiente = (*pila)->puntero;
 free(*pila);
 *pila = siguiente;
 };
 
 return resp;
};
 
 
 
// FUNCIÓN QUE CREA UNA COPIA IDENTICA DE UNA PILA:
void creaUnaCopiaDePila( struct NODO **pila, struct NODO **pilaCopia )
{
 /*
 Precondición:
 Se reciben dos dobles punteros a dos pilas de tipo struct NODO, la primera ha de tener nodos y la segunda ha de estar vacía.
 Poscondición:
 Se realiza una copia exacta de toda la pila de la original a la copia.
 */
 
 
 struct NODO *siguiente = *pila;
 struct NODO *antBusq;
 struct NODO *sigBusq;
 struct NODO *temp;
 
 // Mientras el puntero siguiente siga apuntando a otro Nodo...
 while( siguiente != NULL )
 {
 
 temp = (struct NODO *) malloc(sizeof(struct NODO));
 
 
 // Si la pila nueva no tiene ningún Nodo se introduce al principio:
 if( *pilaCopia == NULL )
 {
 temp->disc = siguiente->disc;
 temp->puntero = NULL;
 *pilaCopia = temp;
 }
   // En caso contrario se introducen los siguientes Nodos siempre al final de la pila (que se esta tratando como una cola).
 else
 {
 sigBusq = *pilaCopia;
 
 // Se busca el ultimo Nodo:
 while( sigBusq != NULL )
 {
 antBusq = sigBusq;
 sigBusq = sigBusq->puntero;
 };
 
 
 temp->disc = siguiente->disc;
 temp->puntero = NULL;
 antBusq->puntero = temp;
 };
 
 
 // Se avanza una posición en el puntero de la lista original:
 siguiente = siguiente->puntero;
 };
 
};
 
 
 
// FUNCIÓN QUE BORRA UNA LISTA ENTERA:
void borrarLista( struct NODO **lista )
{
 /*
 Precondición:
 Se ha de recibir un puntero de tipo struct NODO al primer nodo de la lista.
 Poscondición:
 Se borran todos los nodos de esa lista hasta llegar a NULL.
 */
 
 
 struct NODO *actual, *siguiente;
 actual = *lista;
 
 while(actual != NULL)
 {
 siguiente = actual->puntero;
 free(actual);
 actual = siguiente;
 };
 
 *lista = NULL;
 
};
 
 
 
// FUNCIÓN QUE IMPRIME EL TABLERO DE HANOI:
void imprimeTablero( struct NODO **pilaO, struct NODO **pilaA, struct NODO **pilaD, int totDiscos, int tamDiscGrande )
{
 /*
 Precondición:
 pilaO, pilaA, pilaD			Se reciben tres dobles punteros a tres pilas de tipo struct NODO.
 totDiscos					Parámetro de tipo entero que indica el numero de discos totales para calcular el tiempo de pausa por cada impresión.
 tamDiscGrande				Parámetro de tipo entero que indica el tamaño del disco mas grande, se emplea para calcular los espacios a imprimir a ambos lados del disco.
*/
 
 
 // Se crean tres punteros temporales:
 struct NODO *pilaOc=NULL, *pilaAc=NULL, *pilaDc=NULL;
 
 int discoO, discoA, discoD, nivelO=0, nivelA=0, nivelD=0;
 int espO, espA, espD;
 int numNivel;
 int i;
 
 
 // Se usan los punteros temporales para que apunten a unas nuevas pilas idénticas a las originales:
 creaUnaCopiaDePila( pilaO, &pilaOc );
 creaUnaCopiaDePila( pilaA, &pilaAc );
 creaUnaCopiaDePila( pilaD, &pilaDc );
 
 
 // Se obtiene el numero de disco por return y la altura del disco por referencia...
 discoO = extraeDatoDeLaPila(&pilaOc, &nivelO);
 discoA = extraeDatoDeLaPila(&pilaAc, &nivelA);
 discoD = extraeDatoDeLaPila(&pilaDc, &nivelD);
 
 
 // Se recorren todos los niveles de las pilas aunque estén vacíos:
 for( numNivel=totDiscos; numNivel > 0; numNivel-- )
 {
 
 // Se calculan los espacios necesarios para el disco a imprimir en la altura correspondiente:
 espO = ( tamDiscGrande - discoO )/2;
 espA = ( tamDiscGrande - discoA )/2;
 espD = ( tamDiscGrande - discoD )/2;
 
 
 // Si la altura en la que se esta, la marca el for, es la misma que la altura del disco que se ha leído... se imprime, en caso contrario se imprimen tantos espacios como ancho tenga el disco mas grande.
 // Torre 1 o Origen:
 if( nivelO == numNivel )
 {
 // Espacios a la izquierda
 for( i=0; i < espO; i++ )
 printf( " " );
 // Imprime los comodines
 for( i=0; i < discoO; i++ )
 printf( "*" );
 // Espacios a la derecha
 for( i=0; i < espO; i++ )
 printf( " " );
 
 // Se recoge el siguiente disco:
 discoO = extraeDatoDeLaPila(&pilaOc, &nivelO);
 }
 else
 {
 // Se rellena todo de espacios ya que no hay disco en ese altura:
 for( i=0; i < tamDiscGrande; i++ )
 printf( " " );
 };
 
 
 printf( "  " );
 
 
 // Torre 1 o Auxiliar:
 if( nivelA == numNivel )
 {
 // Espacios a la izquierda
 for( i=0; i < espA; i++ )
 printf( " " );
 // Imprime los comodines
 for( i=0; i < discoA; i++ )
 printf( "*" );
 // Espacios a la derecha
 for( i=0; i < espA; i++ )
 printf( " " );
 
 discoA = extraeDatoDeLaPila(&pilaAc, &nivelA);
 }
 else
 {
 // Se rellena todo de espacios ya que no hay disco en ese altura:
 for( i=0; i < tamDiscGrande; i++ )
 printf( " " );
 };
 
 
 printf( "  " );
 
 
 // Torre 1 o Destino:
 if( nivelD == numNivel )
 {
 // Espacios a la izquierda
 for( i=0; i < espD; i++ )
 printf( " " );
 // Imprime los comodines
 for( i=0; i < discoD; i++ )
 printf( "*" );
 // Espacios a la derecha
 for( i=0; i < espD; i++ )
 printf( " " );
 
 discoD = extraeDatoDeLaPila(&pilaDc, &nivelD);
 }
 else
 {
 // Se rellena todo de espacios ya que no hay disco en ese altura:
 for( i=0; i < tamDiscGrande; i++ )
 printf( " " );
 };
 
 
 // Se hace un salto de linea para representar la próxima altura:
 printf( "\n" );
 
 };
 
};
 
 
 
// FUNCIÓN QUE MUEVE UN DISCO DE UNA PILA A OTRA:
void mueveDisco( struct NODO **pilaO, struct NODO **pilaA, struct NODO **pilaD, int totDiscos, int tamDiscGrande, char listOrigen, char listDestino )
{
 /*
 Precondición:
 pilaO, pilaA, pilaD			Se reciben tres dobles punteros a tres pilas de tipo struct NODO.
 totDiscos					Parámetro de tipo entero que indica el numero de discos totales para calcular el tiempo de pausa por cada impresión.
 tamDiscGrande				Parámetro de tipo entero que indica el tamaño del disco mas grande, se emplea para calcular los espacios a imprimir a ambos lados del disco.
 listOrigen, listDestino		Dos enteros que indican el origen del disco y su destino.
 Poscondición:
 Se mueve el disco de Origen a Destino y se llama a la función que imprime el tablero.
 */
 
 
 int paraNada=0;
 
 
 if( listOrigen == 'O' )
 {
 if( listDestino == 'A' )
 insertaDatoEnLaPila( pilaA, extraeDatoDeLaPila(pilaO, &paraNada) );
 
 else if( listDestino == 'D' )
 insertaDatoEnLaPila( pilaD, extraeDatoDeLaPila(pilaO, &paraNada) );
 }
 else if( listOrigen == 'A' )
 {
 if( listDestino == 'O' )
 insertaDatoEnLaPila( pilaO, extraeDatoDeLaPila(pilaA, &paraNada) );
 
 else if( listDestino == 'D' )
 insertaDatoEnLaPila( pilaD, extraeDatoDeLaPila(pilaA, &paraNada) );
 }
 else if( listOrigen == 'D' )
 {
 if( listDestino == 'O' )
 insertaDatoEnLaPila( pilaO, extraeDatoDeLaPila(pilaD, &paraNada) );
 
 else if( listDestino == 'A' )
 insertaDatoEnLaPila( pilaA, extraeDatoDeLaPila(pilaD, &paraNada) );
 };
 
 
 // Se imprime el tablero:
 imprimeTablero( pilaO, pilaA, pilaD, totDiscos, tamDiscGrande );
};
 
 
 
// FUNCIÓN DE HANOI MEDIANTE RECURSIVIDAD:
void hanoi( struct NODO **pilaO, struct NODO **pilaA, struct NODO **pilaD, int nDiscos, int totDiscos, int tamDiscGrande, char O, char A, char D )
{
/*
Precondición:
 pilaO, pilaA, pilaD		Se reciben tres dobles punteros a tres pilas de tipo struct NODO.
 nDiscos					Parámetro de tipo entero que indica el numero de discos usados en cada recursividad.
 totDiscos				Parámetro de tipo entero que indica el numero de discos totales para calcular el tiempo de pausa por cada impresión.
 tamDiscGrande			Parámetro de tipo entero que indica el tamaño del disco mas grande, se emplea para calcular los espacios a imprimir a ambos lados del disco.
 O, A, D					Tres enteros que indican la fila desde donde se ha de coger el disco y a donde se ha de traspasar. La primera vez que se llama a hanoi tienen los valores de: 0 ,1 y 2 respectivamente.
Poscondición:
 Se llama recursivamente a hanoi hasta resolver el tablero.
*/
 
 
 if( nDiscos == 1 )
 {
 // Se borra la pantalla, se mueve el disco/imprime y se hace una pausa que varia dependiendo del numero de discos:
 system("clear");
 mueveDisco( pilaO, pilaA, pilaD, totDiscos, tamDiscGrande, O, D );
 if(totDiscos<=5) system("sleep 0.8"); else if(totDiscos<=10) system("sleep 0.3"); else if(totDiscos<=15) system("sleep 0.06"); else if(totDiscos>15) system("sleep 0.02");
 }
 else
 {
 hanoi( pilaO, pilaA, pilaD, nDiscos-1, totDiscos, tamDiscGrande, O, D, A );
 
 system("clear");
 mueveDisco( pilaO, pilaA, pilaD, totDiscos, tamDiscGrande, O, D );
 if(totDiscos<=5) system("sleep 0.8"); else if(totDiscos<=10) system("sleep 0.3"); else if(totDiscos<=15) system("sleep 0.06"); else if(totDiscos>15) system("sleep 0.02");
 
 hanoi( pilaO, pilaA, pilaD, nDiscos-1, totDiscos, tamDiscGrande, A, O, D );
 };
 
};
 
 
 
void main() {
 
 struct NODO *pilaO=NULL, *pilaA=NULL, *pilaD=NULL;
 int nDiscos, disco, tamDiscGrande, i;
 
 
 printf( "Indique el número de discos: " );
 scanf( "%i", &nDiscos );
 
 
 // Se halla el disco más grande (de tamaño impar) que se usara:
 disco = 1 + 2*(nDiscos - 1);
 tamDiscGrande = disco; // Se hace una copia para poder conservar el numero.
 
 
 for( i=0; i < nDiscos; i++ )
 {
 // Se introduce el disco que corresponda y se resta 2 para la siguiente iteración:
 insertaDatoEnLaPila( &pilaO, disco );
 disco -= 2;
 };
 
 
 // Se imprime el tablero:
 system("clear");
 imprimeTablero( &pilaO, &pilaA, &pilaD, nDiscos, tamDiscGrande );
 system("sleep 1");
 
 
 // Se llama a hanoi para comenzar "la partida":
 hanoi( &pilaO, &pilaA, &pilaD, nDiscos, nDiscos, tamDiscGrande, 'O', 'A', 'D' );
 
 
 // Se borran la pila de destino que es la única que tiene nodos:
 borrarLista( &pilaD );
 
};