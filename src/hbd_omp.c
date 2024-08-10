#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    // Number of threads must be provided as a command-line argument
    if (argc != 2) {
        printf("Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }


    // Get the number of threads
    int num_threads = atoi(argv[1]);

    // Set the number of threads
    omp_set_num_threads(num_threads);

    // Parallel region
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        if (thread_id % 2 == 0) {
            printf("Saludos del hilo %d\n", thread_id);
        } else {
            printf("Feliz cumpleaños número %d!\n", omp_get_thread_num());
        }
    }

    return 0;
}