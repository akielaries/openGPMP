#!/usr/bin/python3

"""
since the Matrix class is a template class, there are classes created
for both Doubles and Integers

The template Matrix class and mtx struct were converted to type double
methods instead of declaring a method for each type.
    *NOTE* there is a respective 'INTEGER' version of each method that 
    defaulted to type double, my recommendation is to use the default
    methods that converted to type double as data will more than likely
    follow the scheme.

    SCHEMES:
        class Matrix (int) -> class MatrixI
        an INTEGER type mtx struct is not possible given floating
        point requirements for certain cases of cassert
"""
from openmtpk import Matrix, mtx

# create and print a 3x4 matrix of zeros
print('** Method to create Matrix of zeros **')
mtx_z1 = Matrix(3,4)
mtx_z1.print_shape()
mtx_z1.print_mtx()

# create and print a 15x12 matrix of zeros
print('** ANOTHER method to create Matrix of zeros **')
mtx_z2 = mtx.zeros(15, 12)
mtx_z2.print_shape()
mtx_z2.print_mtx()

# create and print a 3x7 matrix of ones
print('** Method to create Matrix of ones **')
mtx_o = mtx.ones(3, 7)
mtx_o.print_shape()
mtx_o.print_mtx()

# random matrix of positive numbers
print('** 8x5 Matrix of random positive numbers **')
# declare positive matrix object calling the original mtx struct
mtx_pos = mtx.rand(8, 5)
mtx_pos.print_shape()
mtx_pos.print_mtx()

# random matrix of pos and neg numbers
print('** 8x5 Matrix of random numbers including negatives **')
mtx_neg = mtx.randn(8, 5)
mtx_neg.print_shape()
mtx_neg.print_mtx()

# multiply each element of mtx_pos by a number
print('** Multiply each element of mtx_pos, mtx_neg respectively\
 by a specific number **')

print('* 2')
mtx_pos.scalar_mult(2).print_mtx()
print('* 2')
mtx_neg.scalar_mult(3).print_mtx()

# multiply each element of mtx_pos by itself
print('** Multiply each element of mtx_pos, mtx_neg respectively\
 by itself **')

mtx_pos.mult_elem(mtx_pos).print_mtx()
mtx_neg.mult_elem(mtx_pos).print_mtx()


