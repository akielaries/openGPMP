/*
 * definitions for basic Linear Algebra operations on vectors and matrix spaces 
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


template<typename Type>
class Matrices {
    size_t cols;
    size_t rows;

    public:
        std::vector<Type> data;
        std::tuple<size_t, size_t> dim;
        
        int num = rows * cols;
        
        // constructor
        Matrices(size_t rows, size_t cols) {
            // initialize an empty vector for storage
            data.resize(cols * rows, Type());
            dim = {rows, cols};
        }
        Matrices() : cols(0), rows(0), data({}) {dim = {rows, cols};};

        // overload operator
        Type& operator()(size_t row, size_t col) {
            assert(0 <= row && row < rows);
            assert(0 <= col && col < cols);

            return data[row * cols + col];
        }

        /* Matrix Multiplication
         * TODO: optimize this with threading 
         */
        Matrices mult(Matrices &target) {
            assert(cols == target.rows);
            Matrices res(rows, target.cols);

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
        Matrices scalar_mult(Type scalar) {
            Matrices res((*this));
            
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
        Matrices mult_elem(Matrices &target) {
            assert(dim == target.dim);
            Matrices res((*this));

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
        Matrices sqr_err() {
            Matrices res((*this));

            res = mult_elem(res);
            return res;
        }

        /*
         * Matrix Addition
         */
        Matrices add(Matrices &target) {
            assert(dim == target.dim);
            Matrices res(rows, target.cols);

            for (size_t r = 0; r < res.rows; ++r) {
                for (size_t c = 0; c < res.cols; ++c) {
                    res(r, c) = (*this)(r, c) + target(r, c);
                }
            }
            return res;
        }
        Matrices operator+(Matrices &target) {
            return add(target);   
        }

        /*
         * Addition of scalars
         */
        Matrices scalar_add(Type scalar) {
           Matrices res((*this)); 

           for (size_t r = 0; r < rows; ++r) {
                for (size_t c = 0; c < cols; ++c) {
                    res(r, c) = (*this)(r, c) + scalar;
                }
            }
           return res;
        }

        Matrices operator-() {
            Matrices res(rows, cols);
            
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
        Matrices sub(Matrices &target) {
            Matrices target_neg = -target;
            return add(target_neg);
        }
        Matrices operator-(Matrices &target) {
            return sub(target);
        }

        Matrices<ushort> operator==(Matrices &target) {
            assert(dim == target.dim);
            Matrices<ushort> res(rows, cols);

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
        
        Matrices<ushort> operator!=(Matrices &target) {
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
        Matrices transpose() {
            size_t new_rows{cols}, new_cols{rows};
            Matrices transposed(new_rows, new_cols);

            for (size_t r = 0; r < new_rows; ++r) {
                for (size_t c = 0; c < new_cols; ++c) {
                    transposed(r, c) = (*this)(c, r);
                }
            }
            return transposed;
        }

        Matrices T() {
            return (*this).transpose();
        }

        /*
         * Compute sum of matrix by element
         */
        Matrices sum() {
            Matrices res{1, 1};

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
        Matrices sum(size_t dimension) {
            assert(0 <= dimension && dimension < 2);
            auto res = (dimension = 0) ? Matrices{1, cols} : Matrices{rows, 1};

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
        Matrices mean() {
            auto m = Type(num);
            return sum().scalar_mult(1 / m);
        }

        /*
         * Compute mean of matrix by dimension
         */ 
        Matrices mean(size_t dimension) {
            auto m = (dimension == 0) ? Type(rows) : Type(cols);
            return sum().scalar_mult(1 / m);
        }

        /*
         * Concatenate two given matrices
         */
        Matrices concatenate(Matrices target, size_t dimension) {
            (dimension == 0) ? assert(rows == target.rows) : 
                                assert(cols == target.cols);

            auto res = (dimension == 0) ? Matrices{rows + target.rows, cols} :
                                        Matrices{rows, cols + target.cols};

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

        Matrices diag() {
            assert((rows == 1 || cols == 1) || (rows == cols));

            if (rows == 1 || cols == 1) {
                Matrices res{std::max(rows, cols), std::max(rows, cols)};
                for (size_t i = 0; i < rows; ++i)
                    res(i, i) = (*this)(i, 0);
                return res;
            } 
            else {
                assert(rows == cols);
                Matrices res{rows, 1};
                for (size_t i = 0; i < rows; ++i)
                    res(i, 0) = (*this)(i, i);
                return res;
            }
        }

};
} // namespace 

#endif

