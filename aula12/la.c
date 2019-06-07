#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PLOT_LIMIT 15

FILE* gnu = NULL;

double** getPoints(char* fileName, int numberOfPoints) {
    FILE* dataFile = fopen(fileName, "r");
    double** data = (double**) malloc (sizeof(double*) * numberOfPoints);
    for (int i = 0; i < numberOfPoints; i++) {
        data[i] = (double*) malloc (sizeof(double) * 2);
        fscanf(dataFile, "%lf %lf", &data[i][0], &data[i][1]);
    }
    return data;
}

void printPoints(double** data, int numberOfPoints) {
    for (int i = 0; i < numberOfPoints; i++) {
        printf("%lf %lf\n", data[i][0], data[i][1]);
    }
}

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

FILE* show_graph(char* fileName, int numberOfPoints) {
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "set zeroaxis\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set xrange[-20:20]\n");
    fprintf(gnuplotPipe, "set yrange[-1000:1000]\n");
    fprintf(gnuplotPipe, "plot '-' title 'f(x)' with lines\n");
    for(double i = -PLOT_LIMIT; i <= PLOT_LIMIT; i += 0.01) {
        fprintf(gnuplotPipe, "%lf %lf\n", i, P(i, getPoints(fileName, numberOfPoints), numberOfPoints));
    }
    fprintf(gnuplotPipe, "e\n");
    return gnuplotPipe;
}

int main(int argc, char const *argv[]) {
    char fileName[100];
    int numberOfPoints = 0;
    double x = 0;
    double **data;

    printf("Digite o nome do arquivo com os pontos:\n");
    scanf("%s", fileName);
    printf("Digite o número de pontos a interpolar:\n");
    scanf("%d", &numberOfPoints);
    printf("Digite um valor de x para um novo y:\n");
    scanf("%lf", &x);

    double new_y = P(x, getPoints(fileName, numberOfPoints), numberOfPoints);

    printf("Novo y = %lf\n", new_y);

    show_graph(fileName, numberOfPoints);

    return 0;
}
