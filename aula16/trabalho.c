#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "../mleocomp.h"

double f(double x) {
	return exp(pow(-x, 2)) * sqrt(1 - pow(x, 2));
}

double s_error(double N) {
	double n = simpson(0, 1, N, &f);
	double n2 = simpson(0, 1, N - 2, &f);
	return fabs(n - n2) / n;
}

double t_error(double N) {
	double n = trapezio(0, 1, N, &f);
	double n2 = trapezio(0, 1, N - 2, &f);
	return fabs(n - n2) / n;
}

void writeFile(char* fileName, double** data) {
	FILE* file = fopen(fileName, "w");
	size_t size = sizeof(data) / sizeof(data[0]);
	for (int i = 0; i < size; i++) {
		fprintf(file, "%lf %lf\n", data[i][0], data[i][1]);
	}
	fclose(file);
}

int main(int argc, char const *argv[])
{
	double a;
	double b;
	double N;
	int method;
	char* outFile;

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
	
	if (method == 1) {
		fprintf(g, "set title 'Método de Simpson'\n");
	} else {
		fprintf(g, "set title 'Método do Trapézio'\n");
	}

	fprintf(g, "plot '-' title 'f(x)' with lines\n");

	double** data = (double**) malloc (sizeof(double*) * (N / 2));

	for (int i = 2; i <= N; i += 2) {
		int j = i - (i / 2) + 1;
		data[j] = (double*) malloc (sizeof(double) * 2);
		data[j][0] = i;
		if (method == 1) {
			data[j][1] = s_error(i);
		} else {
			data[j][1] = t_error(i);			
		}

		fprintf(g, "%lf %lf\n", data[j][0], data[j][1]);
	}

	fprintf(g, "e\n");

	writeFile(outFile, data);

	return 0;
}