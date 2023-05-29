#include "../../include/core/threadpool.hpp"
#include <chrono>
#include <immintrin.h>
#include <iostream>
#include <omp.h>
#include <random>
#include <vector>

constexpr int matrixSize = 10000;
constexpr int blockSize = 2;

void matrixAddition_t(const std::vector<std::vector<int>> &A,
                      const std::vector<std::vector<int>> &B,
                      std::vector<std::vector<int>> &C) {
    const int size = A.size();
    mtpk::core::ThreadPool threadPool(8);

    for (int i = 0; i < size; ++i) {
        threadPool.enqueue([&A, &B, &C, i]() {
            const int rowSize = A[i].size();
            for (int j = 0; j < rowSize; ++j) {
                C[i][j] = A[i][j] + B[i][j];
            }
        });
    }
}

void matrixAddition_u(const std::vector<std::vector<int>> &A, 
                      const std::vector<std::vector<int>> &B, 
                      std::vector<std::vector<int>> &C) {
    const int size = A.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; j += 128) {  // Unroll by 4 elements
            // Perform matrix addition
            C[i][j] = A[i][j] + B[i][j];
            C[i][j + 1] = A[i][j + 1] + B[i][j + 1];
            C[i][j + 2] = A[i][j + 2] + B[i][j + 2];
            C[i][j + 3] = A[i][j + 3] + B[i][j + 3];
        }
    }

}

void matrixAddition_c(const std::vector<std::vector<int>> &A,
                      const std::vector<std::vector<int>> &B,
                      std::vector<std::vector<int>> &C) {
    const int size = A.size();

    for (int i = 0; i < size; ++i) {
        std::vector<int>& C_row = C[i];
        const std::vector<int>& A_row = A[i];
        const std::vector<int>& B_row = B[i];

        for (int j = 0; j < size; ++j) {
            // Perform matrix addition
            C_row[j] = A_row[j] + B_row[j];
        }
    }

}


void matrixAddition_i(const std::vector<std::vector<int>> &A,
                      const std::vector<std::vector<int>> &B,
                      std::vector<std::vector<int>> &C) {
    const int size = A.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int result;
            asm (
                "movl %[a], %[result]\n\t"  // Move A[i][j] to result
                "addl %[b], %[result]\n\t"  // Add B[i][j] to result
                : [result] "=r" (result)   // Output operand (result)
                : [a] "r" (A[i][j]),       // Input operand (A[i][j])
                  [b] "r" (B[i][j])        // Input operand (B[i][j])
            );
            C[i][j] = result;  // Store the result in C[i][j]
        }
    }


}

// Function to perform matrix addition
void matrixAddition(const std::vector<std::vector<int>> &A,
                    const std::vector<std::vector<int>> &B,
                    std::vector<std::vector<int>> &C) {
    const int size = A.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; j += 4) {  // Unroll the inner loop by 4
            __m128i a = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&A[i][j]));
            __m128i b = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&B[i][j]));

            __m128i result = _mm_add_epi32(a, b);

            _mm_storeu_si128(reinterpret_cast<__m128i*>(&C[i][j]), result);
        }
    }


}

void matrixAddition_tf(const std::vector<std::vector<int>>& A,
                       const std::vector<std::vector<int>>& B,
                       std::vector<std::vector<int>>& C) {
    const int size = A.size();

    mtpk::core::parallel_for(size, [&](int start, int end) {
        for (int i = start; i < end; ++i) {
            std::vector<int>& C_row = C[i];
            const std::vector<int>& A_row = A[i];
            const std::vector<int>& B_row = B[i];

            for (int j = 0; j < size; ++j) {
                // Perform matrix addition
                C_row[j] = A_row[j] + B_row[j];
            }
        }
    });
}

void matrixAddition_n(const std::vector<std::vector<int>> &A,
                      const std::vector<std::vector<int>> &B,
                      std::vector<std::vector<int>> &C) {
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
    std::vector<std::vector<int>> H(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> I(matrixSize, std::vector<int>(matrixSize));

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

    std::chrono::steady_clock::time_point start_time_u =
        std::chrono::steady_clock::now();
    // Perform matrix addition
    matrixAddition_u(A, B, F);
    std::chrono::steady_clock::time_point end_time_u =
        std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point start_time_c =
        std::chrono::steady_clock::now();
    // Perform matrix addition
    matrixAddition_c(A, B, H);
    std::chrono::steady_clock::time_point end_time_c =
        std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point start_time_t =
        std::chrono::steady_clock::now();
    // Perform matrix addition
    matrixAddition_t(A, B, G);
    std::chrono::steady_clock::time_point end_time_t =
        std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point start_time_th =
        std::chrono::steady_clock::now();
    // Perform matrix addition
    matrixAddition_tf(A, B, I);
    std::chrono::steady_clock::time_point end_time_th =
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
        */
        // Display the result
        std::cout << "Matrix C after addition:" << std::endl;
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                std::cout << I[i][j] << " ";
            }
            std::cout << std::endl;
        }
        /*
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

    std::cout << "NULL!! INTRINSICS - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time_i - start_time_i)
                     .count()
              << " ms" << std::endl;

    std::cout << "Loop Unrolling - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time_u - start_time_u)
                     .count()
              << " ms" << std::endl;

    std::cout << "Cache Optimization - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time_c - start_time_c)
                     .count()
              << " ms" << std::endl;

    std::cout << "THREADPOOL - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time_t - start_time_t)
                     .count()
              << " ms" << std::endl;

    std::cout << "BLOCKED - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " ms" << std::endl;

    std::cout << "Threaded Loops - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time_th - start_time_th)
                     .count()
              << " ms" << std::endl;


    std::cout << "NAIVE - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time_n - start_time_n)
                     .count()
              << " ms" << std::endl;

    return 0;
}
