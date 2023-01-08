/*
 * Linear Algebra Sample File
 *
 * test driver program on the implementations for some basic Linear Algebra
 * operations. 
 *
 * For operations on vectors (addition, subtraction) the sizes of the vectors
 * must be of equal length. This is to follow traditional rules in 
 * Linear Algebra vector operations.
 */
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cassert>

#include <openMTPK/linalg.hpp>
//#include "../../include/linalg/vectors.hpp"
//#include "../../include/linalg/matrix.hpp"


int main() {
    // declaring an object for the Vectors class is permitted
    mtpk::Vectors v;
    std::cout << "MATRIX/VECTOR OPERATIONS EXAMPLE\n" << std::endl;

    int x = v.add(1, 3);

    std::cout << "Sum = " << x << "\n\n";

    // declaring matrix with random negative floats
    std::cout << "Creating 2x2 matrix (MAT1) of random negative floats\n"; 
    auto matrix_neg = mtpk::mtx<float>::randn(2, 2);
    matrix_neg.print_shape();
    matrix_neg.print_mtx();

    // declaring matrix with random positive floats
    std::cout << "Creating 2x2 matrix (MAT1) of random positive floats\n"; 
    auto matrix_pos = mtpk::mtx<float>::rand(2, 2);
    matrix_pos.print_shape();
    matrix_pos.print_mtx();

    std::cout << "Multiply each element of the matrix(MAT1) by itself" << "\n";
    (matrix_pos.scalar_mult(2.f)).print_mtx();


    // declare a matrix of zeros with 3 x 5 dimensions
    std::cout << "Creating 3x5 matrix of 0's" << "\n"; 
    auto matrix_zero = mtpk::Matrix<float>(3, 5);
    matrix_zero.print_shape();
    matrix_zero.print_mtx();

    // another method to declare a matrix of zeros with 8 x 9 dimensions
    std::cout << "Creating 8x9 matrix of 0's" << "\n"; 
    auto matrix_zero_2 = mtpk::mtx<int>::zeros(8, 9);
    matrix_zero_2.print_shape();
    matrix_zero_2.print_mtx();

    // declare matrix of ones with 8 x 9 dimensions
    std::cout << "Creating 8x9 matrix of 1's" << "\n"; 
    auto matrix_one = mtpk::mtx<int>::ones(8, 9);
    matrix_one.print_shape();
    matrix_one.print_mtx();

    return 0;
}

