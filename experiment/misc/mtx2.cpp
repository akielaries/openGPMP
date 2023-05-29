#include <immintrin.h> // For Intel intrinsics (SIMD instructions)
#include <iostream>
#include <thread>
#include <vector>

class Matrix {

  public:
    int rows;
    int cols;
    std::vector<float> data;

    // Constructor
    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows * cols) {
    }

    // Element access
    float &operator()(int row, int col) {
        return data[row * cols + col];
    }

    // Matrix addition
    Matrix operator+(const Matrix &other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; i++) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // Matrix multiplication
    Matrix operator*(const Matrix &other) const {
        Matrix result(rows, other.cols);

        // Perform matrix multiplication in parallel using threading
        std::vector<std::thread> threads;
        int numThreads = std::thread::hardware_concurrency();
        int chunkSize = result.rows / numThreads;

        for (int t = 0; t < numThreads; t++) {
            threads.emplace_back([&, t]() {
                for (int i = t * chunkSize; i < (t + 1) * chunkSize; i++) {
                    for (int j = 0; j < result.cols; j++) {
                        __m256 sum = _mm256_setzero_ps();
                        for (int k = 0; k < cols; k += 8) {
                            __m256 a = _mm256_load_ps(&data[i * cols + k]);
                            __m256 b =
                                _mm256_set1_ps(other.data[k * other.cols + j]);
                            sum = _mm256_add_ps(sum, _mm256_mul_ps(a, b));
                        }
                        result(i, j) = sum[0] + sum[1] + sum[2] + sum[3] +
                                       sum[4] + sum[5] + sum[6] + sum[7];
                    }
                }
            });
        }

        for (auto &thread : threads) {
            thread.join();
        }

        return result;
    }
};

int main() {
    Matrix A(3, 2);
    Matrix B(2, 4);

    // Initialize matrices A and B
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            A(i, j) = i + j + 1;
        }
    }

    for (int i = 0; i < B.rows; i++) {
        for (int j = 0; j < B.cols; j++) {
            B(i, j) = i * j + 2;
        }
    }

    // Perform matrix multiplication
    Matrix C = A * B;

    // Print matrix A
    std::cout << "Matrix A:" << std::endl;
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            std::cout << A(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Print matrix B
    std::cout << "Matrix B:" << std::endl;
    for (int i = 0; i < B.rows; i++) {
        for (int j = 0; j < B.cols; j++) {
            std::cout << B(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Print the resulting matrix C
    std::cout << "Resulting matrix C:" << std::endl;
    for (int i = 0; i < C.rows; i++) {
        for (int j = 0; j < C.cols; j++) {
            std::cout << C(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
