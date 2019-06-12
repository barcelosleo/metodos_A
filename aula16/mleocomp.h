#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct BM_ {
	char* name;
	clock_t c0;
} BM;

BM* startBenchmark(char* name);
void stopBenchmark(BM* bm);

// INTEGRAÇÃO

double somatorio(double a, int N, double dx, double step, int firstElement, double (*function)(double));
double simpson(double a, double b, int N, double (*function)(double));
double trapezio(double a, double b, int N, double (*function)(double));

// PLOTING WITH GNUPLOT

typedef FILE* GnuPipe;
GnuPipe initializeGnuPipe();
void plotData(GnuPipe gnuPipe, double initialValue, double finalValue, double step, double (*function)(double));
void gnuPlotCommand(GnuPipe gnu, char* command);