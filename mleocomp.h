#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>

#define MAX_INTERATIONS 50000

typedef struct Point_ {
	double x;
	double y;
} Point;

typedef struct PointList_ {
	int size;
	Point* points;
} PointList;

typedef struct BM_ {
	char* name;
	clock_t c0;
} BM;

BM* startBenchmark(char* name);
void stopBenchmark(BM* bm);

PointList* createPointList(int size);
PointList* readPointsFromFile(char* fileName, int size);
void savePointsToFile(char* fileName, PointList* points);

// INTEGRAÇÃO

double somatorio(double a, int N, double dx, double step, int firstElement, double (*function)(double));
double simpson(double a, double b, int N, double (*function)(double));
double trapezio(double a, double b, int N, double (*function)(double));

double somatorioVetorizado(double** points);

// PLOTING WITH GNUPLOT

typedef FILE* GnuPipe;
GnuPipe initializeGnuPipe();
void plotData(GnuPipe gnuPipe, double initialValue, double finalValue, double step, double (*function)(double));
void gnuPlotCommand(GnuPipe gnu, char* command);

// INTERPOLAÇÃO

double laGrange(double x, double** data, int numberOfPoints);
double getAij(double** points, int i, int j, double x, int n);
double neville(double x, int n, double** points);

// ZERO DE FUNÇÕES

double newtonRaphson(double x0, int p, double (*function)(double), double (*derivative)(double));
double interacaoSimples(double x0, int p, double (*function)(double));
double bisseccao(double min, double max, int p, double (*function)(double));

double df_direita(double x, double h, double (*function)(double));
double df_centrada(double x, double h, double (*function)(double));

// MATRIZES

typedef struct Matrix_ {
	double** data;
	int lines;
	int columns;
} Matrix;

Matrix* createMatrix(int lines, int columns);
Matrix* getSubMatrix(Matrix* original, int currentLine, int currentColumn);
void printMatrix(Matrix* matrix);
double getDeterminant(Matrix* matrix);
Matrix* getTranposedMatrix(Matrix* matrix);
Matrix* getCofactorMatrix(Matrix* matrix);
Matrix* multiplyMatrixByNumber(Matrix* matrix, double n);
Matrix* multiplyMatrixByMatrix(Matrix* m1, Matrix* m2);
Matrix* getInverse(Matrix* matrix);

// FITTING

double pointSumX(int p, int N, double** points, double (*function)(double, double));
double pointSumYX(int p, int N, double** points, double (*function)(double, double));
Matrix* getCoefficientMatrix(double** points, int polynomialDegree, int N);
Matrix* getIndependentTermsMatrix(double** points, int polynomialDegree, int N);
Matrix* getIncognitoMatrix(double** points, int polynomialDegree, int N);
