#include <stdint.h>
#include <stdio.h>
#include <time.h>

int main() {
    clock_t begin = clock();
    uint64_t val = 0;
    for (uint64_t j = 0; j < 100000000; j++) {
        val += j;
    }
    printf("Result: %llu\n", val);
    clock_t end = clock();
    double runtime = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Runtime: %lfms\n", runtime);
}
