#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int num_threads = 10; // Default value

    // Check if the number of threads is provided as a command-line argument
    if (argc > 1) {
        num_threads = atoi(argv[1]);
    }

    // Set the number of threads
    omp_set_num_threads(num_threads);

    // Parallel region
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        printf("Hello from thread %d of %d!\n", thread_id, total_threads);
    }

    return 0;
}