#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <num_threads> <num_terms>\n", argv[0]);
        return 1;
    }

    int n_threads = atoi(argv[1]);
    int n = atoll(argv[2]);

    double sum = 0.0;
    double factor = 0.0;
#pragma omp parallel for num_threads(n_threads) reduction(+:sum) private(factor)
    for (int k = 0; k < n; k++) {
        factor = (k % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2 * k + 1);
    }

    printf("Pi is approximately %.16f\n", 4.0 * sum);

    return 0;
}