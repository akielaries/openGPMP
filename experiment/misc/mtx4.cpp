#include <chrono>
#include <iostream>
#include <random>
#include <vector>

constexpr int matrixSize = 10000;

void matrixAddition_u(const std::vector<std::vector<int>> &A,
                      const std::vector<std::vector<int>> &B,
                      std::vector<std::vector<int>> &C) {
    const int size = A.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; j += 128) { // Unroll by 4 elements
            // Perform matrix addition
            C[i][j] = A[i][j] + B[i][j];
            C[i][j + 1] = A[i][j + 1] + B[i][j + 1];
            C[i][j + 2] = A[i][j + 2] + B[i][j + 2];
            C[i][j + 3] = A[i][j + 3] + B[i][j + 3];
        }
    }
}

int main() {
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
    matrixAddition_u(A, B, C);
    std::chrono::steady_clock::time_point end_time_u =
        std::chrono::steady_clock::now();

    std::cout << "Loop Unrolling - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time_u - start_time_u)
                     .count()
              << " ms" << std::endl;

    return 0;
}
