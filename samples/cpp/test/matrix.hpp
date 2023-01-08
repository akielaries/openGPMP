//
// Created by Lyndon Duong on 12/21/21.
//

#pragma once
#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
#include <tuple>
#include <functional>
#include <random>

namespace mtpk {
template<typename Type>
class Matrix {

  size_t cols;
  size_t rows;

 public:
  std::vector<Type> data;
  std::tuple<size_t, size_t> shape;
  int numel = rows * cols;

  Matrix(size_t rows, size_t cols)
      : cols(cols), rows(rows), data({}) {
    data.resize(cols * rows, Type());
    shape = std::make_tuple(rows, cols);
  }
  Matrix() : cols(0), rows(0), data({}) { shape = {rows, cols}; };

  Type &operator()(size_t row, size_t col) {
    assert (0 <= row && row < rows);
    assert (0 <= col && col < cols);
    return data[row * cols + col];
  }

  Matrix matmul(Matrix &target) {
    assert(cols == target.rows);
    Matrix output(rows, target.cols);

    for (size_t r = 0; r < output.rows; ++r) {
      for (size_t c = 0; c < output.cols; ++c) {
        for (size_t k = 0; k < target.rows; ++k)
          output(r, c) += (*this)(r, k) * target(k, c);
      }
    }
    return output;
  }

  Matrix multiply_scalar(Type scalar) {
    Matrix output((*this));
    for (size_t r = 0; r < output.rows; ++r) {
      for (size_t c = 0; c < output.cols; ++c) {
        output(r, c) = scalar * (*this)(r, c);
      }
    }
    return output;
  }

  Matrix multiply_elementwise(Matrix &target) {
    assert(shape == target.shape);
    Matrix output((*this));
    for (size_t r = 0; r < output.rows; ++r) {
      for (size_t c = 0; c < output.cols; ++c) {
        output(r, c) = target(r, c) * (*this)(r, c);
      }
    }
    return output;
  }

  Matrix square() {
    Matrix output((*this));
    output = multiply_elementwise(output);
    return output;
  }

  Matrix add(Matrix &target) {
    assert(shape == target.shape);
    Matrix output(rows, target.cols);

    for (size_t r = 0; r < output.rows; ++r) {
      for (size_t c = 0; c < output.cols; ++c) {
        output(r, c) = (*this)(r, c) + target(r, c);
      }
    }
    return output;
  }
  Matrix operator+(Matrix &target) {
    return add(target);
  }

  Matrix add_scalar(Type scalar) {
    Matrix output(*(this));
    for (size_t r = 0; r < rows; ++r) {
      for (size_t c = 0; c < cols; ++c) {
        output(r, c) = (*this)(r, c) + scalar;
      }
    }
    return output;
  }

  Matrix operator-() {
    Matrix output(rows, cols);
    for (size_t r = 0; r < rows; ++r) {
      for (size_t c = 0; c < cols; ++c) {
        output(r, c) = -(*this)(r, c);
      }
    }
    return output;
  }

  Matrix sub(Matrix &target) {
    Matrix neg_target = -target;
    return add(neg_target);
  }
  Matrix operator-(Matrix &target) {
    return sub(target);
  }

