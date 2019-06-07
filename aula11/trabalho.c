#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define PLOT_LIMIT 10
#define MAX_INTERATIONS 50000

FILE* gnu = NULL;

double f(double x) {
        return (sin(x) / (pow(x, 2) + 1)) + 0.2 - (0.01 * pow(x, 2));
}

double df(double x) {
        return (-0.02 * x) + (cos(x) / (pow(x, 2) + 1)) - ((2 * x * sin(x)) / pow((pow(x, 2) + 1), 2));
}

void indicaRaiz(FILE *gnuplotPipe, double raiz, int p) {
        fprintf(gnuplotPipe, "set arrow to %lf,%d from %lf, %f\n", raiz, 0, (raiz + 1), sin(45)/2);
        fprintf(gnuplotPipe, "set label 1 \"%.*f\" at %lf, %f\n", p, raiz, (raiz + 1), sin(45)/2);
        fprintf(gnuplotPipe, "replot\n");

}

FILE* show_graph() {
        FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
        fprintf(gnuplotPipe, "set zeroaxis\n");
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "plot '-' title 'f(x)' with lines, '-' title 'df/dx' with lines\n");
        for(double i = -PLOT_LIMIT; i <= PLOT_LIMIT; i += 0.01) {
                fprintf(gnuplotPipe, "%lf %lf\n", i, f(i));
        }
        fprintf(gnuplotPipe, "e\n");
        for(double i = -PLOT_LIMIT; i <= PLOT_LIMIT; i += 0.01) {
                fprintf(gnuplotPipe, "%lf %lf\n", i, df(i));
        }
        fprintf(gnuplotPipe, "e\n");
        return gnuplotPipe;
}

double nextValueNewtonRaphson(double xN) {
        return xN - (f(xN) / df(xN));
}

double newtonRaphson(double x0, int p) {
        int i = 1;
        double xN = x0;
        double xN1 = nextValueNewtonRaphson(xN);
        while ((fabs(xN1 - xN) > pow(10, -p)) && i < MAX_INTERATIONS && xN1 <= DBL_MAX) {
                xN = xN1;
                xN1 = nextValueNewtonRaphson(xN);
                i++;
        }

        if ((fabs(xN1 - xN) > pow(10, -p)) || i == MAX_INTERATIONS) {
                printf("Raíz não encontrada! Tente outro x0.\n");
        } else {
                gnu = show_graph();
                printf("Raíz aproximada: %.*lf\n", p, xN1);
                printf("Interções: %d\n", i);

                fprintf(gnu, "set title 'Método de Newton-Raphson: x_0 = %lf p = %.0e'\n", x0, pow(10, -p));

                indicaRaiz(gnu, xN1, p);
                pclose(gnu);
        }

        return xN1;
}

double interacaoSimples(double x0, int p) {
        int i = 1;
        double xN = x0;
        double xN1 = f(xN) + x0;
        while ((fabs(xN1 - xN) > pow(10, -p)) && i < MAX_INTERATIONS && fabs(xN1 - xN) <= DBL_MAX) {
                xN = xN1;
                xN1 = f(xN) + xN;
                i++;
        }

        if ((fabs(xN1 - xN) > pow(10, -p)) || i == MAX_INTERATIONS || xN1 >= DBL_MAX) {
                printf("Raíz não encontrada! Tente outro x0.\n");
        } else {
                gnu = show_graph();
                printf("Raíz aproximada: %.*lf\n", p, xN1);
                printf("Interções: %d\n", i);

                fprintf(gnu, "set title 'Método da Interação Simples: x_0 = %lf p = %.0e'\n", x0, pow(10, -p));

                indicaRaiz(gnu, xN1, p);
                pclose(gnu);
        }

        return xN1;
}

double getSignal(double number) {
        return number >= 0 ? 1 : -1;
}

