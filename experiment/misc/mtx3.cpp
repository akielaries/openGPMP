#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <immintrin.h> 
#include <omp.h>
#include "../../include/core/threadpool.hpp"


constexpr int matrixSize = 10000;
constexpr int blockSize = 2;

void matrixAddition_t(const std::vector<std::vector<int>>& A,
                    const std::vector<std::vector<int>>& B,
                    std::vector<std::vector<int>>& C) {
    const int size = A.size();
    mtpk::core::ThreadPool threadPool;

    for (int i = 0; i < size; ++i) {
        threadPool.enqueue([&A, &B, &C, i]() {
            const int rowSize = A[i].size();
            for (int j = 0; j < rowSize; ++j) {
                C[i][j] = A[i][j] + B[i][j];
            }
        });
    }
}


void matrixAddition_o(const std::vector<std::vector<int>>& A,
                    const std::vector<std::vector<int>>& B,
                    std::vector<std::vector<int>>& C) {
    const int size = A.size();

    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // Perform matrix addition
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void matrixAddition_i(const std::vector<std::vector<int>>& A,
                    const std::vector<std::vector<int>>& B,
                    std::vector<std::vector<int>>& C) {
    const int size = A.size();

    // SIMD vectorization using AVX2
    constexpr int simdSize = 8;  // Number of elements processed in each SIMD operation
    constexpr int innerSize = matrixSize / simdSize;
    constexpr int remainingSize = matrixSize % simdSize;

    for (int i = 0; i < size; ++i) {
        int j = 0;
        for (; j < innerSize * simdSize; j += simdSize) {
            // Perform matrix addition using SIMD intrinsics
            __m256i aVec = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&A[i][j]));
            __m256i bVec = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&B[i][j]));
            __m256i resultVec = _mm256_add_epi32(aVec, bVec);
            _mm256_storeu_si256(reinterpret_cast<__m256i*>(&C[i][j]), resultVec);
        }

        // Handle the remaining elements
        for (; j < size; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}


// Function to perform matrix addition
void matrixAddition(const std::vector<std::vector<int>>& A,
                    const std::vector<std::vector<int>>& B,
                    std::vector<std::vector<int>>& C)
{
    const int size = A.size();

    // Loop blocking (loop tiling)
    for (int i = 0; i < size; i += blockSize) {
        for (int j = 0; j < size; j += blockSize) {
            for (int ii = i; ii < std::min(i + blockSize, size); ++ii) {
                for (int jj = j; jj < std::min(j + blockSize, size); ++jj) {
                    // Perform matrix addition
                    C[ii][jj] = A[ii][jj] + B[ii][jj];
                }
            }
        }
    }
}

void matrixAddition_n(const std::vector<std::vector<int>>& A,
                    const std::vector<std::vector<int>>& B,
                    std::vector<std::vector<int>>& C) {
    const int size = A.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // Perform matrix addition
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}


int main() {
    std::vector<std::vector<int>> A(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> B(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> C(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> D(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> E(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> F(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> G(matrixSize, std::vector<int>(matrixSize));

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // Populate matrices A and B with random values
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            A[i][j] = distribution(gen);
            B[i][j] = distribution(gen);
        }
    }

    std::chrono::steady_clock::time_point start_time =
        std::chrono::steady_clock::now();
    // Perform matrix addition
    matrixAddition(A, B, C);
    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point start_time_n =
        std::chrono::steady_clock::now();
    // Perform matrix addition
    matrixAddition_n(A, B, D); 
    std::chrono::steady_clock::time_point end_time_n =
        std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point start_time_i =
        std::chrono::steady_clock::now();
    // Perform matrix addition
    matrixAddition_i(A, B, E);
    std::chrono::steady_clock::time_point end_time_i =
        std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point start_time_o =
        std::chrono::steady_clock::now();
    // Perform matrix addition
    matrixAddition_o(A, B, F);
    std::chrono::steady_clock::time_point end_time_o =
        std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point start_time_t =
        std::chrono::steady_clock::now();
    // Perform matrix addition
    matrixAddition_o(A, B, G);
    std::chrono::steady_clock::time_point end_time_t =
        std::chrono::steady_clock::now();

/*
    std::cout << "Matrix A:" << std::endl;
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            std::cout << A[i][j] << " ";
        }   
        std::cout << std::endl;
    }   

    std::cout << "Matrix B:" << std::endl;
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            std::cout << B[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Display the result
    std::cout << "Matrix C after addition:" << std::endl;
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nMatrix D after addition:" << std::endl;
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            std::cout << D[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nMatrix E after addition:" << std::endl;
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            std::cout << E[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nMatrix F after addition:" << std::endl;
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            std::cout << F[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nMatrix G after addition:" << std::endl;
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            std::cout << G[i][j] << " ";
        }
        std::cout << std::endl;
    }
    */


    std::cout << "INTRINSICS - Time elapsed: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time_i - start_time_i).count() << " ms" << std::endl;

    std::cout << "INTRINSICS + THREADS - Time elapsed: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time_o - start_time_o).count() << " ms" << std::endl;

    std::cout << "THREADPOOL - Time elapsed: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time_t - start_time_t).count() << " ms" << std::endl;

    std::cout << "BLOCKED - Time elapsed: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time - start_time).count() << " ms" << std::endl;

    std::cout << "NAIVE - Time elapsed: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time_n - start_time_n).count() << " ms" << std::endl;


    return 0;
}

