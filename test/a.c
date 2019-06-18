#include <stdio.h>
#include "../mleocomp.h"

int main(int argc, char const *argv[]) {
    PointList* pl = readPointsFromFile("pontos.dat", 100);

    for(int i = 0; i < pl->size; i++) {
        printf("%lf %lf\n", pl->points[i].x, pl->points[i].y);
    }
}
