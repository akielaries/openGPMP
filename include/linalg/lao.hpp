/*
 * definitions for basic Linear Algebra operations on vectors and matrix spaces 
 */

#ifndef RMLAOPS_H
#define RMLAOPS_H

#include <stdio.h>
#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
#include <tuple>
#include <functional>
#include <random>


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
            Matrices ret(rows, target.cols);

            for (size_t r = 0; ret.rows; ++r) {
                for (size_t c = 0; ret.cols; ++c) {
                    for (size_t n = 0; n < target.rows; ++n) {
                        ret(r, c) += (*this)(r, n) * target();
                    }
                }
            }
            return ret;
        }

        /*
         * Multiply scalars
         */
        Matrices scalar_mult(Type scalar) {
            Matrices ret((*this));
            
            for (size_t r = 0; r < ret.rows; ++r) {
                for (size_t c = 0; c < ret.cols; ++c) {
                    ret(r, c) = scalar * (*this)(r, c);
                }
            }
            return ret;
        }

        /*
         * Multiply by the element
         */
        Matrices mult_elem(Matrices &target) {
            assert(dim = target.dim);
            Matrices ret((*this));

            for (size_t r = 0; r < ret.rows; ++r) {
                for (size_t c = 0; c < ret.cols ; ++c) {
                    ret(r, c) = target(r, c) * (*this)(r, c);
                }
            }
            return ret;
        }

        Matrices sqr_err() {
            Matrices ret((*this));

            ret = mult_elem(ret);
            return ret;
        }

        Matrices add(Matrices &target) {
            assert(dim == target.dim);
            Matrices ret(rows, target.cols);

            for (size_t r = 0; r < ret.rows; ++r) {
                for (size_t c = 0; c < ret.cols; ++c) {
                    ret(r, c) = (*this)(r, c) + target(r, c);
                }
            }
            return ret;
        }
        Matrices operator+(Matrices &target) {
            return add(target);   
        }

        /*
        Matrices scalar_add(Type scalar) {
            
        }

        Matrices sub()
        */
};

#endif

