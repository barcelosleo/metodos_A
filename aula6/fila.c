#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila* criaFila() {
	Fila *fila = (Fila*) malloc (sizeof(Fila));
	fila->inicio = NULL;
	fila->fim = NULL;
}

Item* criaItem(double valor) {
	Item *item = (Item*) malloc (sizeof(Item));
	item->valor = valor;
	item->prox = NULL;
	return item;
}

void entraNaFila(Fila *fila, Item *item) {
	if (fila->inicio == NULL && fila->fim == NULL) {
		fila->inicio = item;
		fila->fim = item;
	} else {
		fila->fim->prox = item;
		fila->fim = item;
	}
}

void mostraFila(Fila *fila) {
	Item *aux = fila->inicio;

	while(aux) {
		printf("%.0f\n", aux->valor);
		aux = aux->prox;
	}
}