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

    double start_time = omp_get_wtime();  // Record start time
    for (int repeat = 0; repeat < 5; repeat++) {  // Repeat 5 times
        double sum_even = 0.0;
        double sum_odd = 0.0;

        double start_time = omp_get_wtime();  // Record start time

#pragma omp parallel for num_threads(n_threads) reduction(+:sum_even)
        for (int i = 0; i < n; i += 2) {
            sum_even += 1.0 / (2 * i + 1);
        }

#pragma omp parallel for num_threads(n_threads) reduction(+:sum_odd)
        for (int i = 1; i < n; i += 2) {
            sum_odd += 1.0 / (2 * i + 1);
        }

        double end_time = omp_get_wtime();  // Record end time

        printf("[%.8f] → Pi=%.16f\n", end_time - start_time, 4.0 * (sum_even - sum_odd));
    }

    return 0;
}