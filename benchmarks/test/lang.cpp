#include <chrono>
#include <iostream>

#define NUM_OPS 100000000

template <typename T> void arithmetic_loop(T &result) {
    result = result + 1;
    result = result * 2;
    result = result / 2;
    result = result - 1;
}

template <typename T> void benchmark() {
    int i;
    T result;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    double cpu_time_used;

    start = std::chrono::high_resolution_clock::now();

    for (i = 0; i < NUM_OPS; i++) {
        arithmetic_loop(result);
    }

    end = std::chrono::high_resolution_clock::now();
    cpu_time_used =
        std::chrono::duration_cast<std::chrono::duration<double>>(end -
                                                                  start)
            .count();

    std::cout << "C++ benchmark: Performed " << NUM_OPS
              << " operations in " << cpu_time_used << " seconds."
              << std::endl;
}

int main() {
    benchmark<int>();

    return 0;
}
