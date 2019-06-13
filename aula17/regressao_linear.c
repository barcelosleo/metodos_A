#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../mleocomp.h"

int main() {
	Matrix *m = createMatrix(3,3), *a, *i;
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
	printf("-------------------------\n");
	i = getInverse(m);
	printf("-------------------------\n");
	printMatrix(i);

	free(m);
	free(a);
	free(i);
}