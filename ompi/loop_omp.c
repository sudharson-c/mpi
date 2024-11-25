#include <stdio.h>
#include <omp.h>

int main() {
    int total = 0;
    #pragma omp parallel for reduction(+:total)
    for (int i = 0; i < 10; i++) {
        printf("From for[%d] thread: %d\n", i, omp_get_thread_num());
        total += i;
    }

    printf("Total: %d\n", total);

    return 0;
}
