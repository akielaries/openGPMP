#include <immintrin.h>
#include <vector>
#include <iostream>
#include <chrono>

// Block size for tiling optimization
const size_t BLOCK_SIZE = 256;

// Naive GEMM implementation (no optimizations)
void gemm_naive(const float* A, const float* B, float* C, size_t M, size_t N, size_t K) {
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            C[i * N + j] = 0.0f;
            for (size_t k = 0; k < K; ++k) {
                C[i * N + j] += A[i * K + k] * B[k * N + j];
            }
        }
    }
}

// Tiled GEMM implementation (optimized with blocking and packing)
void pack_matrix_A(const float* A, float* packed_A, size_t M, size_t K, size_t block_start_row, size_t block_start_col) {
    for (size_t i = 0; i < BLOCK_SIZE && (block_start_row + i) < M; ++i) {
        for (size_t j = 0; j < BLOCK_SIZE && (block_start_col + j) < K; ++j) {
            packed_A[i * BLOCK_SIZE + j] = A[(block_start_row + i) * K + block_start_col + j];
        }
    }
}

void pack_matrix_B(const float* B, float* packed_B, size_t K, size_t N, size_t block_start_row, size_t block_start_col) {
    for (size_t i = 0; i < BLOCK_SIZE && (block_start_row + i) < K; ++i) {
        for (size_t j = 0; j < BLOCK_SIZE && (block_start_col + j) < N; ++j) {
            packed_B[i * BLOCK_SIZE + j] = B[(block_start_row + i) * N + block_start_col + j];
        }
    }
}

void gemm_block(const float* packed_A, const float* packed_B, float* C, size_t M, size_t N, size_t K, size_t block_row, size_t block_col) {
    for (size_t i = 0; i < BLOCK_SIZE && (block_row + i) < M; ++i) {
        for (size_t j = 0; j < BLOCK_SIZE && (block_col + j) < N; ++j) {
            float sum = 0.0f;
            for (size_t k = 0; k < BLOCK_SIZE && k < K; ++k) {
                sum += packed_A[i * BLOCK_SIZE + k] * packed_B[k * BLOCK_SIZE + j];
            }
            C[(block_row + i) * N + block_col + j] += sum;
        }
    }
}

void gemm_tiled(const float* A, const float* B, float* C, size_t M, size_t N, size_t K) {
    std::vector<float> packed_A(BLOCK_SIZE * BLOCK_SIZE, 0.0f);
    std::vector<float> packed_B(BLOCK_SIZE * BLOCK_SIZE, 0.0f);

    for (size_t block_row = 0; block_row < M; block_row += BLOCK_SIZE) {
        for (size_t block_col = 0; block_col < N; block_col += BLOCK_SIZE) {
            for (size_t block_k = 0; block_k < K; block_k += BLOCK_SIZE) {
                pack_matrix_A(A, packed_A.data(), M, K, block_row, block_k);
                pack_matrix_B(B, packed_B.data(), K, N, block_k, block_col);
                gemm_block(packed_A.data(), packed_B.data(), C, M, N, K, block_row, block_col);
            }
        }
    }
}

void print_matrix(const std::vector<float>& mat, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << mat[i * cols + j] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    // Dimensions of matrices (use larger sizes for more meaningful benchmarks)
    size_t M = 384, N = 384, K = 384;

    // Initialize matrices with random values
    std::vector<float> A(M * K, 1.0f);
    std::vector<float> B(K * N, 1.0f);
    std::vector<float> C_naive(M * N, 0.0f);
    std::vector<float> C_optimized(M * N, 0.0f);

    // Measure time for naive GEMM
    auto start_naive = std::chrono::high_resolution_clock::now();
    gemm_naive(A.data(), B.data(), C_naive.data(), M, N, K);
    auto end_naive = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration_naive = end_naive - start_naive;
    std::cout << "Naive GEMM Time: " << duration_naive.count() << " seconds\n";

    // Measure time for optimized GEMM
    auto start_optimized = std::chrono::high_resolution_clock::now();
    gemm_tiled(A.data(), B.data(), C_optimized.data(), M, N, K);
    auto end_optimized = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration_optimized = end_optimized - start_optimized;
    std::cout << "Optimized GEMM Time: " << duration_optimized.count() << " seconds\n";

    // Verify results
    bool correct = true;
    for (size_t i = 0; i < M * N; ++i) {
        if (std::abs(C_naive[i] - C_optimized[i]) > 1e-6) {
            correct = false;
            break;
        }
    }

    if (correct) {
        std::cout << "Results match between naive and optimized GEMM.\n";
    } else {
        std::cout << "Results do not match between naive and optimized GEMM.\n";
    }

    return 0;
}

