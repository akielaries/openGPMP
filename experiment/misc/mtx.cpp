#include <chrono>
#include <iostream>

const int64_t N = 99999; // Size of the matrix

// Function to create a matrix using the two-dimensional array approach
void createMatrix2D(int64_t matrix[N][N]) {
    for (int64_t i = 0; i < N; i++) {
        for (int64_t j = 0; j < N; j++) {
            matrix[i][j] = i + j; // Assign a value to the element
        }
    }
}

// Function to create a matrix using the linear storage approach
int64_t *createMatrix1D() {
    int64_t *matrix = new int64_t[N * N]; // Allocate memory for the matrix

    for (int64_t i = 0; i < N; i++) {
        for (int64_t j = 0; j < N; j++) {
            int64_t index = i * N + j; // Calculate the one-dimensional index
            matrix[index] = i + j; // Assign a value to the element
        }
    }

    return matrix; // Return the created matrix
}

// Function to access a matrix element using the two-dimensional array approach
int64_t accessElement2D(int64_t matrix[N][N], int64_t row, int64_t col) {
    return matrix[row][col];
}

// Function to access a matrix element using the linear storage approach
int64_t accessElement1D(int64_t *matrix, int64_t row, int64_t col) {
    int64_t index = row * N + col; // Calculate the one-dimensional index
    return matrix[index];
}

int main() {
    int64_t matrix2D[N][N];
    int64_t *matrix1D;

    // Measure the time to create a matrix using the two-dimensional array
    // approach
    std::chrono::steady_clock::time_point start2D = std::chrono::steady_clock::now();

//    createMatrix2D(matrix2D);
    
    std::chrono::steady_clock::time_point end2D =
        std::chrono::steady_clock::now();
    
    std::chrono::duration<long double> time2D = end2D - start2D;

    // Measure the time to create a matrix using the linear storage approach
    std::chrono::steady_clock::time_point start1D =
        std::chrono::steady_clock::now();
    matrix1D = createMatrix1D();
    std::chrono::steady_clock::time_point end1D =
        std::chrono::steady_clock::now();
    std::chrono::duration<long double> time1D = end1D - start1D;

    std::cout
        << "Time to create matrix using the two-dimensional array approach: "
        << time2D.count() << " seconds" << std::endl;
    std::cout << "Time to create matrix using the linear storage approach: "
              << time1D.count() << " seconds" << std::endl;

    // Measure the time to access a matrix element using the two-dimensional
    // array approach
    std::chrono::steady_clock::time_point startAccess2D =
        std::chrono::steady_clock::now();
    int64_t element2D = accessElement2D(matrix2D, 0, 0);
    std::chrono::steady_clock::time_point endAccess2D =
        std::chrono::steady_clock::now();
    std::chrono::duration<long double> timeAccess2D = endAccess2D - startAccess2D;

    // Measure the time to access a matrix element using the linear storage
    // approach
    std::chrono::steady_clock::time_point startAccess1D =
        std::chrono::steady_clock::now();
    int64_t element1D = accessElement1D(matrix1D, 0, 0);
    std::chrono::steady_clock::time_point endAccess1D =
        std::chrono::steady_clock::now();
    std::chrono::duration<long double> timeAccess1D = endAccess1D - startAccess1D;
    std::cout << "Time to access matrix element using the two-dimensional "
                 "array approach: "
              << timeAccess2D.count() << " seconds" << std::endl;
    std::cout
        << "Time to access matrix element using the linear storage approach: "
        << timeAccess1D.count() << " seconds" << std::endl;

    delete[] matrix1D; // Deallocate memory for the linear storage matrix

    return 0;
}
