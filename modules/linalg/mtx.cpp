#include <iostream>
#include <chrono>
#include <vector>
#include <cassert>
#include <random>
#include <cstdint>

void mult();
void add();

extern "C" {
  void mtx_add_(double* a, double* b, double* c);//, int64_t* nrows, int64_t* ncols);
  //void mtx_mult_(double* a, double* b, double* c, int64_t* nrows, int64_t* ncols);
}

int main() {
    
    add();
    mult();
    return 0;
}

void mult() {

    int i;
}

void add() {
    int64_t rows = 3;
    int64_t cols = 3;

    // Create variables a and b as vectors of vectors
    std::vector<std::vector<double>> a(rows, std::vector<double>(cols));
    std::vector<std::vector<double>> b(rows, std::vector<double>(cols));
    std::vector<std::vector<double>> c(rows, std::vector<double>(cols));

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
    std::vector<double> a_flat(rows * cols);
    std::vector<double> b_flat(rows * cols);
    std::vector<double> c_flat(rows * cols);

    for (int64_t i = 0; i < rows; ++i) {
        for (int64_t j = 0; j < cols; ++j) {
            a_flat[i * cols + j] = a[i][j];
            b_flat[i * cols + j] = b[i][j];
            c_flat.push_back(0.0f);
        }
    }

    std::chrono::steady_clock::time_point start_time =
        std::chrono::steady_clock::now();

  mtx_add_(a_flat.data(), b_flat.data(), c_flat.data());//, &nrows, &ncols);
    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    std::cout << "Time elapsed: "
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     end_time - start_time)
                     .count()
              << " microseconds" << std::endl;
  // Convert result back to matrix format
  for (int64_t i = 0; i < rows; ++i) {
    for (int64_t j = 0; j < cols; ++j) {
      c[i][j] = c_flat[i * cols + j];
    }
  }

  // Display matrices
  std::cout << "Matrix A:" << std::endl;
  for (int64_t i = 0; i < rows; ++i) {
    for (int64_t j = 0; j < cols; ++j) {
      std::cout << a[i][j] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "Matrix B:" << std::endl;
  for (int64_t i = 0; i < rows; ++i) {
    for (int64_t j = 0; j < cols; ++j) {
      std::cout << b[i][j] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "Matrix C (A + B):" << std::endl;
  for (int64_t i = 0; i < rows; ++i) {
    for (int64_t j = 0; j < cols; ++j) {
      std::cout << c[i][j] << " ";
    }
    std::cout << std::endl;
  }

}

