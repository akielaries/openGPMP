#include <chrono>
#include <iostream>
#include <stdio.h>

#define NUM_OPS 100000000

int main() {
    int i, result;
    clock_t c_start, c_end;
    std::chrono::time_point<std::chrono::high_resolution_clock> cpp_start,
        cpp_end;
    double c_cpu_time_used, cpp_cpu_time_used;

    // C benchmark
    c_start = clock();

    for (i = 0; i < NUM_OPS; i++) {
        result = i + 1;
        result = result * 2;
        result = result / 2;
        result = result - 1;
    }

    c_end = clock();
    c_cpu_time_used = ((double)(c_end - c_start)) / CLOCKS_PER_SEC;

    printf("C benchmark: Performed %d operations in %f seconds.\n", NUM_OPS,
           c_cpu_time_used);

    // C++ benchmark
    cpp_start = std::chrono::high_resolution_clock::now();

    for (i = 0; i < NUM_OPS; i++) {
        result = i + 1;
        result = result * 2;
        result = result / 2;
        result = result - 1;
    }

    cpp_end = std::chrono::high_resolution_clock::now();
    cpp_cpu_time_used =
        std::chrono::duration_cast<std::chrono::duration<double>>(cpp_end -
                                                                  cpp_start)
            .count();

    std::cout << "C++ benchmark: Performed " << NUM_OPS << " operations in "
              << cpp_cpu_time_used << " seconds." << std::endl;

    return 0;
}
