#include <stdio.h>
#include <stdlib.h>

/**
 * Função para mostrar as somas parciais de maneira amigável
 */
void mostraSomatorio(int n, long int sum) {
	if (n == 1) {
		printf("S%d = 2^%d = %ld\n", n, n, sum);
		return;
	}

	printf("S%d = S%d + 2^%d = %ld\n", n, n - 1, n, sum);
}

/**
 * Função para calcular as potências de 2
 */
long int doisElevado(int x) {
	long int mPow = 1;
	while(x > 0) {
		mPow *= 2;
		x--;
	}
	return mPow;
}

int main(int argc, char const *argv[])
{
	int n = argc == 2 ? atof(argv[1]) : 40;
	if (n <= 0) return printf("Valor de n inválido\n");
	long int sum = 0;

	for(int i = 1; i <= n; i++) {
		sum += doisElevado(i);
		mostraSomatorio(i, sum);
	}

	return 0;
}
