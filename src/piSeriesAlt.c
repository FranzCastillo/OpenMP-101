#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <num_threads> <num_terms>\n", argv[0]);
        return 1;
    }

    int n_threads = atoi(argv[1]);
    int n = atoi(argv[2]);

    double sum_even = 0.0;
    double sum_odd = 0.0;
#pragma omp parallel for num_threads(n_threads) reduction(+:sum_even)
    for (int i = 0; i < n; i += 2) {
        sum_even += 1.0 / (2 * i + 1);
    }

#pragma omp parallel for num_threads(n_threads) reduction(+:sum_odd)
    for (int i = 1; i < n; i += 2) {
        sum_odd += 1.0 / (2 * i + 1);
    }

    printf("Pi: %.16f\n", 4.0 * (sum_even - sum_odd));

    return 0;
}