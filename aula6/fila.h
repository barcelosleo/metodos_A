#include <stdio.h>
#include <stdlib.h>

typedef struct Item_ {
	struct Item_ *prox;
	double valor;
} Item;

typedef struct Fila_ {
	Item *inicio;
	Item *fim;
} Fila;

Fila* criaFila();
Item* criaItem(double valor);
void entraNaFila(Fila *fila, Item *item);
void mostraFila(Fila *fila);