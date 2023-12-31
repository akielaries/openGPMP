/* Defining linear algebra methods/classes for python swig process
*/

%module linalg

%{
#include "../../include/linalg/mtx.hpp"
using namespace gpmp;
%}

%include "std_string.i"
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>

%nodefaultctor;

%include "../../include/linalg/mtx.hpp"

// Forward declaration of the C++ class
%{
#include "../../include/linalg/mtx.hpp"
%}

namespace gpmp {
namespace linalg {
    class Mtx;
}
}

%include "../../include/linalg/mtx.hpp"

// Extend the Mtx class to provide a unified interface for overloaded methods
%extend gpmp::linalg::Mtx {

    void mtx_add(int8_t *A, int8_t *B, int8_t *C, int rows, int cols) {
        $self->mtx_add(A, B, C, rows, cols);
    }

    void mtx_add(int16_t *A, int16_t *B, int16_t *C, int rows, int cols) {
        $self->mtx_add(A, B, C, rows, cols);
    }

    void mtx_add(int *A, int *B, int *C, int rows, int cols) {
        $self->mtx_add(A, B, C, rows, cols);
    }
    void mtx_add(const double *A, const double *B, double *C, int rows, int cols) {
        $self->mtx_add(A, B, C, rows, cols);
    }

    void mtx_add(const std::vector<std::vector<int>> &A,
                 const std::vector<std::vector<int>> &B,
                 std::vector<std::vector<int>> &C) {
        $self->mtx_add(A, B, C);
    }

    void mtx_add(const std::vector<std::vector<double>> &A,
                 const std::vector<std::vector<double>> &B,
                 std::vector<std::vector<double>> &C) {
        $self->mtx_add(A, B, C);
    }

    void mtx_add(const std::vector<std::vector<float>> &A,
                 const std::vector<std::vector<float>> &B,
                 std::vector<std::vector<float>> &C) {
        $self->mtx_add(A, B, C);
    }

    void mtx_sub(const std::vector<std::vector<int>> &A,
                 const std::vector<std::vector<int>> &B,
                 std::vector<std::vector<int>> &C) {
        $self->mtx_sub(A, B, C);
    }

    void mtx_sub(const std::vector<std::vector<double>> &A,
                 const std::vector<std::vector<double>> &B,
                 std::vector<std::vector<double>> &C) {
        $self->mtx_sub(A, B, C);
    }

    void mtx_mult(const std::vector<std::vector<int>> &A,
                  const std::vector<std::vector<int>> &B,
                  std::vector<std::vector<int>> &C) {
        $self->mtx_mult(A, B, C);
    }

    void mtx_mult(const std::vector<std::vector<double>> &A,
                  const std::vector<std::vector<double>> &B,
                  std::vector<std::vector<double>> &C) {
        $self->mtx_mult(A, B, C);
    }

    void mtx_tpose(std::vector<std::vector<int>> &matrix) {
        $self->mtx_tpose(matrix);
    }

    void mtx_tpose(std::vector<std::vector<double>> &matrix) {
        $self->mtx_tpose(matrix);
    }

    void std_mtx_add(const int *A, const int *B, int *C, int rows, int cols) {
        $self->std_mtx_add(A, B, C, rows, cols);
    }

    void std_mtx_add(const std::vector<int> &A,
                     const std::vector<int> &B,
                     std::vector<int> &C) {
        $self->std_mtx_add(A, B, C);
    }

    void std_mtx_add(const std::vector<std::vector<int>> &A,
                     const std::vector<std::vector<int>> &B,
                     std::vector<std::vector<int>> &C) {
        $self->std_mtx_add(A, B, C);
    }

    void std_mtx_add(const double *A, const double *B, double *C, int rows, int cols) {
        $self->std_mtx_add(A, B, C, rows, cols);
    }

    void std_mtx_add(const std::vector<double> &A,
                     const std::vector<double> &B,
                     std::vector<double> &C) {
        $self->std_mtx_add(A, B, C);
    }

    void std_mtx_add(const std::vector<std::vector<double>> &A,
                     const std::vector<std::vector<double>> &B,
                     std::vector<std::vector<double>> &C) {
        $self->std_mtx_add(A, B, C);
    }
}

