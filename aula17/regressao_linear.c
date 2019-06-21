#include <stdlib.h>
#include <stdio.h>

#include "../mleocomp.h"

double** getPoints(char* fileName, int numberOfPoints) {
    FILE* dataFile = fopen(fileName, "r");
    double** data = (double**) malloc (sizeof(double*) * numberOfPoints);
    for (int i = 0; i < numberOfPoints; i++) {
        data[i] = (double*) malloc (sizeof(double) * 2);
        fscanf(dataFile, "%lf %lf", &data[i][0], &data[i][1]);
    }
    fclose(dataFile);
    return data;
}

int main() {
    char fileName[100];
    int numberOfPoints = 0, degree = 0;
    printf("Digite o nome do arquivo onde estão os pontos:\n");
    scanf("%s", fileName);
    printf("Digite o número de pontos:\n");
    scanf("%d", &numberOfPoints);
    printf("Digite o grau do polinômio:\n");
    scanf("%d", &degree);

    double** points = getPoints(fileName, numberOfPoints);

    BM* b = startBenchmark("Tempo de Execução da Regressão Linear");
    Matrix* incognito = getIncognitoMatrix(points, degree, numberOfPoints);
    stopBenchmark(b);
    printf("Os coeficientes são:\n");
    for(int i = 0; i < incognito->lines; i++) {
        printf("α%d = %lf\n", i, incognito->data[i][0]);
    }

    GnuPipe g = initializeGnuPipe();

	fprintf(g, "set grid\n");
	fprintf(g, "set title 'Regressão Linear'\n");
	fprintf(g, "set zeroaxis\n");
	fprintf(g, "f(x) = ");
	for(int i = incognito->lines - 1; i >= 0; i--) {
		if(i == incognito->lines - 1) {
			fprintf(g, "%lf*x**%d", incognito->data[i][0], i);
		} else {
			char s = incognito->data[i][0] >= 0 ? '+' : '-';
			fprintf(g, " %c %lf*x**%d", s, incognito->data[i][0], i);
		}
	}
	fprintf(g, "\n");

	fprintf(g, "plot '-' title 'Pontos', f(x) title '");

	fprintf(g, "f(x) = ");
	for(int i = incognito->lines - 1; i >= 0; i--) {
		if(i == incognito->lines - 1) {
			fprintf(g, "%lfx^%d", incognito->data[i][0], i);
		} else {
			char s = incognito->data[i][0] >= 0 ? '+' : '-';
			fprintf(g, " %c %lfx^%d", s, incognito->data[i][0], i);
		}
	}
	fprintf(g, "'\n");
    for (int i = 0; i < numberOfPoints; i++) {
        fprintf(g, "%lf %lf\n", points[i][0], points[i][1]);
    }
    fprintf(g, "e\n");
}