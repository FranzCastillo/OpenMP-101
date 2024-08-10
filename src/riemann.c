#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double n = 10e6;

double f(const double x) {
    // return x * x;
    // return 2 * pow(x, 3);
    return sin(x);
}

/**
* Compute the integral of f(x) using Rieman's method with the left rule
*/
double trapezoides(const double dx, const int a, const int b) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        const double x = a + i * dx;
        sum += f(x);
    }
    return sum * dx;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <lower_limit (a)> <upper_limit (b)>\n", argv[0]);
        return 1;
    }

    // Get the limits
    const int a = atoi(argv[1]);
    const int b = atoi(argv[2]);

    const double dx = (b - a) / n;

    printf("n = %e\n", n);
    printf("f(x) = sin(x)\n");
    printf("[a, b] = [%d, %d]\n", a, b);
    printf("Approximation = %f\n", trapezoides(dx, a, b));
}