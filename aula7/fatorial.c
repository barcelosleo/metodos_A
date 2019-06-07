#include <stdio.h>
#include <stdlib.h>

int fatorial(int n) {
	if (n == 1) {

	}
}

int main(int argc, char const *argv[]) {
	if (argc != 2) return 0;
	double n = atof(argv[1]);
	double fat = 1;

	for(double i = n; i >= 1; i--) {
		fat *= i;
	}

	printf("Fatorial de %.0f: %.0f\n", n, fat);
}