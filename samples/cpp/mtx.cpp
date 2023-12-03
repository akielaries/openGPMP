#include <chrono>
#include <iostream>
#include <openGPMP/linalg/mtx.hpp>
#include <random>
#include <vector>
constexpr int matrixSize = 8912;

void run_mtx_add() {
    gpmp::linalg::Mtx mtx;

    std::chrono::steady_clock::time_point gen_start_time =
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

    std::chrono::steady_clock::time_point start_time_mtx =
        std::chrono::steady_clock::now();
    // perform matrix addition
    mtx.mtx_add(A, B, C);
    std::chrono::steady_clock::time_point start_time_std_mtx =
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

    std::cout << "Generating random matrices (VECTORS) - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     start_time_mtx - gen_start_time)
                     .count()
              << " ms" << std::endl;

    std::cout << "SIMD - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     start_time_std_mtx - start_time_mtx)
                     .count()
              << " ms" << std::endl;

    std::cout << "NAIVE - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time_std_mtx)
                     .count()
              << " ms" << std::endl;
}

void run_mtx_add_flt() {
    gpmp::linalg::Mtx mtx;

    std::chrono::steady_clock::time_point gen_start_time =
        std::chrono::steady_clock::now();

    std::vector<std::vector<float>> A(matrixSize,
                                      std::vector<float>(matrixSize));
    std::vector<std::vector<float>> B(matrixSize,
                                      std::vector<float>(matrixSize));
    std::vector<std::vector<float>> C(matrixSize,
                                      std::vector<float>(matrixSize));

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(1.0, 100.0);

    // populate matrices A and B with random values
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            A[i][j] = distribution(gen);
            B[i][j] = distribution(gen);
        }
    }

    std::chrono::steady_clock::time_point start_time_mtx =
        std::chrono::steady_clock::now();
    // perform matrix addition
    mtx.mtx_add(A, B, C);
    std::chrono::steady_clock::time_point start_time_std_mtx =
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

    std::cout << "Generating random matrices (VECTORS, FLOATS) - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     start_time_mtx - gen_start_time)
                     .count()
              << " ms" << std::endl;

    std::cout << "SIMD - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     start_time_std_mtx - start_time_mtx)
                     .count()
              << " ms" << std::endl;

    std::cout << "NAIVE - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time_std_mtx)
                     .count()
              << " ms" << std::endl;
}

void run_mtx_add_doub() {
    gpmp::linalg::Mtx mtx;

    std::chrono::steady_clock::time_point gen_start_time =
        std::chrono::steady_clock::now();

    std::vector<std::vector<double>> A(matrixSize,
                                       std::vector<double>(matrixSize));
    std::vector<std::vector<double>> B(matrixSize,
                                       std::vector<double>(matrixSize));
    std::vector<std::vector<double>> C(matrixSize,
                                       std::vector<double>(matrixSize));

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(1.0, 100.0);

    // populate matrices A and B with random values
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            A[i][j] = distribution(gen);
            B[i][j] = distribution(gen);
        }
    }

    std::chrono::steady_clock::time_point start_time_mtx =
        std::chrono::steady_clock::now();
    // perform matrix addition
    mtx.mtx_add(A, B, C);
    std::chrono::steady_clock::time_point start_time_std_mtx =
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

    std::cout
        << "Generating random matrices (VECTORS, DOUBLES) - Time elapsed: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(
               start_time_mtx - gen_start_time)
               .count()
        << " ms" << std::endl;

    std::cout << "SIMD - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     start_time_std_mtx - start_time_mtx)
                     .count()
              << " ms" << std::endl;

    std::cout << "NAIVE - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time_std_mtx)
                     .count()
              << " ms" << std::endl;
}

void run_mtx_add_arr() {
    gpmp::linalg::Mtx mtx;

    std::chrono::steady_clock::time_point gen_start_time =
        std::chrono::steady_clock::now();

    /*new int A[matrixSize * matrixSize];
    new int B[matrixSize * matrixSize];
    new int C[matrixSize * matrixSize];
    */

    int *A = new int[matrixSize * matrixSize];
    int *C = new int[matrixSize * matrixSize];
    int *B = new int[matrixSize * matrixSize];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // populate matrices A and B with random values
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            A[i * matrixSize + j] = distribution(gen);
            B[i * matrixSize + j] = distribution(gen);
        }
    }

    std::chrono::steady_clock::time_point start_time_mtx =
        std::chrono::steady_clock::now();
    // perform matrix addition
    mtx.mtx_add(A, B, C, matrixSize, matrixSize);
    std::chrono::steady_clock::time_point start_time_std_mtx =
        std::chrono::steady_clock::now();

    mtx.std_mtx_add(A, B, C, matrixSize, matrixSize);

    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    std::cout << "Generating random matrices (ARRAYS, INT) - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     start_time_mtx - gen_start_time)
                     .count()
              << " ms" << std::endl;

    std::cout << "SIMD - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     start_time_std_mtx - start_time_mtx)
                     .count()
              << " ms" << std::endl;

    std::cout << "NAIVE - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time_std_mtx)
                     .count()
              << " ms" << std::endl;

    delete[] A;
    delete[] B;
    delete[] C;
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
    gpmp::linalg::Mtx mtx;

    std::chrono::steady_clock::time_point gen_start_time =
        std::chrono::steady_clock::now();

    float *A = new float[matrixSize * matrixSize];
    float *B = new float[matrixSize * matrixSize];
    float *C = new float[matrixSize * matrixSize];
    // Initialize A and B matrices with random values
    fill_matrix_random(A, matrixSize, matrixSize);
    fill_matrix_random(B, matrixSize, matrixSize);

    std::chrono::steady_clock::time_point mtx_start_time =
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

    std::cout << "Generating random matrices (ARRAYS) - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     mtx_start_time - gen_start_time)
                     .count()
              << " ms" << std::endl;

    std::cout << "mtx add using Fortran subroutine & flattened matrices: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - mtx_start_time)
                     .count()
              << " ms" << std::endl;

    delete[] A;
    delete[] B;
    delete[] C;
}

int main() {
    run_mtx_add();

    run_mtx_add_flt();

    run_mtx_add_doub();

    run_mtx_add_arr();

    mtx_add_f90();
    return 0;
}
