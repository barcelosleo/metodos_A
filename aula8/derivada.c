#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x) {
	// return (sin(pow(x, 2)) * exp(x / 3)) / sqrt(pow(x, 2) + 4);
	return sin(x) * pow(x, 3);
}

double df_direita(double x, double h) {
	return (f(x + h) - f(x)) / h;
}

double df_centrada(double x, double h) {
	return ((f(x + h) - f(x - h)) / (2 * h));
}

int main() {
	FILE* arquivo = fopen("derivadas.dat", "w");
	double x = 6;
	double h;
	for (double i = -10; i <= 1; i += 0.2) {
		h = pow(10, i);
		fprintf(arquivo, "%1.1E %lf %lf\n", h, df_direita(x, h), df_centrada(x, h));
	}
	fclose(arquivo);
}