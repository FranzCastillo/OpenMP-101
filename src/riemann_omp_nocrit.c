#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

const double n = 10e6;  // Number of intervals

double f(const double x) {
    // return x * x;
    // return 2 * pow(x, 3);
    return sin(x);
}

/**
* Compute the integral of f(x) using Rieman's method with the left rule
*/
double trapezoides(const double n_local, const double dx, const int a, const int b) {
    double sum = 0;
    for (int i = 0; i < n_local; i++) {
        const double x = a + i * dx;
        sum += f(x);
    }
    return sum * dx;
}

int main(int argc, char *argv[]) {
    // Number of threads must be provided as a command-line argument
    if (argc != 4) {
        printf("Usage: %s <lower_limit (a)> <upper_limit (b)> <num_threads>\n", argv[0]);
        return 1;
    }

    // Get the limits
    const int a = atoi(argv[1]);
    const int b = atoi(argv[2]);
    const int n_threads = atoi(argv[3]);

    // Check n is a multiple of num_threads
    if ((int)n % n_threads != 0) {
        printf("Error: num_threads must be a factor of n\n");
        return 1;
    }

    // Compute the step size
    const double dx = (b - a) / n;

    // Compute the number of intervals per thread
    const double n_local = n / n_threads;

    // Array to store the sum of the integrals
    double sums[n_threads];

    // Compute the integral
    #pragma omp parallel num_threads(n_threads)
    {
        const int tid = omp_get_thread_num();

        const double a_local = a + (tid * n_local * dx);
        const double b_local = a_local + n_local * dx;
        printf("Thread %d: [a, b] = [%f, %f]\n", tid, a_local, b_local);

        const double local_sum = trapezoides(n_local, dx, a_local, b_local);

        sums[tid] = local_sum;
    }

    // Compute the total sum
    double sum = 0;
    for (int i = 0; i < n_threads; i++) {
        sum += sums[i];
    }

    printf("n = %e\n", n);
    printf("f(x) = sin(x)\n");
    printf("[a, b] = [%d, %d]\n", a, b);
    printf("Approximation = %f\n", sum);
}