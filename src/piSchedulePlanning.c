#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int n_threads = 1;
    int n = 1000000000;  // 1e9
    int block_sizes[] = {16, 64, 128};
    const char* schedules[] = {"static", "dynamic", "guided", "auto"};
    omp_sched_t schedule_types[] = {omp_sched_static, omp_sched_dynamic, omp_sched_guided, omp_sched_auto};

    for (int i = 0; i < 4; i++) {  // Iterate over schedules
        printf("Schedule: %s\n", schedules[i]);
        for (int j = 0; j < 3; j++) {  // Iterate over block sizes
            printf("\tBlock size: %d\n", block_sizes[j]);

            for (int repeat = 0; repeat < 5; repeat++) {  // Repeat 5 times
                double sum = 0.0;
                double factor = 0.0;
                double start_time = omp_get_wtime();  // Record start time

                // Set the schedule and block size
                omp_set_schedule(schedule_types[i], block_sizes[j]);

#pragma omp parallel for num_threads(n_threads) reduction(+:sum) private(factor) schedule(runtime)
                for (int k = 0; k < n; k++) {
                    factor = (k % 2 == 0) ? 1.0 : -1.0;
                    sum += factor / (2 * k + 1);
                }

                double end_time = omp_get_wtime();  // Record end time
                printf("\t\t[%d] T=%.8f → Pi=%.16f\n", repeat, end_time - start_time, 4.0 * sum);
            }
        }
    }

    return 0;
}