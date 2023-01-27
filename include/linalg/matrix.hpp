/**
 * @ file
 *
 * Definitions for Matrix and Scalar operations
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

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
 * @class Matrix
 * @brief Matrix and Scalar operations
 */
template<typename Type>
class Matrix {
    size_t cols;
    size_t rows;

    public:
        std::vector<Type> data;
        std::tuple<size_t, size_t> dim;
        
        int64_t num_elements = rows * cols;
        
        /**
         * @brief Matrix Class constructor initializing empty vector
         *
         * @param[in] rows : size of rows
         * @param[in] cols : size of columns 
         */
        Matrix(size_t rows, size_t cols) : 
            cols(cols), rows(rows), data({}) {
            // initialize an empty vector for storage
            data.resize(cols * rows, Type());
            dim = std::make_tuple(rows, cols);
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
                        res(r, c) += (*this)(r, n) * target(n, c);
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
         * Multiply by the element; see Hadamard Product
         */
        Matrix hadamard(Matrix &target) {
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

            res = hadamard(res);
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

        Matrix<unsigned short> operator==(Matrix &target) {
            assert(dim == target.dim);
            Matrix<unsigned short> res(rows, cols);

            for (int64_t r = 0; r < rows; ++r) {
                for (int64_t c = 0; c < cols; ++c) {
                    if ((*this)(r, c) - target(r, c) == 0.)
                        res(r, c) = 1;
                    else
                        res(r, c) = 0;
                }
            }
            return res;
        }
        
        //Matrix<ushort> operator!=(Matrix &target) {
        //    return (!(*this)) == target;
        //}

        bool all() {
            int64_t counter{0};

            for (int64_t r = 0; r < rows; ++r) {
                for (int64_t c = 0; c < cols; ++c) {
                    if ((*this)(r, c))
                        counter++;
                }
            }
            return (counter == num_elements);
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
            auto m = Type(num_elements);
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

        void print_shape() {
            std::cout << "Matrix Size([" << 
                rows << ", " << cols << 
                "])" << std::endl;
        }


        void print_mtx() {
            for (size_t r = 0; r < rows; ++r) {
                for (int64_t c = 0; c < cols; ++c) {
                    std::cout << (*this)(r, c) << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        void fill_index(Type val) {
            for (size_t r = 0; r < rows; ++r) {
                for (int64_t c = 0; c < cols; ++c) {
                    (*this)(r, c) = val;
                }
            }
        }
};

template<typename T>
/**
 * @struct mtx
 * @brief Matrix struct
 */
struct mtx {
    /**
     * @brief Matrix zeros method
     */
    static Matrix<T> zeros(size_t rows, size_t cols) {
        Matrix<T> MTX{rows, cols};
        // fill by index
        MTX.fill_index(T(0));
        return MTX;
    }
    
    static Matrix<T> ones(size_t rows, size_t cols) {
        Matrix<T> MTX{rows, cols};
        MTX.fill_index(T(1));
        return MTX;
    }
    
    static Matrix<T> randn(size_t rows, size_t cols) {
        Matrix<T> MTX{rows, cols};

        std::random_device rd{};
        std::mt19937 gen{rd()};
        T n(MTX.num_elements);
        T stdev{1 / sqrt(n)};
        std::normal_distribution<T> d{0, stdev};

        for (size_t r = 0; r < rows; ++r) {
            for (uint64_t c = 0; c < cols; ++c) {
            MTX(r, c) = d(gen);
            }
        }
        return MTX;
    }
    static Matrix<T> rand(size_t rows, size_t cols) {
        Matrix<T> MTX{rows, cols};

        std::random_device rd{};
        std::mt19937 gen{rd()};
        std::uniform_real_distribution<T> d{0, 1};

        for (size_t r = 0; r < rows; ++r) {
          for (int64_t c = 0; c < cols; ++c) {
            MTX(r, c) = d(gen);
            }
        }
        return MTX;
    }

};

} // namespace 

#endif

