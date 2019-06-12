#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mleocomp.h"

double f1(double x) {
	return sin(x) * pow(x, 3);
}

double f(double x) {
        return (sin(x) / (pow(x, 2) + 1)) + 0.2 - (0.01 * pow(x, 2));
}

double df(double x) {
        return (-0.02 * x) + (cos(x) / (pow(x, 2) + 1)) - ((2 * x * sin(x)) / pow((pow(x, 2) + 1), 2));
}



int main() {
	printf("Derivada em 6 centrada com erro 10^-5(177.21990810422026611792): %.20lf\n", df_centrada(6, 0.00001, &f1));
	printf("Derivada em 6 a direita com erro 10^-5(177.22119656156108617739): %.20lf\n", df_direita(6, 0.00001, &f1));

	printf("Newton Raphson(-0.2098883328): %.10lf\n", newtonRaphson(0, 10, &f, &df));
	printf("Bissecção(3.9541696473): %.10lf\n", bisseccao(0, 10, 10, &f));
	printf("Interação Simples(3.9541696464): %.10lf\n", interacaoSimples(0, 10, &f));
	return 0;
}