#include <stdio.h>
#include <stdlib.h>

#define PLOT_LIMIT 20

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

double Pij(double x, double** points, int i, int j) {

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

FILE* show_graph(char* fileName, int numberOfPoints) {
	double** points = getPoints(fileName, numberOfPoints);
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "set zeroaxis\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set xrange[-20:20]\n");
    fprintf(gnuplotPipe, "set yrange[-1000:1000]\n");
    fprintf(gnuplotPipe, "plot '-' title 'f(x)' with lines, '-' title 'Pontos'\n");
    for(double i = -PLOT_LIMIT; i <= PLOT_LIMIT; i += 0.1) {
        fprintf(gnuplotPipe, "%lf %lf\n", i, neville(i, numberOfPoints, points));
    }
    fprintf(gnuplotPipe, "e\n");

    for(int i = 0; i < numberOfPoints; i++) {
    	fprintf(gnuplotPipe, "%lf %lf\n", points[i][0], points[i][1]);
    }
    fprintf(gnuplotPipe, "e\n");
    return gnuplotPipe;
}

int main() {
	char fileName[100];
    int numberOfPoints = 0;
    double x = 0;

	printf("Digite o nome do arquivo com os pontos:\n");
    scanf("%s", fileName);
    printf("Digite o número de pontos a interpolar:\n");
    scanf("%d", &numberOfPoints);
    printf("Digite um valor de x para um novo y:\n");
    scanf("%lf", &x);

    double new_y = neville(x, numberOfPoints, getPoints(fileName, numberOfPoints));

    show_graph(fileName, numberOfPoints);

    printf("Novo y = %lf\n", new_y);
}