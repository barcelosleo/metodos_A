#include "mleocomp.h"

BM* startBenchmark(char* name) {
	BM* bm = (BM*) malloc (sizeof(BM));
	bm->name = name;
	bm->c0 = clock();
}

void stopBenchmark(BM* bm) {
	clock_t c1 = clock();
	double time_diff_ms = (c1 - bm->c0) * 1000. / CLOCKS_PER_SEC;
	printf("\"%s\": %lf ms\n", bm->name, time_diff_ms);
}

// INTEGRAÇÃO

double somatorio(double a, int N, double dx, double step, int firstElement, double (*function)(double)) {
	double Xi = 0;
	double sum = 0;
	for (int i = firstElement; i < N; i += step) {
		Xi = a + (i * dx);
		sum += (*function)(Xi);
	}
	return sum;
}

double simpson(double a, double b, int N, double (*function)(double)) {
	if (N <= 0) {
		printf("Valor inválido para o número de divisões");
		exit(0);
	}
	double h = (b - a) / N;
	double somatorioPares = somatorio(a, N, h, 2, 0, function);
	double somatorioImpares = somatorio(a, N, h, 2, 1, function);
	return (h / 3) * ((*function)(a) +  (2 * somatorioPares) + (4 * somatorioImpares) + (*function)(b));
}

double trapezio(double a, double b, int N, double (*function)(double)) {
	if (N <= 0) {
		printf("Valor inválido para o número de divisões");
		exit(0);
	}
	double dx = (b - a) / N;
	return ((((*function)(a) + (*function)(b)) / 2) + somatorio(a, N, dx, 1, 0, function)) * dx;
}

// PLOT WITH GNUPLOT

GnuPipe initializeGnuPipe() {
	return popen("gnuplot -persistent", "w");
}

void plotData(GnuPipe gnuPipe, double initialValue, double finalValue, double step, double (*function)(double)) {
	fprintf(gnuPipe, "set zeroaxis\n");
    fprintf(gnuPipe, "set grid\n");
    fprintf(gnuPipe, "set xrange[%lf:%lf]\n", initialValue, finalValue);
    fprintf(gnuPipe, "set title 'Método de Neville'\n");
    fprintf(gnuPipe, "plot '-' title 'f(x)' with lines\n");
	for(double i = initialValue; i < finalValue; i += step) {
		fprintf(gnuPipe, "%lf %lf\n", i, (*function)(i));
	}
	fprintf(gnuPipe, "e\n");
}

void gnuPlotCommand(GnuPipe gnu, char* command) {
	fprintf(gnu, "%s\n", command);
}