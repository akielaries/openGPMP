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
from pygpmp import linalg

mtx = linalg.Mtx()

# Examples of usage
mtx_add_float_result = mtx.mtx_add([1.0, 2.0, 3.0], [4.0, 5.0, 6.0], [0.0, 0.0, 0.0], 3)
mtx_add_int_result = mtx.mtx_add([1, 2, 3], [4, 5, 6], [0, 0, 0], 3)

# Use the result as needed
print(mtx_add_float_result)
print(mtx_add_int_result)



