#include <stdio.h>
#include <omp.h>

int main() {
    int total = 0;

    #pragma omp parallel num_threads(5)
    {
        int local = 0;
        int id = omp_get_thread_num();

        for (int i = 0; i < 100; i++) {
            local += i;
        }

        #pragma omp critical
        {
            printf("Thread %d adding local sum %d to total\n", id, local);
            total += local;
        }
    }

    printf("Total: %d\n", total);

    return 0;
}
