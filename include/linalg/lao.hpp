/**
 * @ file
 *
 * Definitions for Matrix and Vector operations
 */

#ifndef LAOPS_H
#define LAOPS_H

#include <stdio.h>
#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
#include <tuple>
#include <functional>
#include <random>


namespace mtpk {

/**
 * @brief Operations related to Vectors and Scalars
 */
class Vectors {
    std::vector<int> x;
    std::vector<int> y;


    public:
        /*
         * vectors of the same dimension size are just scalars as they only 
         * contain magnitude. vectors contain both magnitude + direction
         */
        // function to add two 1D vectors
        // template <typename T>
        //float scalar_add();
        // function to subtract two 1D vectors
        //float scalar_sub();
        // function to multiply two 1D vectors
        //float scalar_mult();
        int add(int a, int b);
};

/**
 * @brief Matrix and Scalar operations
 */
template<typename Type>
class Matrix {
    size_t cols;
    size_t rows;

    public:
        std::vector<Type> data;
        std::tuple<size_t, size_t> dim;
        
        int num = rows * cols;
        
        /**
         * @brief Matrix Class constructor initializing empty vector
         *
         * @param[in] rows : size of rows
         * @param[in] cols : size of columns 
         */
        Matrix(size_t rows, size_t cols) {
            // initialize an empty vector for storage
            data.resize(cols * rows, Type());
            dim = {rows, cols};
        }
        Matrix() : cols(0), rows(0), data({}) {dim = {rows, cols};};

        
        /**
         * @brief Overload operator
         *
         * @param[in] row : size of rows
         * @param[in] col : size of columns 
         */
        Type& operator()(size_t row, size_t col) {
            assert(0 <= row && row < rows);
            assert(0 <= col && col < cols);

            return data[row * cols + col];
        }

        /**
         * @brief Matrix Multiplication
         *
         * @param[in] 
         *
         * @todo optimize this with threading
         */
        Matrix mult(Matrix &target) {
            assert(cols == target.rows);
            Matrix res(rows, target.cols);

            for (size_t r = 0; res.rows; ++r) {
                for (size_t c = 0; res.cols; ++c) {
                    for (size_t n = 0; n < target.rows; ++n) {
                        res(r, c) += (*this)(r, n) * target();
                    }
                }
            }
            return res;
        }

        /*
         * Multiply scalars
         */
        Matrix scalar_mult(Type scalar) {
            Matrix res((*this));
            
            for (size_t r = 0; r < res.rows; ++r) {
                for (size_t c = 0; c < res.cols; ++c) {
                    res(r, c) = scalar * (*this)(r, c);
                }
            }
            return res;
        }

        /*
         * Multiply by the element
         */
        Matrix mult_elem(Matrix &target) {
            assert(dim == target.dim);
            Matrix res((*this));

            for (size_t r = 0; r < res.rows; ++r) {
                for (size_t c = 0; c < res.cols ; ++c) {
                    res(r, c) = target(r, c) * (*this)(r, c);
                }
            }
            return res;
        }

        /*
         * Element based squaring of matrices. Method allows for finding 
         * the squared error
         */
        Matrix sqr_err() {
            Matrix res((*this));

            res = mult_elem(res);
            return res;
        }

        /*
         * Matrix Addition
         */
        Matrix add(Matrix &target) {
            assert(dim == target.dim);
            Matrix res(rows, target.cols);

            for (size_t r = 0; r < res.rows; ++r) {
                for (size_t c = 0; c < res.cols; ++c) {
                    res(r, c) = (*this)(r, c) + target(r, c);
                }
            }
            return res;
        }
        Matrix operator+(Matrix &target) {
            return add(target);   
        }

        /*
         * Addition of scalars
         */
        Matrix scalar_add(Type scalar) {
           Matrix res((*this)); 

           for (size_t r = 0; r < rows; ++r) {
                for (size_t c = 0; c < cols; ++c) {
                    res(r, c) = (*this)(r, c) + scalar;
                }
            }
           return res;
        }

        Matrix operator-() {
            Matrix res(rows, cols);
            
            for (size_t r = 0; r < rows; ++r) {
                for (size_t c = 0; c < cols; ++c) {
                    res(r, c) = -(*this)(r, c);
                }
            }
            return res;
        }

