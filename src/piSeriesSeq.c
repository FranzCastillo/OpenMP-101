#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <num_terms>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    double factor = 1.0;
    double sum = 0.0;
    for (int k=0; k<n; k++) {
        sum += factor/(2*k+1);
        factor = -factor;
    }

    printf("Pi is approximately %.16f\n", 4.0*sum);

    return 0;
}