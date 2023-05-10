#include <iostream>
#include <vector>
#include <cassert>

extern "C" {
  void matrix_addition_(float* a, float* b, float* c, int* nrows, int* ncols);
}

int main() {

  std::vector<std::vector<float>> a = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };

  std::vector<std::vector<float>> b = {
    {9, 8, 7},
    {6, 5, 4},
    {3, 5, 2}
  };

  assert(a.size() == b.size());
  assert(a[0].size() == b[0].size());

  int nrows = a.size();
  int ncols = a[0].size();

  std::vector<std::vector<float>> c(nrows, std::vector<float>(ncols));

  // Convert matrices to flat arrays
  std::vector<float> a_flat, b_flat, c_flat;
  for (int i = 0; i < nrows; ++i) {
    for (int j = 0; j < ncols; ++j) {
      a_flat.push_back(a[i][j]);
      b_flat.push_back(b[i][j]);
      c_flat.push_back(0.0f);  // Initialize c_flat with zeros
    }
  }

  matrix_addition_(a_flat.data(), b_flat.data(), c_flat.data(), &nrows, &ncols);

  // Convert result back to matrix format
  for (int i = 0; i < nrows; ++i) {
    for (int j = 0; j < ncols; ++j) {
      c[i][j] = c_flat[i * ncols + j];
    }
  }

  // Display matrices
  std::cout << "Matrix A:" << std::endl;
  for (int i = 0; i < nrows; ++i) {
    for (int j = 0; j < ncols; ++j) {
      std::cout << a[i][j] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "Matrix B:" << std::endl;
  for (int i = 0; i < nrows; ++i) {
    for (int j = 0; j < ncols; ++j) {
      std::cout << b[i][j] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "Matrix C (A + B):" << std::endl;
  for (int i = 0; i < nrows; ++i) {
    for (int j = 0; j < ncols; ++j) {
      std::cout << c[i][j] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}

