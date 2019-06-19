#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

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
	Matrix *i;
	// m->data = {{1.,4.,-7.},{-1.,-3.,10.},{-2.,-6.,12.}};
	double** points = getPoints("pontos.dat", 10);

	// Matrix* m = createMatrix(2, 2);
	// m->data = points;

	// printMatrix(m);
	// i = getInverse(m);
	// printMatrix(i);

	i = getIncognitoMatrix(points, 2, 10);
	printMatrix(i);

	free(i);
}