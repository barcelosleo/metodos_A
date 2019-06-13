#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Matrix_ {
	double** data;
	int lines;
	int columns;
} Matrix;

Matrix* createMatrix(int lines, int columns) {
	Matrix* newMatrix = (Matrix*) malloc (sizeof(Matrix));
	newMatrix->lines = lines;
	newMatrix->columns = columns;
	newMatrix->data = (double**) malloc (sizeof(double*) * lines);
	for(int i = 0; i < lines; i++) {
		newMatrix->data[i] = calloc (columns, sizeof(double));
	}
	return newMatrix;
}

Matrix* getSubMatrix(Matrix* original, int currentLine, int currentColumn) {
	Matrix* subMatrix = createMatrix(original->lines - 1, original->lines - 1);
	for (int i = 0, k = 0; i < original->lines; i++) {
		for (int j = 0, l = 0; j < original->columns; j++) {
			if (i != currentLine && j != currentColumn) {
				subMatrix->data[k][l] = original->data[i][j];
				l++;
			}
		}
		if (i != currentLine) k++;
	}
	return subMatrix;
}

void printMatrix(Matrix* matrix) {
	for(int i = 0; i < matrix->lines; i++) {
		for(int j = 0; j < matrix->columns; j++) {
			printf("%lf\t", matrix->data[i][j]);
		}
		printf("\n");
	}
}

double getDeterminant(Matrix* matrix) {
	if (matrix->lines != matrix->columns) {
		printf("Matriz não invertível, portanto, não existe o determinante!\n");
		exit(0);
	}
	if (matrix->lines == 2) {
		return (matrix->data[0][0] * matrix->data[1][1]) - (matrix->data[0][1] * matrix->data[1][0]);
	}

	double determinant = 0;

	for(int j = 0; j < matrix->columns; j++) {
		Matrix* subMatrix = getSubMatrix(matrix, 0, j);
		determinant += matrix->data[0][j] * getDeterminant(subMatrix) * pow(-1, j);
		free(subMatrix);
	}

	return determinant;
}

int main() {
	Matrix* m = createMatrix(3,3);
	// a = {{1.,4.,-7.},{-1.,-3.,10.},{-2.,-6.,12.}};
	m->data[0][0] = 1.;
	m->data[0][1] = 4.;
	m->data[0][2] = -7.;
	m->data[1][0] = -1.;
	m->data[1][1] = -3.;
	m->data[1][2] = -10.;
	m->data[2][0] = -2.;
	m->data[2][1] = -6.;
	m->data[2][2] = 12.;
	printMatrix(m);
	printf("Determinante: %lf\n", getDeterminant(m));
}