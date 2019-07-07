#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mleocomp.h"


double f1(double x) {
	return x + 4 * cos(x);
}

double f2(double x) {
	return exp(-pow(x,2)*cos(x));
}

void indicaRaiz(GnuPipe g, double raiz, int p) {
    fprintf(g, "set arrow to %lf,%d from %lf, %f\n", raiz, 0, (raiz + 1), sin(45)/2);
    fprintf(g, "set label 1 \"%.*f\" at %lf, %f\n", p, raiz, (raiz + 1), sin(45)/2);
    fprintf(g, "replot\n");

}

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
	double rMinPositiva = bisseccao(1, 2, 4, f1);
	printf("Menor Raíz Positiva: %lf\n", rMinPositiva);

	double I = trapezio(0, 1, 200, &f2);
	printf("Valor integral: %lf\n", I);

    double** points = getPoints("pontos.dat", 4);
	Matrix* incognito =  getIncognitoMatrix(points, 1, 4);
	printf("Os coeficientes que melhor da reta que melhor se aproxima dos pontos são:\n");
    for(int i = 0; i < incognito->lines; i++) {
        printf("α%d = %lf\n", i, incognito->data[i][0]);
    }

}