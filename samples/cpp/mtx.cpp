#include "../../include/linalg/mtx.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
constexpr int matrixSize = 8912;

void run_mtx_add() {
    std::vector<std::vector<int>> A(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> B(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> C(matrixSize, std::vector<int>(matrixSize));

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

    std::chrono::steady_clock::time_point start_time_u =
        std::chrono::steady_clock::now();
    // Perform matrix addition
    gpmp::linalg::Mtx mtx;
    mtx.mtx_add(A, B, C);
    std::chrono::steady_clock::time_point end_time_u =
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
    */

    std::cout << "Loop Unrolling - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time_u - start_time_u)
                     .count()
              << " ms" << std::endl;
}

int main() {
    run_mtx_add();

    return 0;
}
