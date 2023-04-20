#include <chrono>
#include <cstdlib>
#include <ctime>
#include <emmintrin.h>
#include <immintrin.h>
#include <iostream>
#include <random>

const int N = 12;
// const int N = 1000;

void multiply_matrices(float A[N][N], float B[N][N], float C[N][N]) {
    auto start = std::chrono::high_resolution_clock::now();

    /*
    __m128 row, col, res;
    float tmp[N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Load a row from the first matrix into a vector
            row = _mm_load_ps(&A[i][0]);

            // Load a column from the second matrix into a vector
            col = _mm_set_ps(B[0][j], B[1][j], B[2][j], B[3][j]);

            // Multiply the row and column vectors
            res = _mm_mul_ps(row, col);

            // Sum the four values in the result vector
            _mm_store_ps(tmp, res);
            C[i][j] = tmp[0] + tmp[1] + tmp[2] + tmp[3];
        }
    }*/
    __m128 row, col, res;
    float tmp[N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Load a row from the first matrix into a vector
            row = _mm_load_ps(&A[i][0]);

            // Load a column from the second matrix into a vector
            col = _mm_set_ps(B[3][j], B[2][j], B[1][j], B[0][j]);

            // Multiply the row and column vectors
            res = _mm_mul_ps(row, col);

            // Sum the four values in the result vector
            _mm_store_ps(tmp, res);
            C[i][j] = tmp[0] + tmp[1] + tmp[2] + tmp[3];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::nano> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " ns\n";
}

void multiply_matrices_std(float A[N][N], float B[N][N], float C[N][N]) {
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            C[i][j] = A[i][0] * B[0][j];
            for (size_t k = 1; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }   

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::nano> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " ns\n";
}


void multiply_matrices_std(float A[N][N], float B[N][N], float C[N][N]) {
    auto start = std::chrono::high_resolution_clock::now();

    using V = Vector<T>;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; j += V::size()) {
            V c_ij = A[i][0] * V(&B[0][j], Aligned);
            for (size_t k = 1; k < N; ++k) {
                c_ij += A[i][k] * V(&B[k][j], Aligned);
            }
            c_ij.store(&C[i][j], Aligned);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::nano> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " ns\n";
}

int main() {

    /*
        float A[N][N] = {{1, 2, 3, 4},
                         {5, 6, 7, 8},
                         {9, 10, 11, 12},
                         {13, 14, 15, 16}};

        float B[N][N] = {{16, 15, 14, 13},
                         {12, 11, 10, 9},
                         {8, 7, 6, 5},
                         {4, 3, 2, 1}};
    */
    float A[N][N] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24},
        {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36},
        {37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48},
        {49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60},
        {61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72},
        {73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84},
        {85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96},
        {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108},
        {109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120},
        {121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132},
        {133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144}};

    float B[N][N] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24},
        {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36},
        {37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48},
        {49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60},
        {61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72},
        {73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84},
        {85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96},
        {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108},
        {109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120},
        {121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132},
        {133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144}};

    float C[N][N];

    /*(std::srand(std::time(nullptr)); // seed the random number generator

        float A[N][N], B[N][N];

        // Fill the arrays with random values
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = static_cast<float>(std::rand()) /
       static_cast<float>(RAND_MAX) * 10.0f; B[i][j] =
       static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 10.0f;
            }
        }

        float C[N][N];
    */

    multiply_matrices(A, B, C);

    // Print the result matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    float Z[N][N];

    multiply_matrices_std(A, B, Z);

    // Print the result matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << Z[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
