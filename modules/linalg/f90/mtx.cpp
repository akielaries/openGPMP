#include <cassert>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

void mult();
void add();

extern "C" {
void mtx_add_(double *a, double *b, double *c, int64_t *nrows, int64_t *ncols);
void mtx_mult_(float *matrix1, float *matrix2, float *res, int *nrows1,
               int *ncols1, int *ncols2);
}

void matrixMultiply(const std::vector<std::vector<double>> &a,
                    const std::vector<std::vector<double>> &b,
                    std::vector<std::vector<double>> &c) {
    assert(a.size() == b.size());
    assert(a[0].size() == b[0].size());

    int64_t nrows = a.size();
    int64_t ncols = a[0].size();

    for (int64_t i = 0; i < nrows; ++i) {
        for (int64_t j = 0; j < ncols; ++j) {
            c[i][j] = 0.0;
            for (int64_t k = 0; k < ncols; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main() {

    add();
    mult();
    return 0;
}

void mult() {
    int nrows1 = 2;
    int ncols1 = 3;
    int ncols2 = 2;

    float matrix1[nrows1][ncols1] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};

    float matrix2[ncols1][ncols2] = {{7.0, 8.0}, {9.0, 10.0}, {11.0, 12.0}};

    float result[nrows1][ncols2];

    // Call the Fortran subroutine
    mtx_mult_(&matrix1[0][0], &matrix2[0][0], &result[0][0], &nrows1, &ncols1,
              &ncols2);

    // Print the result
    for (int i = 0; i < nrows1; ++i) {
        for (int j = 0; j < ncols2; ++j) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void add() {
    int64_t rows = 2;
    int64_t cols = 2;

    // Create variables a and b as vectors of vectors
    std::vector<std::vector<double>> a(rows, std::vector<double>(cols));
    std::vector<std::vector<double>> b(rows, std::vector<double>(cols));

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    // Populate matrix a
    for (int64_t i = 0; i < rows; ++i) {
        for (int64_t j = 0; j < cols; ++j) {
            a[i][j] = dis(gen);
        }
    }

    // Populate matrix b
    for (int64_t i = 0; i < rows; ++i) {
        for (int64_t j = 0; j < cols; ++j) {
            b[i][j] = dis(gen);
        }
    }

    assert(a.size() == b.size());
    assert(a[0].size() == b[0].size());

    int64_t nrows = a.size();
    int64_t ncols = a[0].size();

    std::vector<std::vector<double>> c(nrows, std::vector<double>(ncols));

    // Convert matrices to flat arrays
    std::vector<double> a_flat, b_flat, c_flat;
    for (int64_t i = 0; i < nrows; ++i) {
        for (int64_t j = 0; j < ncols; ++j) {
            a_flat.push_back(a[i][j]);
            b_flat.push_back(b[i][j]);
            c_flat.push_back(0.0); // Initialize c_flat with zeros
        }
    }

    std::chrono::steady_clock::time_point start_time =
        std::chrono::steady_clock::now();

    matrixMultiply(a, b, c);

    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    std::cout << "Time elapsed CPP: "
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     end_time - start_time)
                     .count()
              << " microseconds" << std::endl;
    std::cout << "A x B" << std::endl;
    for (int64_t i = 0; i < rows; ++i) {
        for (int64_t j = 0; j < cols; ++j) {
            std::cout << c[i][j] << " ";
        }
        std::cout << std::endl;
    }

    start_time = std::chrono::steady_clock::now();

    mtx_add_(a_flat.data(), b_flat.data(), c_flat.data(), &nrows, &ncols);
    end_time = std::chrono::steady_clock::now();

    std::cout << "Time elapsed FORTRAN: "
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     end_time - start_time)
                     .count()
              << " microseconds" << std::endl;
    // Convert result back to matrix format
    for (int64_t i = 0; i < nrows; ++i) {
        for (int64_t j = 0; j < ncols; ++j) {
            c[i][j] = c_flat[i * ncols + j];
        }
    }

    // Display matrices
    std::cout << "Matrix A:" << std::endl;
    for (int64_t i = 0; i < nrows; ++i) {
        for (int64_t j = 0; j < ncols; ++j) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix B:" << std::endl;
    for (int64_t i = 0; i < nrows; ++i) {
        for (int64_t j = 0; j < ncols; ++j) {
            std::cout << b[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix C (A + B):" << std::endl;
    for (int64_t i = 0; i < nrows; ++i) {
        for (int64_t j = 0; j < ncols; ++j) {
            std::cout << c[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
