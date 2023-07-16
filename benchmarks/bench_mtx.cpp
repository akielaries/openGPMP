#include <benchmark/benchmark.h>
#include <armadillo>
#include <Eigen/Dense>
#include <vector>
#include <random>
#include "../include/linalg/mtx.hpp"

/******************************************************************************/
// Matrix Arithmetic class benchmarks.
// - Accelerated methods (SIMD intrinsics) VS. Naive methods
// - openGPMP vs Eigen
// - openGPMP vs Armadillo
/******************************************************************************/
// Define the benchmark function for gpmp::linalg::Mtx::mtx_add
static void BM_GPMP_simd_mtx_add(benchmark::State& state) {
  std::vector<std::vector<int>> A;
  std::vector<std::vector<int>> B;  
  std::vector<std::vector<int>> C;
  int matrixSize = 8192;
  gpmp::linalg::Mtx mtx;

  // Resize the vectors to allocate memory
  A.resize(matrixSize, std::vector<int>(matrixSize));
  B.resize(matrixSize, std::vector<int>(matrixSize));
  C.resize(matrixSize, std::vector<int>(matrixSize));

  // initialize random number generator
  std::random_device rd; 
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribution(1, 100);

  // populate matrices A and B with random values
  for (int i = 0; i < matrixSize; ++i) {
    for (int j = 0; j < matrixSize; ++j) {
      A[i][j] = distribution(gen);
      B[i][j] = distribution(gen);
    }
  }

  for (auto _ : state) {
    mtx.mtx_add(A, B, C);
  }
}
BENCHMARK(BM_GPMP_simd_mtx_add);

// Define the benchmark function for gpmp::linalg::Mtx::std_mtx_add
template <typename T>
static void BM_naive_mtx_add(benchmark::State& state) {
  std::vector<std::vector<int>> A;
  std::vector<std::vector<int>> B;
  std::vector<std::vector<int>> C;
  int matrixSize = 8192;
  gpmp::linalg::Mtx mtx;

  // Resize the vectors to allocate memory
  A.resize(matrixSize, std::vector<int>(matrixSize));
  B.resize(matrixSize, std::vector<int>(matrixSize));
  C.resize(matrixSize, std::vector<int>(matrixSize));

  // initialize random number generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribution(1, 100);

  // populate matrices A and B with random values
  for (int i = 0; i < matrixSize; ++i) {
    for (int j = 0; j < matrixSize; ++j) {
      A[i][j] = distribution(gen);
      B[i][j] = distribution(gen);
    }
  }

  for (auto _ : state) {
    mtx.std_mtx_add(A, B, C);
  }
}
BENCHMARK_TEMPLATE(BM_naive_mtx_add, int); 

// define benchmark for armadillo mtx addition
static void BM_armadillo_mtx_add(benchmark::State& state) {
  int size = 8912;
  // Define two matrices
  arma::imat A(size, size);
  arma::imat B(size, size);

  std::random_device rd; 
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);

  // Initialize matrices with random integer values
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      A(i, j) = dis(gen);
      B(i, j) = dis(gen);
    }   
  }
  for (auto _ : state) {
    arma::imat C = A + B;
  }
}
// register benchmark
BENCHMARK(BM_armadillo_mtx_add);

// define benchmark for eigen mtx addition
static void BM_eigen_mtx_add(benchmark::State& state) {
  int size = 8912;
  // Define two matrices
  Eigen::MatrixXi A(size, size);
  Eigen::MatrixXi B(size, size);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);

  // Initialize matrices with random integer values
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      A(i, j) = dis(gen);
      B(i, j) = dis(gen);
    }
  }
  for (auto _ : state) {
      Eigen::MatrixXi C = A + B;
  }
}
// register benchmark
BENCHMARK(BM_eigen_mtx_add);

// Run the benchmarks
BENCHMARK_MAIN();

