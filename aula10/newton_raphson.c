#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEV 1

double f(double x) {
        return (pow(sin(x) - 0.3, 3)) / (sqrt(pow(x, 2) + 1));
}

double df(double x) {
        return (pow((sin(x) - 0.3), 2) * ((3 * (pow(x, 2) + 1) * cos(x)) - (x * (sin(x) - 0.3)))) / pow((pow(x, 2) + 1), 0.5);
}

double newtonRaphson(double xN) {
        return xN + (f(xN) / df(xN));
}

double geraPontos() {
        FILE* file = fopen("pontos_funcao.dat", "w");
        for(double i = -100; i <= 100; i += 1e-1) {
            fprintf(file, "%lf %lf %lf\n", i, f(i), df(i));
        }
        printf("Arquivo Gerado!.\n");
        fclose(file);
}

double encontraRaiz(double x0, double p) {
        double xN = x0;
        double xN1 = newtonRaphson(x0);
        int i = 1;

        while ((fabs(xN1 - xN) < p) || i <= 50000) {
                xN = xN1;
                xN1 = newtonRaphson(xN);
                printf("Precisão: %lf\t|Xn+1 - Xn|: %lf\n", p, fabs(xN1 - xN));
                i++;
        }

        if (i == 50000) {
                printf("Programa estourou o limite de 50000 interações!\n");
        } else {
                printf("Valor aproximado da raíz para x0 = %lf é %lf. Resultado encontrado em %d interações.\n", x0, xN1, i);
        }

        return xN;
}

int main(int argc, char const *argv[]) {
        if (DEV || (argc > 1 && (argv[1] == "1"))) {
                int gA = 0;
                printf("Deseja gerar arquivo de pontos? [1] Sim [0] Não\n");
                scanf("%d", &gA);
                if (gA == 1) {
                    geraPontos();
                    printf("Saindo...\n");
                    return 1;
                }
                
        }

        double p = 1e-10;
        double e = 0;
        double x0 = 0;

        printf("Digite o valor da precisão desejada(casas depois da vírgula):\n");
        scanf("%lf", &p);

        printf("Digite o valor de x0:\n");
        scanf("%lf", &x0);

        p = pow(10, -p);
        printf("precisão %lf\n", p);

        encontraRaiz(x0, p);

}
