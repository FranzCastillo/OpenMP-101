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

    double factor = 1.0;
    double sum = 0.0;
    #pragma omp parallel for num_threads(n_threads) reduction(+:sum)
    for (int k=0; k<n; k++) {
        sum += factor/(2*k+1);
        factor = -factor;
    }

    printf("Pi is approximately %.16f\n", 4.0*sum);

    return 0;
}