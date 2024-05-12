#include <benchmark/benchmark.h>

// Define the add1 function
int add1(int a, int b) {
    return a + b;
}

// Define the add2 function
int add2(int a, int b) {
    return a + b;
}

// Define the benchmark for add1
static void BM_Add1(benchmark::State& state) {
    int a = 10;
    int b = 20;
    for (auto _ : state) {
        benchmark::DoNotOptimize(add1(a, b));
    }
}
BENCHMARK(BM_Add1);

// Define the benchmark for add2
static void BM_Add2(benchmark::State& state) {
    int a = 10;
    int b = 20;
    for (auto _ : state) {
        benchmark::DoNotOptimize(add2(a, b));
    }
}
BENCHMARK(BM_Add2);

// Run the benchmarks
BENCHMARK_MAIN();

