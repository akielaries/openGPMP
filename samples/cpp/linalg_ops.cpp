/* TESTING BASIC LINEAR ALGEBRA OPERATIONS
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
//#include <openMTPK/linalg.hpp>
#include "../../include/linalg/vectors.hpp"
#include "../../include/linalg/matrix.hpp"


int main() {
    // declaring an object for the Vectors class is permitted
    mtpk::Vectors v;
    std::cout << "MATRIX/VECTOR OPERATIONS EXAMPLE" << std::endl;

    int x = v.add(1, 3);

    std::cout << "Sum = " << x << std::endl;

    // declaring matrix with random floats
    std::cout << "Creating 2x2 matrix of random floats" << "\n"; 
    auto MAT1 = mtpk::mtx<float>::randn(2, 2);
    MAT1.print_shape();
    MAT1.print_mtx();

    // declare a matrix of zeros with 3 x 5 dimensions
    std::cout << "Creating 3x5 matrix of 0's" << "\n"; 
    auto MAT2 = mtpk::Matrix<float>(3, 5);
    MAT2.print_shape();
    MAT2.print_mtx();

    // another method to declare a matrix of zeros with 8 x 9 dimensions
    std::cout << "Creating 8x9 matrix of 0's" << "\n"; 
    auto MAT3 = mtpk::mtx<int>::zeros(8, 9);
    MAT3.print_shape();
    MAT3.print_mtx();

    // declare a matrix 
    // auto MAT4 = mtpk::Matrix<float>();

    // MAT4.print_shape();
    // MAT4.print_mtx();

    return 0;
}