  Matrix<ushort> operator==(Matrix &target) {
    assert(shape == target.shape);
    Matrix<ushort> output(rows, cols);

    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        if ((*this)(r, c) - target(r, c) == 0.)
          output(r, c) = 1;
        else
          output(r, c) = 0;
      }
    }
    return output;
  }

  Matrix<ushort> operator!=(Matrix &target) {
    return !(*this) == target;
  }

  bool all() {
    int counter{0};
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        if ((*this)(r, c))
          counter++;
      }
    }
    return (counter == numel);
  }

  Matrix transpose() {
    size_t new_rows{cols}, new_cols{rows};
    Matrix transposed(new_rows, new_cols);

    for (size_t r = 0; r < new_rows; ++r) {
      for (size_t c = 0; c < new_cols; ++c) {
        transposed(r, c) = (*this)(c, r);
      }
    }
    return transposed;
  }
  Matrix T() {
    return (*this).transpose();
  }

  // sum all elements
  Matrix sum() {
    Matrix output{1, 1};
    for (size_t r = 0; r < rows; ++r) {
      for (size_t c = 0; c < cols; ++c) {
        output(0, 0) += (*this)(r, c);
      }
    }
    return output;
  }

  // sum across dim
  Matrix sum(size_t dim) {
    assert (0 <= dim && dim < 2);
    auto output = (dim == 0) ? Matrix{1, cols} : Matrix{rows, 1};

    if (dim == 0) {
      for (size_t c = 0; c < cols; ++c)
        for (size_t r = 0; r < rows; ++r)
          output(0, c) += (*this)(r, c);
    } else {
      for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
          output(r, 0) += (*this)(r, c);
    }
    return output;
  }

  // mean of all elements
  Matrix mean() {
    auto n = Type(numel);
    return sum().multiply_scalar(1 / n);
  }

  // mean across dim
  Matrix mean(size_t dim) {
    auto n = (dim == 0) ? Type(rows) : Type(cols);
    return sum().multiply_scalar(1 / n);
  }

  // concatenate two matrices
  Matrix cat(Matrix target, size_t dim) {
    (dim == 0) ? assert(rows == target.rows) : assert(cols == target.cols);
    auto output = (dim == 0) ? Matrix{rows + target.rows, cols} : Matrix{rows, cols + target.cols};

    // copy self
    for (size_t r = 0; r < rows; ++r)
      for (size_t c = 0; c < cols; ++c)
        output(r, c) = (*this)(r, c);

    // copy target
    if (dim == 0) {
      for (size_t r = 0; r < target.rows; ++r)
        for (size_t c = 0; c < cols; ++c)
          output(r + rows, c) = target(r, c);
    } else {
      for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < target.cols; ++c)
          output(r, c + cols) = target(r, c);
    }
    return output;
  }

  Matrix diag() {
    assert((rows == 1 || cols == 1) || (rows == cols));
    if (rows == 1 || cols == 1) {
      Matrix output{std::max(rows, cols), std::max(rows, cols)};
      for (size_t i = 0; i < rows; ++i)
        output(i, i) = (*this)(i, 0);
      return output;
    } else {
      assert(rows == cols);
      Matrix output{rows, 1};
      for (size_t i = 0; i < rows; ++i)
        output(i, 0) = (*this)(i, i);
      return output;
    }
  }

  Matrix apply_function(const std::function<Type(const Type &)> &function) {
    Matrix output((*this));
    for (size_t r = 0; r < rows; ++r) {
      for (size_t c = 0; c < cols; ++c) {
        output(r, c) = function((*this)(r, c));
      }
    }
    return output;
  }

  void print_shape() {
    std::cout << "Matrix Size([" << rows << ", " << cols << "])" << std::endl;
  }

  void print() {
    for (size_t r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        std::cout << (*this)(r, c) << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  // in-place fill with single value
  void fill_(Type val) {
    for (size_t r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        (*this)(r, c) = val;
      }
    }
  }

};

template<typename T>
struct mtx {
  static Matrix<T> zeros(size_t rows, size_t cols) {
    Matrix<T> M{rows, cols};
    M.fill_(T(0));
    return M;
  }

  static Matrix<T> ones(size_t rows, size_t cols) {
    Matrix<T> M{rows, cols};
    M.fill_(T(1));
    return M;
  }

  static Matrix<T> randn(size_t rows, size_t cols) {
    Matrix<T> M{rows, cols};

    std::random_device rd{};
    std::mt19937 gen{rd()};
    T n(M.numel);
    T stdev{1 / sqrt(n)};
    std::normal_distribution<T> d{0, stdev};

    for (size_t r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        M(r, c) = d(gen);
      }
    }
    return M;
  }

  static Matrix<T> rand(size_t rows, size_t cols) {
    Matrix<T> M{rows, cols};

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<T> d{0, 1};

    for (size_t r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        M(r, c) = d(gen);
      }
    }
    return M;
  }

};

}

