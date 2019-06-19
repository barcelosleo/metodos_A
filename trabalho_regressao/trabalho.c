#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

void main() {
    char fileName[100];
    int numberOfPoints = 0;
    printf("Digite o nome do arquivo onde estão os pontos:\n");
    scanf("%s", fileName);
    printf("Digite o número de pontos:\n");
    scanf("%d", &numberOfPoints);
    double** points = getPoints(fileName, numberOfPoints);

    BM* b = startBenchmark("Tempo de Execução da Regressão Linear");
    Matrix* incognito = getIncognitoMatrix(points, 1, numberOfPoints);
    stopBenchmark(b);
    printf("Os coeficientes são:\n");
    for(int i = 0; i < incognito->lines; i++) {
        printf("α%d = %lf\n", i, incognito->data[i][0]);
    }

    GnuPipe g = initializeGnuPipe();

	fprintf(g, "set grid\n");
	fprintf(g, "set title 'Regressão Linear'\n");
	fprintf(g, "set zeroaxis\n");
    char s = incognito->data[0][0] >= 0 ? '+' : '-';
	fprintf(g, "f(x) = %lf*x %c %lf\n", incognito->data[1][0], s, fabs(incognito->data[0][0]));
	fprintf(g, "plot '-' title 'Pontos', f(x) title 'f(x) = %lfx %c %lf'\n", incognito->data[1][0], s, fabs(incognito->data[0][0]));
    for (int i = 0; i < numberOfPoints; i++) {
        fprintf(g, "%lf %lf\n", points[i][0], points[i][1]);
    }
    fprintf(g, "e\n");


}