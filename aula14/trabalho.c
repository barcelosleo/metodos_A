#include <stdio.h>
#include <stdlib.h>

double L(int i, double x, double** data, int numberOfPoints) {
    double multiplication = 1;
    for (int j = 0; j < numberOfPoints; j++) {
        if (i != j) multiplication *= (x - data[j][0]) / (data[i][0] - data[j][0]);
    }
    return multiplication;
}

double P(double x, double** data, int numberOfPoints) {
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

double** neville_method(char* fileName, int numberOfPoints, double xMax, double xMin, int M) {
    double** points = getPoints(fileName, numberOfPoints);
    double** interpolatedPoints = (double**) malloc (sizeof(double*) * M);
    double step = (xMax - xMin) / M;
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "set zeroaxis\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set xrange[%lf:%lf]\n", xMin, xMax);
    fprintf(gnuplotPipe, "set title 'Método de Neville'\n");
    fprintf(gnuplotPipe, "plot '-' title 'f(x)' with lines, '-' title 'Pontos'\n");
    int j = 0;
    for(double i = xMin; i <= xMax; i += step, j++) {
        interpolatedPoints[j] = (double*) malloc (sizeof(double) * 2);
        interpolatedPoints[j][0] = i;
        interpolatedPoints[j][1] = neville(i, numberOfPoints, points);
        fprintf(gnuplotPipe, "%lf %lf\n", interpolatedPoints[j][0], interpolatedPoints[j][1]);
    }
    fprintf(gnuplotPipe, "e\n");

    for(int i = 0; i < numberOfPoints; i++) {
        fprintf(gnuplotPipe, "%lf %lf\n", points[i][0], points[i][1]);
    }
    fprintf(gnuplotPipe, "e\n");
    return interpolatedPoints;
}

double** lagrange_method(char* fileName, int numberOfPoints, double xMax, double xMin, int M) {
    double** points = getPoints(fileName, numberOfPoints);
    double** interpolatedPoints = (double**) malloc (sizeof(double*) * M);
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "set zeroaxis\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set xrange[%lf:%lf]\n", xMin, xMax);
    fprintf(gnuplotPipe, "set title 'Método de LaGrange'\n");
    fprintf(gnuplotPipe, "plot '-' title 'f(x)' with lines, '-' title 'Pontos'\n");
    double step = (xMax - xMin) / M;
    int j = 0;
    for(double i = xMin; i <= xMax; i += step, j++) {
        interpolatedPoints[j] = (double*) malloc (sizeof(double) * 2);
        interpolatedPoints[j][0] = i;
        interpolatedPoints[j][1] = P(i, points, numberOfPoints);
        fprintf(gnuplotPipe, "%lf %lf\n", interpolatedPoints[j][0], interpolatedPoints[j][1]);
    }
    fprintf(gnuplotPipe, "e\n");

    for(int i = 0; i < numberOfPoints; i++) {
        fprintf(gnuplotPipe, "%lf %lf\n", points[i][0], points[i][1]);
    }
    fprintf(gnuplotPipe, "e\n");
    return interpolatedPoints;
}

void writeFile(char* resultFileName, double** points, int M) {
    FILE* file = fopen(resultFileName, "w");
    for(int i = 0; i < M; i++) {
        fprintf(file, "%lf %lf\n", points[i][0], points[i][1]);
    }
    fclose(file);
}

int main() {
    int method = 0, numberOfPoints = 0, M = 0;
    double xMin = 0, xMax = 0;
    char pointsFile[100], resultFile[100];
    double** interpolatedPoints;

    printf("Digite o nome do arquivo com os pontos de entrada:\n");
    scanf("%s", pointsFile);

    printf("Digite o número de pontos deste arquivo a serem levados em conta na interpolação:\n");
    scanf("%d", &numberOfPoints);

    printf("Digite o nome do arquivo de saída:\n");
    scanf("%s", resultFile);

    printf("Digite o valor Máximo e Mínimo  do intervalo de Interpolação:\n");
    scanf("%lf %lf", &xMax, &xMin);

    if (xMax == xMin) {
        printf("Intervalo Inválido!\n");
        return 0;
    }
    if (xMax < xMin) {
        double aux = xMax;
        xMax = xMin;
        xMin = aux;
    }

    printf("Número de pontos a serem interpolados neste intervalo:\n");
    scanf("%d", &M);

    printf("Deseja utilizar qual método? [1] - Lagrange\t[2] - Neville:\n");
    scanf("%d", &method);

    if (method == 1) {
        interpolatedPoints = lagrange_method(pointsFile, numberOfPoints, xMax, xMin, M);
    } else {
        interpolatedPoints = neville_method(pointsFile, numberOfPoints, xMax, xMin, M);
    }

    if (interpolatedPoints) {
        writeFile(resultFile, interpolatedPoints, M);
    }

    return 1;

}
