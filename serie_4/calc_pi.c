#include <stdio.h>

int main(int argc, char *argv[]) {
    const int intervals = 1000000000;
    double pi = 0.0;

    double delta = 1.0 / (double) intervals;

    int j;
    for (j = 0; j <= intervals; j++) {
        double x = ((double) j - 0.5) * delta;
        pi += 4.0 / (1.0 + (x * x));
    }

    printf("Pi = %.10f\n", pi * delta);

    return 0;
}
