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

    double start_time = omp_get_wtime();  // Record start time

#pragma omp parallel for num_threads(n_threads) reduction(+:sum) private(factor)
    for (int k = 0; k < n; k++) {
        factor = (k % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2 * k + 1);
    }

    double end_time = omp_get_wtime();  // Record end time


    printf("Pi is approximately %.16f\n", 4.0 * sum);
    printf("Execution time: %f seconds\n", end_time - start_time);  // Print elapsed time


    return 0;
}