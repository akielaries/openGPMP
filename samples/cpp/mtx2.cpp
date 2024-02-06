/**
 * Linear Algebra Sample File
 *
 * The Matrix Class is capable of creating both Vectors and Matrices
 * alike
 *
 * BY DEFINITION:
 * A scalar is a single number, like 3, -5, 0.368, etc,
 * A vector is a list of numbers (can be in a row or column),
 *      [ 2 -4 3 ]
 *      OR
 *    _____
 *    | 2 |
 *    | -4|
 *    | 3 |
 *    |___|
 *
 * A matrix is an array of numbers (one or more rows, one or more
 * columns). 3 x 5 3 7 5 8 7 0 4 1 5 5 1 2 0 7 6
 *
 * @example linalg_ops.cpp
 */
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>

#include <openGPMP/linalg.hpp>

using namespace gpmp;

void print_csv() {
    std::ifstream csvFile("data/school_scores.csv");
    std::string line;
    std::vector<std::vector<double>> data;
    while (std::getline(csvFile, line)) {
        std::vector<double> row;
        std::stringstream lineStream(line);
        std::string cell;
        while (std::getline(lineStream, cell, ',')) {
            row.push_back(std::stod(cell));
            std::cout << line;
        }
        data.push_back(row);
    }
    csvFile.close();
    size_t rows = data.size();
    size_t cols = data[0].size();
    gpmp::Matrix<double> mat(rows, cols);

    mat.print_mtx();
}

int main() {
    // declaring an object for the Vectors class is permitted
    gpmp::Vectors v;
    std::cout << "MATRIX/VECTOR OPERATIONS EXAMPLE\n" << std::endl;

    int x = v.add(1, 3);

    std::cout << "Sum = " << x << "\n\n";

    gpmp::Matrix<int> mat(3, 4);
    mat.print_mtx();

    std::tuple<Matrix<double>, Matrix<double>> matrices =
        std::make_tuple(Matrix<double>(5, 3), Matrix<double>(6, 4));

    std::get<0>(matrices).print_mtx();
    std::get<1>(matrices).print_mtx();

    std::cout << "PRINT CSV AS MATRIX \n";
    // print_csv();

    // declaring matrix with random negative decimals
    std::cout << "Creating 2x2 matrix of random negative floats\n";
    auto matrix_neg = gpmp::mtx<double>::randn(2, 2);
    matrix_neg.print_shape();
    matrix_neg.print_mtx();

    // declaring matrix with random positive decimals
    std::cout << "Creating 2x2 matrix of random positive floats\n";
    auto matrix_pos = gpmp::mtx<double>::rand(2, 2);
    matrix_pos.print_shape();
    matrix_pos.print_mtx();

    std::cout << "Transpose the MATRIX \n";
    (matrix_pos.transpose()).print_mtx();
    // multiply each element of matrix_pos by a number
    std::cout << "Multiply each element of the matrix by a number"
              << "\n";
    std::cout << "By 2\n";
    (matrix_pos.scalar_mult(2.f)).print_mtx();
    std::cout << "By 3\n";
    (matrix_pos.scalar_mult(3.f)).print_mtx();

    // multiply each element of matrix_pos by itself
    std::cout << "Multiply each element of the matrix by itself"
              << "\n";
    (matrix_pos.hadamard(matrix_pos)).print_mtx();

    // declare a matrix of zeros with 3 x 5 dimensions
    std::cout << "Creating 3x5 matrix of 0's"
              << "\n";
    auto matrix_zero = gpmp::Matrix<double>(3, 5);
    matrix_zero.print_shape();
    matrix_zero.print_mtx();

    // another method to declare a matrix of zeros with 8 x 9
    // dimensions
    std::cout << "Creating 8x9 matrix of 0's"
              << "\n";
    auto matrix_zero_2 = gpmp::mtx<int>::zeros(8, 9);
    matrix_zero_2.print_shape();
    matrix_zero_2.print_mtx();

    // declare matrix of ones with 8 x 9 dimensions
    std::cout << "Creating 8x9 matrix of 1's"
              << "\n";
    auto matrix_one = gpmp::mtx<int>::ones(8, 9);
    matrix_one.print_shape();
    matrix_one.print_mtx();

    return 0;
}