double bisseccao(double min, double max, int p) {
        int i = 1;
        double xN = min;
        double xN1 = max;
        double step = fabs(max - min);
        double dxN_signal = getSignal(f(xN));
        double dxN1_signal = getSignal(f(xN1));
        while ((fabs(xN1 - xN) > pow(10, -p)) && i < MAX_INTERATIONS && fabs(xN1 - xN) <= DBL_MAX) {
                if (dxN_signal != dxN1_signal) {
                        step /= 2 * -1;
                }

                xN = xN1;
                xN1 += step;

                dxN_signal = getSignal(f(xN));
                dxN1_signal = getSignal(f(xN1));

                i++;
        }

        if ((fabs(xN1 - xN) > pow(10, -p)) || i == MAX_INTERATIONS || xN1 >= DBL_MAX) {
                printf("Raíz não encontrada! Tente outro x0.\n");
        } else {
                gnu = show_graph();
                printf("Raíz aproximada: %.*lf\n", p, xN1);
                printf("Interções: %d\n", i);

                fprintf(gnu, "set title 'Método da Bissecção: x_{min} = %lf x_{max} = %lf p = %.0e'\n", min, max, pow(10, -p));

                indicaRaiz(gnu, xN1, p);
                pclose(gnu);
        }

        return xN1;
}

void newtonRapRotina() {
        double x0 = 0;
        int p = 0;
        int validP = 0;

        while (!validP) {
                printf("Entre com a precisão:(número de casas após a vírgula)\n");
                scanf("%d", &p);

                if (p <= 0) {
                        printf("Valor de precisão inválido. Tente um valor maior que 0!\n");
                } else {
                        validP = 1;
                }
        }
        printf("Entre com o x0:\n");
        scanf("%lf", &x0);
        double raiz = newtonRaphson(x0, p);
}

void intSimplesRotina() {
        double x0 = 0;
        int p = 0;
        int validP = 0;

        while (!validP) {
                printf("Entre com a precisão:(número de casas após a vírgula)\n");
                scanf("%d", &p);

                if (p <= 0) {
                        printf("Valor de precisão inválido. Tente um valor maior que 0!\n");
                } else {
                        validP = 1;
                }
        }
        printf("Entre com o x0:\n");
        scanf("%lf", &x0);
        double raiz = interacaoSimples(x0, p);
}

void bissecRotina() {
        int p = 0;
        double max = 0;
        double min = 0;
        int validP = 0;

        while (!validP) {
                printf("Entre com a precisão:(número de casas após a vírgula)\n");
                scanf("%d", &p);

                if (p <= 0) {
                        printf("Valor de precisão inválido. Tente um valor maior que 0!\n");
                } else {
                        validP = 1;
                }
        }
        while (min == max) {
                printf("Entre com o X mínimo:\n");
                scanf("%lf", &min);
                printf("Entre com o X máximo:\n");
                scanf("%lf", &max);

                if (min == max) {
                        printf("X mínimo deve ser diferente de X máximo!\n");
                }
        }

        // Troca os valores caso estejam na ordem errada
        if (min > max) {
                double aux = min;
                min = max;
                max = aux;
        }

        double raiz = bisseccao(min, max, p);

}

int main(int argc, char const *argv[]) {
        int metodo = 0;
        int continuar = 0;

        while(metodo != 1 && metodo != 2 && metodo != 3) {
                printf("Deseja qual método? [1] Interação Simples \t [2] Bissecção \t [3] Newton-Raphson \t [0] Sair\n");
                scanf("%d", &metodo);

                switch(metodo) {
                        case 0: return 0;
                        case 1: intSimplesRotina(); break;
                        case 2: bissecRotina(); break;
                        case 3: newtonRapRotina(); break;
                        default: printf("Método inválido!\n"); break;
                }

                if (metodo == 1 || metodo == 2 || metodo == 3) {

                        printf("Deseja tentar outro método? [1] Sim \t [0] Não\n");
                        scanf("%d", &continuar);

                        metodo = 0;

                        if (gnu) {
                                fprintf(gnu, "exit gnuplot\n");
                                pclose(gnu);
                        }

                        if (continuar == 0) {
                                return 0;
                        }
                }
        }

        return 0;
}