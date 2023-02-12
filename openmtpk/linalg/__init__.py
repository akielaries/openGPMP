"""
/*************************************************************************
 *
 *  Project
 *                        __  __ _______ _____  _  __
 *                       |  \/  |__   __|  __ \| |/ /
 *  ___  _ __   ___ _ __ | \  / |  | |  | |__) | ' /
 * / _ \| '_ \ / _ \ '_ \| |\/| |  | |  |  ___/|  <
 *| (_) | |_) |  __/ | | | |  | |  | |  | |    | . \ 
 * \___/| .__/ \___|_| |_|_|  |_|  |_|  |_|    |_|\_\ 
 *      | |
 *      |_|
 *
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openMTPK/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/

openMTPK Linear Algebra Module
==============================
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

FEATURES :
    CLASS : Matrix
        - The default Matrix Class defaulting to floating type
        - MatrixI Class features same methods but Integer types
    METHODS :
        mult
        scalar_mult
        mult_elem
        sqr_err
        add
        scalar_add
        sub
        transpose
        sum
        mean
        concatenate
        diag
        print_shape
        print_mtx
        fill_index

    CLASS : mtx
        - Closely coupled with the Matrix Class
        - mtxI Class features same methods but Integer types
    METHODS :
        zeros
        ones
        randn
        rand

    TODO :
        - Vectors Class? Matrix Class is capable of creating Vectors
        but possible error prone to not fixing to a dimension size.

        - Tensor Class?

    USAGE :
        >> import openmtpk
        >> # create matrix of 3,4 size
        >> mtx = openmtpk.linalg.Matrix(3, 4)
        OR
        >> from openmtpk import linalg
"""

from openmtpk.linalg.linalg import (
    Matrix,
    mtx,
    Vectors,
)

__all__: list[str]
__path__: list[str]
