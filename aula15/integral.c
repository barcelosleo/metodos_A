#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "../mleocomp.h"

#define PRECISION 20

double f(double x) {
	return exp(-pow(x, 2)) * sqrt(1 - pow(x, 2));
}

double f1(double x) {
	return x;
}

double f2(double x) {
	return pow(2, x);
}

double f3(double x) {
	return -2*x + 3;
}
double f4(double x) {
	return exp(-pow(x,2));
}

void main() {
	double a;
	double b;

	double N;

	int method;

	do {
		printf("Digite o intervalo de integração:\n");
		scanf("%lf %lf", &a, &b);

		if (a == b) {
			printf("Intervalo de integração Inválido! Tente outro.\n");
		}
	} while (a == b);

	do {
		printf("Digite o número de divisões do intervalo:\n");
		scanf("%lf", &N);

		if (N <= 0) {
			printf("Número de divisões inválido! Tente outro.\n");
		}
	} while (N <= 0);

	do {
		printf("Qual método deseja utilizar? [1] - Simpson [2] - Trapézio\n");
		scanf("%d", &method);
		
		if (method != 1 && method != 2) {
			printf("Método Inválido! Tente outro.\n");
		}
	} while (method != 1 && method != 2);

	double integral;

	if (method == 1) {
		BM* bm = startBenchmark("Tempo de processamento:");
		integral = simpson(a, b, N, &f);
		stopBenchmark(bm);
	} else {
		BM* bm = startBenchmark("Tempo de processamento:");
		integral = trapezio(a, b, N, &f);		
		stopBenchmark(bm);
	}

	printf("A integral é aproximadamente %.*lf\n", PRECISION, integral);
	printf("Intevalo: %lf -> %lf\n", a, b);
	printf("Número de Divisões: %lf\n", N);
}