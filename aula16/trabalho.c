#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "mleocomp.h"

double f(double x) {
	return exp(-pow(x, 2)) * sqrt(1 - pow(x, 2));
}

double* s_error(double N, double a, double b) {
	double* r = (double*) malloc(sizeof(double) * 3);
	double n = simpson(a, b, N, &f);
	double n2 = 1;
	r[2] = 1;
	if (N - 2 != 0) {
		n2 = simpson(0, 1, N - 2, &f);
		r[2] = fabs(n - n2) / n;
	}
	r[0] = N;
	r[1] = n;
	return r;
}

double* t_error(double N, double a, double b) {
	double* r = (double*) malloc(sizeof(double) * 3);
	double n = trapezio(a, b, N, &f);
	double n2 = 1;
	r[2] = 1; // erro
	if (N - 2 != 0) {
		n2 = trapezio(0, 1, N - 2, &f);
		r[2] = fabs(n - n2) / n;
	}
	r[0] = N;
	r[1] = n; // valor da integral
	return r;
}

void writeFile(char* fileName, double** data, int N) {
	FILE* file = fopen(fileName, "w");
	for (int i = 0; i < N; i++) {
		fprintf(file, "%lf %lf %lf\n", data[i][0], data[i][1], data[i][2]);
	}
	fclose(file);
}

int main(int argc, char const *argv[])
{
	double a;
	double b;
	double N;
	int method;
	char outFile[100];

	do {
		printf("Qual método deseja utilizar? [1] - Simpson [2] - Trapézio\n");
		scanf("%d", &method);

		if (method != 1 && method != 2) {
			printf("Método Inválido! Tente outro.\n");
		}
	} while (method != 1 && method != 2);

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

	printf("Digite o nome do arquivo de saída:\n");
	scanf("%s", outFile);

	GnuPipe g = initializeGnuPipe();

	fprintf(g, "set grid\n");
	fprintf(g, "set zeroaxis\n");
	fprintf(g, "set ylabel 'Erro'\n");
	fprintf(g, "set xlabel 'N'\n");
	fprintf(g, "set log\n");

	if (method == 1) {
		fprintf(g, "set multiplot layout 2,1 title 'Método de Simpson'\n");
	} else {
		fprintf(g, "set multiplot layout 2,1 title 'Método do Trapézio'\n");
	}

	if (method == 1) {
		fprintf(g, "plot '-' title 'Erro Simpson' with lines, '-' title 'Erro Trapézio' with lines\n");
	} else {
		fprintf(g, "plot '-' title 'Erro Trapézio' with lines, '-' title 'Erro Simpson' with lines\n");
	}

	double** data = (double**) malloc (sizeof(double*) * (N / 2));

	int j = 0;

	for (int i = 2; i <= (N + 4); i += 2) {
		j = (i / 2) - 1;
		data[j] = (double*) malloc (sizeof(double) * 3);
		if (method == 1) {
			data[j] = s_error(i, a, b);
		} else {
			data[j] = t_error(i, a, b);
		}

		fprintf(g, "%lf %lf\n", data[j][0], data[j][2]);
	}

	fprintf(g, "e\n");

	writeFile(outFile, data, --j);

	j = 0;

	double** comparsion_data = (double**) malloc (sizeof(double*) * (N / 2));

	for (int i = 2; i <= (N + 4); i += 2) {
		j = (i / 2) - 1;
		comparsion_data[j] = (double*) malloc (sizeof(double) * 3);
		if (method == 1) {
			comparsion_data[j] = t_error(i, a, b);
		} else {
			comparsion_data[j] = s_error(i, a, b);
		}

		fprintf(g, "%lf %lf\n", comparsion_data[j][0], comparsion_data[j][2]);
	}

	fprintf(g, "e\n");

	fprintf(g, "unset log\n");
	fprintf(g, "set ylabel 'Integral'\n");
	fprintf(g, "plot '-' with lines title 'Valor da Integral'\n");

	for (int i = 0; i < (N / 2); i++) {
		fprintf(g, "%lf %lf\n", data[i][0], data[i][1]);
	}

	fprintf(g, "e\n");

	free(data);
	free(comparsion_data);

	return 0;
}