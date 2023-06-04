// C++ code

#include <iostream>
#include <vector>

extern "C" {
void mtxx_add_(int *A, int *B, int *C, int *size);
}

void matrixAddition(const std::vector<std::vector<int>> &A,
                    const std::vector<std::vector<int>> &B,
                    std::vector<std::vector<int>> &C) {
    int size = A.size();

    std::vector<int> flatA(size * size);
    std::vector<int> flatB(size * size);
    std::vector<int> flatC(size * size);

    // Flatten A and B matrices
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            flatA[i * size + j] = A[i][j];
            flatB[i * size + j] = B[i][j];
        }
    }

    // Call the Fortran subroutine
    mtxx_add_(flatA.data(), flatB.data(), flatC.data(), &size);

    // Unflatten C matrix
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = flatC[i * size + j];
        }
    }
}

int main() {
    std::vector<std::vector<int>> A = {{1, 2}, {3, 4}};
    std::vector<std::vector<int>> B = {{5, 6}, {7, 8}};
    std::vector<std::vector<int>> C(2, std::vector<int>(2));

    matrixAddition(A, B, C);

    // Print the result
    for (const auto &row : C) {
        for (const auto &element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
