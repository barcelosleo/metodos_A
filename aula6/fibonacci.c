#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void geraFibonacci(Fila *lista, double atual, double anterior, double max, double n) {
	if (atual == 0) {
		entraNaFila(lista, criaItem(0)); // adiciona zero na fila
		entraNaFila(lista, criaItem(1)); // adiciona 1 na fila
		entraNaFila(lista, criaItem(1)); // adiciona 1 na fila
		geraFibonacci(lista, 1, 1, max, n + 3);
	} else if (n  < max) {
		double valorGerado = atual + anterior;
		if (valorGerado < 0) {
			printf("%.0f + %.0f = %.0f \n", anterior, atual, valorGerado);
		}
		entraNaFila(lista, criaItem(valorGerado));
		geraFibonacci(lista, valorGerado, atual, max, n + 1);
	}
	return;
}

Fila* getFibonacci(double max) {
	Fila *lista = criaFila();
	geraFibonacci(lista, 0, 0, max, 0);
	return lista;
}

int main(int argc, char const *argv[]) {
	Fila *lista = getFibonacci(argc == 2 ? atof(argv[1]) : 10);
	mostraFila(lista);
}