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

PointList* createPointList(int size) {
	PointList* pl = (PointList*) malloc (sizeof(PointList));
	pl->size = size;
	pl->points = calloc(sizeof(Point), size);
	return pl;
}

PointList* readPointsFromFile(char* fileName, int size) {
	PointList* pl = createPointList(size);
	FILE* file = fopen(fileName, "r");
	for (int i = 0; i < size; i++) {
		fscanf(file, "%lf %lf", &pl->points[i].x, &pl->points[i].y);
	}
	fclose(file);
	return pl;
}

void savePointsToFile(char* fileName, PointList* points) {
	FILE* file = fopen(fileName, "w");
	for (int i = 0; i < points->size; i++) {
		fprintf(file, "%lf %lf", points->points[i].x, points->points[i].y);
	}
	fclose(file);
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

// INTERPOLAÇÃO
double L(int i, double x, double** data, int numberOfPoints) {
    double multiplication = 1;
    for (int j = 0; j < numberOfPoints; j++) {
        if (i != j) multiplication *= (x - data[j][0]) / (data[i][0] - data[j][0]);
    }
    return multiplication;
}

double laGrange(double x, double** data, int numberOfPoints) {
    double sum = 0;
    for (int i = 0; i < numberOfPoints; i++) {
        sum += data[i][1] * L(i, x, data, numberOfPoints);
    }
    return sum;

}

double getAij(double** points, int i, int j, double x, int n) {
    if (j == 0) {
        return points[i][1];
    }

    if (i == n) { // controlar para quando o valor recebido for diferente de 0,n - 1

    }

    int k = j + i;
    double Xi = points[i][0];
    double Xk = points[k][0];

    double AijEsq = getAij(points, i, j - 1, x, n);
    double AijBaixo = getAij(points, i + 1, j - 1, x, n);

    double Aij = (1 / (Xi - Xk)) * (((x - Xk) * AijEsq) - ((x - Xi) * AijBaixo));

    return Aij;
}

double neville(double x, int n, double** points) {
    double Pn = getAij(points, 0, n - 1, x, n);
    return Pn;
}

// ZERO DE FUNÇÕES

double newtonRaphson(double x0, int p, double (*function)(double), double (*derivative)(double)) {
    int i = 1;
    double xN = x0;
    double xN1 = xN - ((*function)(xN) / (*derivative)(xN));
    while ((fabs(xN1 - xN) > pow(10, -p)) && i < MAX_INTERATIONS && xN1 <= DBL_MAX) {
        xN = xN1;
        xN1 = xN - ((*function)(xN) / (*derivative)(xN));
        i++;
    }

    if ((fabs(xN1 - xN) > pow(10, -p)) || i == MAX_INTERATIONS) {
        printf("Raíz não encontrada! Tente outro x0.\n");
        exit(0);
    } else {
        // printf("Raíz aproximada: %.*lf\n", p, xN1);
        // printf("Interções: %d\n", i);
    }

    return xN1;
}

double interacaoSimples(double x0, int p, double (*function)(double)) {
    int i = 1;
    double xN = x0;
    double xN1 = (*function)(xN) + x0;
    while ((fabs(xN1 - xN) > pow(10, -p)) && i < MAX_INTERATIONS && fabs(xN1 - xN) <= DBL_MAX) {
        xN = xN1;
        xN1 = (*function)(xN) + xN;
        i++;
    }

    if ((fabs(xN1 - xN) > pow(10, -p)) || i == MAX_INTERATIONS || xN1 >= DBL_MAX) {
        printf("Raíz não encontrada! Tente outro x0.\n");
        exit(0);
    } else {
        // printf("Raíz aproximada: %.*lf\n", p, xN1);
        // printf("Interções: %d\n", i);
    }

    return xN1;
}

double getSignal(double number) {
    return number >= 0 ? 1 : -1;
}

double bisseccao(double min, double max, int p, double (*function)(double)) {
    int i = 1;
    double xN = min;
    double xN1 = max;
    double step = fabs(max - min);
    double dxN_signal = getSignal((*function)(xN));
    double dxN1_signal = getSignal((*function)(xN1));
    while ((fabs(xN1 - xN) > pow(10, -p)) && i < MAX_INTERATIONS && fabs(xN1 - xN) <= DBL_MAX) {
        if (dxN_signal != dxN1_signal) {
            step /= 2 * -1;
        }

        xN = xN1;
        xN1 += step;

        dxN_signal = getSignal((*function)(xN));
        dxN1_signal = getSignal((*function)(xN1));

        i++;
    }

    if ((fabs(xN1 - xN) > pow(10, -p)) || i == MAX_INTERATIONS || xN1 >= DBL_MAX) {
        printf("Raíz não encontrada! Tente outro x0.\n");
        exit(0);
    } else {
        // printf("Raíz aproximada: %.*lf\n", p, xN1);
        // printf("Interções: %d\n", i);
    }

    return xN1;
}

// DERIVAÇÃO

double df_direita(double x, double h, double (*function)(double)) {
	return ((*function)(x + h) - (*function)(x)) / h;
}

double df_centrada(double x, double h, double (*function)(double)) {
	return (((*function)(x + h) - (*function)(x - h)) / (2 * h));
}

// MATRIZES



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
		printf("Matriz não quadrada, portanto, não existe o determinante!\n");
		exit(0);
	}

	if (matrix->lines == 1) {
		return fabs(matrix->data[0][0]);
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

Matrix* getTranposedMatrix(Matrix* matrix) {
	Matrix* transposed = createMatrix(matrix->lines, matrix->columns);
	for(int i = 0; i < matrix->lines; i++) {
		for(int j = 0; j < matrix->columns; j++) {
			transposed->data[j][i] = matrix->data[i][j];
		}
	}
	return transposed;
}

Matrix* getCofactorMatrix(Matrix* matrix) {
	Matrix* cofactor = createMatrix(matrix->lines, matrix->columns);
	for(int i = 0; i < matrix->lines; i++) {
		for(int j = 0; j < matrix->columns; j++) {
			Matrix* subMatrix = getSubMatrix(matrix, i, j);
			cofactor->data[i][j] = pow(-1, i + j) * getDeterminant(subMatrix);
			free(subMatrix);
		}
	}
	return cofactor;

}

Matrix* multiplyMatrixByNumber(Matrix* matrix, double n) {
	Matrix* m_copy = createMatrix(matrix->lines, matrix->columns);
	for (int i = 0; i < matrix->lines; i++) {
		for (int j = 0; j < matrix->columns; j++) {
			m_copy->data[i][j] = matrix->data[i][j] * n;
		}
	}
	return m_copy;
}

Matrix* multiplyMatrixByMatrix(Matrix* m1, Matrix* m2) {
	if (m1->columns != m2->lines) {
		printf("Não é possível multiplicar estas matrizes");
		exit(0);
	}
	Matrix* product = createMatrix(m1->lines, m2->columns);
	for(int i = 0; i < m1->lines; i++) {
		for(int j = 0; j < m2->columns; j++) {
			for(int k = 0; k < m1->lines; k++) {
				product->data[i][j] += m1->data[i][k] * m2->data[k][j];
			}
		}
	}
	return product;
}

Matrix* getInverse(Matrix* matrix) {
	if (matrix->lines != matrix->columns) {
		printf("Matriz não quadrada, portanto, não é invertível!");
		exit(0);
	}

	double determinant = getDeterminant(matrix);

	if (determinant == 0) {
		printf("Matriz não é invertível, pois sua determinante é 0!");
		exit(0);
	}

	Matrix* cofactor = getCofactorMatrix(matrix);
	Matrix* cofactorTranposed = getTranposedMatrix(cofactor);

	Matrix* inverted = multiplyMatrixByNumber(cofactorTranposed, 1 / determinant);

	free(cofactor);
	free(cofactorTranposed);

	return inverted;
}

// FITTING

double pointSumX(int p, int N, double** points, double (*function)(double, double)) {
	if (p == 0) return 1;
	double sum = 0;
	for (int i = 0; i < N; i++) {
		sum += (*function)(points[i][0], p);
	}
	return sum;
}

double pointSumYX(int p, int N, double** points, double (*function)(double, double)) {
	double sum = 0;
	for (int i = 0; i < N; i++) {
		sum += points[i][1] * (*function)(points[i][0], p);
	}
	return sum;
}

Matrix* getCoefficientMatrix(double** points, int polynomialDegree, int N) {
	Matrix* coefficientMatrix = createMatrix(polynomialDegree + 1, polynomialDegree + 1);
	for(int i = 0; i < coefficientMatrix->lines; i++) {
		for(int j = 0; j < coefficientMatrix->columns; j++) {
			if (i == 0 && j == 0) {
				coefficientMatrix->data[i][j] = N;
			} else {
				coefficientMatrix->data[i][j] = pointSumX(i + j, N, points, &pow);
			}
		}
	}
	return coefficientMatrix;
}

Matrix* getIndependentTermsMatrix(double** points, int polynomialDegree, int N) {
	Matrix* independentTermsMatrix = createMatrix(polynomialDegree + 1, 1);
	for(int i = 0; i < independentTermsMatrix->lines; i++) {
		independentTermsMatrix->data[i][0] = pointSumYX(i, N, points, &pow);
	}
	return independentTermsMatrix;
}

Matrix* getIncognitoMatrix(double** points, int polynomialDegree, int N) {
	Matrix *incognitoMatrix, *independentTermsMatrix, *coefficientMatrix, *inverse;

	incognitoMatrix = createMatrix(polynomialDegree + 1, 1);

	independentTermsMatrix = getIndependentTermsMatrix(points, polynomialDegree, N);
	coefficientMatrix = getCoefficientMatrix(points, polynomialDegree, N);

	inverse = getInverse(coefficientMatrix);
	free(coefficientMatrix);

	incognitoMatrix = multiplyMatrixByMatrix(inverse, independentTermsMatrix);
	free(independentTermsMatrix);
	free(inverse);

	return incognitoMatrix;
}