        /*
         * Matrix subtraction
         */
        Matrix sub(Matrix &target) {
            Matrix target_neg = -target;
            return add(target_neg);
        }
        Matrix operator-(Matrix &target) {
            return sub(target);
        }

        Matrix<ushort> operator==(Matrix &target) {
            assert(dim == target.dim);
            Matrix<ushort> res(rows, cols);

            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    if ((*this)(r, c) - target(r, c) == 0.)
                        res(r, c) = 1;
                    else
                        res(r, c) = 0;
                }
            }
            return res;
        }
        
        Matrix<ushort> operator!=(Matrix &target) {
            return (!(*this)) == target;
        }

        bool all() {
            int counter{0};

            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    if ((*this)(r, c))
                        counter++;
                }
            }
            return (counter == num);
        }

        /*
         * Transpose the matrix
         */
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

        /*
         * Compute sum of matrix by element
         */
        Matrix sum() {
            Matrix res{1, 1};

            for (size_t r = 0; r < rows; ++r) {
                for (size_t c = 0; c < cols; ++c) {
                    res(0, 0) += (*this)(r, c);
                }
            }
            return res;
        }

        /*
         * Compute sum of matrix by dimension
         */
        Matrix sum(size_t dimension) {
            assert(0 <= dimension && dimension < 2);
            auto res = (dimension = 0) ? Matrix{1, cols} : Matrix{rows, 1};

            if (dimension == 0) {
                for (size_t c = 0; c < cols; ++c) {
                    for (size_t r = 0; r < rows; ++r) {
                        res(0, c) += (*this)(r, c);
                    }
                }
            }
            else {
                for (size_t r = 0; r < rows; ++r) {
                    for (size_t c = 0; c < cols; ++c) {
                        res(r, 0) += (*this)(r, c);
                    }
                }
            }
            return res;
        }
        
        // Compute mean of matrix by elements
        Matrix mean() {
            auto m = Type(num);
            return sum().scalar_mult(1 / m);
        }

        /*
         * Compute mean of matrix by dimension
         */ 
        Matrix mean(size_t dimension) {
            auto m = (dimension == 0) ? Type(rows) : Type(cols);
            return sum().scalar_mult(1 / m);
        }

        /*
         * Concatenate two given matrices
         */
        Matrix concatenate(Matrix target, size_t dimension) {
            (dimension == 0) ? assert(rows == target.rows) : 
                                assert(cols == target.cols);

            auto res = (dimension == 0) ? Matrix{rows + target.rows, cols} :
                                        Matrix{rows, cols + target.cols};

            // copy self
            for (size_t r = 0; r < rows; ++r) {
                for (size_t c = 0; c < cols; ++c) {
                    res(r, c) = (*this)(r, c);
                }
            }

            // copy target
            if (dimension == 0) {
                for (size_t r = 0; r < target.rows; ++r) {
                    for (size_t c = 0; c < cols; ++c) {
                        res(r + rows, c) = target(r, c);
                    }
                }
            } 
            else {
                for (size_t r = 0; r < rows; ++r) {
                    for (size_t c = 0; c < target.cols; ++c) {
                        res(r, c + cols) = target(r, c);
                    }
                }
            }
            return res;
        }

        Matrix diag() {
            assert((rows == 1 || cols == 1) || (rows == cols));

            if (rows == 1 || cols == 1) {
                Matrix res{std::max(rows, cols), std::max(rows, cols)};
                for (size_t i = 0; i < rows; ++i)
                    res(i, i) = (*this)(i, 0);
                return res;
            } 
            else {
                assert(rows == cols);
                Matrix res{rows, 1};
                for (size_t i = 0; i < rows; ++i)
                    res(i, 0) = (*this)(i, i);
                return res;
            }
        }

        Matrix apply_func(const std::function<Type(const Type &)> &function) {
            Matrix res((*this));
            
            for (size_t r = 0; r < rows; ++r) {
                for (size_t c = 0; c < cols; ++c) {
                    res(r, c) = function((*this)(r, c));
                }
            }
            return res;
        }

        void print_mtx() {
            for (size_t r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    std::cout << (*this)(r, c) << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        void fill_index(Type val) {
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
        
    }

};



} // namespace 

#endif

