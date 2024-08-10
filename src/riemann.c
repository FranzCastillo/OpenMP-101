#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const float n = 10e6;

float f1(const float x) {
    return x * x;
}

float f2(const float x) {
    return 2 * pow(x, 3);
}

float f3(const float x) {
    return sin(x);
}

/**
* Compute the integral of f(x) using Rieman's method with the left rule
*/
float trapezoides(const float dx, const int a, const int b) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        const float x = a + i * dx;
        sum += f3(x);
    }
    return sum * dx;
}

int main(int argc, char *argv[]) {
    // Number of threads must be provided as a command-line argument
    if (argc != 3) {
        printf("Usage: %s <lower_limit (a)> <upper_limit (b)>\n", argv[0]);
        return 1;
    }

    // Get the limits
    const int a = atoi(argv[1]);
    const int b = atoi(argv[2]);

    const float dx = (b - a) / n;

    printf("n = %e\n", n);
    printf("f(x) = sin(x)\n");
    printf("[a, b] = [%d, %d]\n", a, b);
    printf("Approximation = %f\n", trapezoides(dx, a, b));
}