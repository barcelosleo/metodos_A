#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long double f(long double x) {
	// return (sin(pow(x, 2)) * exp(x / 3)) / sqrt(pow(x, 2) + 4);
	return sin(x) * pow(x, 3);
}

long double df_direita(long double x, long double h) {
	return (f(x + h) - f(x)) / h;
}

long double df_centrada(long double x, long double h) {
	return ((f(x + h) - f(x - h)) / (2 * h));
}

long double df_exata(long double x) {
	return (pow(x, 2) * (3 * sin(x) + (x * cos(x))));
}

int main() {
	FILE* erros = fopen("erros.dat", "w");
	long double x = 6;
	long double h;
	for (long double i = -5; i <= 1; i += 0.2) {
		h = pow(10, i);
		long double erro_central, erro_direita;
		erro_central = pow(h, 2);
		erro_direita = h;
		fprintf(erros, "%1.20Lf %1.20Lf %1.20Lf %1.20Lf\n", h, df_centrada(x, h), df_exata(x), df_direita(x, h));
	}
	fclose(erros);
}