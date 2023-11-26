#include "../../include/linalg/mtx.hpp"
#include <chrono>
#include <iostream>
#include <openGPMP/linalg/mtx.hpp>
#include <random>
#include <vector>
constexpr int matrixSize = 8912;

void run_mtx_add() {
    std::chrono::steady_clock::time_point start_time =
        std::chrono::steady_clock::now();

    std::vector<std::vector<int>> A(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> B(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> C(matrixSize, std::vector<int>(matrixSize));

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

    std::chrono::steady_clock::time_point start_time_u =
        std::chrono::steady_clock::now();
    // perform matrix addition
    gpmp::linalg::Mtx mtx;
    mtx.mtx_add(A, B, C);
    std::chrono::steady_clock::time_point end_time_u =
        std::chrono::steady_clock::now();

    mtx.std_mtx_add(A, B, C);
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
    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    std::cout << "SIMD - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time_u - start_time_u)
                     .count()
              << " ms" << std::endl;

    std::cout << "NAIVE - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - end_time_u)
                     .count()
              << " ms" << std::endl;

    std::cout << "Total Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " ms" << std::endl;
}

void fill_matrix_random(float *matrix, std::size_t rows, std::size_t cols) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(1.0, 100.0);

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            matrix[i * cols + j] = distribution(gen);
        }
    }
}

void print_matrix(const float *matrix, std::size_t rows, std::size_t cols) {
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            std::cout << matrix[i * cols + j] << " ";
        }
        std::cout << std::endl;
    }
}

void mtx_add_f90() {
    float *A = new float[matrixSize * matrixSize];
    float *B = new float[matrixSize * matrixSize];
    float *C = new float[matrixSize * matrixSize];
    // Initialize A and B matrices with random values
    fill_matrix_random(A, matrixSize, matrixSize);
    fill_matrix_random(B, matrixSize, matrixSize);

    gpmp::linalg::Mtx mtx;

    std::chrono::steady_clock::time_point start_time =
        std::chrono::steady_clock::now();

    // Call the Fortran matrix addition function through the C++ wrapper
    mtx.mtx_add_f90(A, B, C, matrixSize);

    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    // Perform any further operations or print the result as needed
    /*std::cout << "Matrix A:" << std::endl;
    print_matrix(A, matrixSize, matrixSize);

    std::cout << "\nMatrix B:" << std::endl;
    print_matrix(B, matrixSize, matrixSize);

    std::cout << "\nMatrix C:" << std::endl;
    print_matrix(C, matrixSize, matrixSize);*/

    std::cout << "mtx add using Fortran & flattened matrices: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " ms" << std::endl;

    delete[] A;
    delete[] B;
    delete[] C;
}

int main() {
    run_mtx_add();

    mtx_add_f90();
    return 0;
}
