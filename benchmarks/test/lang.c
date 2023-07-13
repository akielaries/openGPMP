#include <stdio.h>
#include <time.h>

#define NUM_OPS 100000000

int main() {
    int i, result;
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    for (i = 0; i < NUM_OPS; i++) {
        result = i + 1;
        result = result * 2;
        result = result / 2;
        result = result - 1;
    }

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("C benchmark: Performed %d operations in %f seconds.\n",
           NUM_OPS,
           cpu_time_used);

    return 0;
}
