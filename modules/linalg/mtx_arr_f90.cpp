/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openGPMP/ along with
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
#include "../../include/linalg/mtx.hpp"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

/************************************************************************
 *
 * Matrix Operations on Arrays using Fortran Subroutines
 * in `mtx_routines.f90`
 *
 ************************************************************************/

// if source C++ API is being compiled, include these Fortran refs and wrappers
#if defined(__GPMP_CPP_API__)

extern "C" {
// Matrix add routine (FLOAT)
void mtx_add_routine_float_(float *A,
                            float *B,
                            float *C,
                            std::size_t *mtx_size);

// Matrix add routine (INT)
void mtx_add_routine_int_(int *A, int *B, int *C, std::size_t *mtx_size);

void mtx_mult_routine_int_(int *A,
                           int *B,
                           int *C,
                           std::size_t *rows_a,
                           std::size_t *cols_a,
                           std::size_t *cols_b);
}

// C++ wrapper for Fortran mtx addition subroutine FLOAT
void gpmp::linalg::Mtx::mtx_add_f90(float *A,
                                    float *B,
                                    float *C,
                                    std::size_t mtx_size) {
    mtx_add_routine_float_(A, B, C, &mtx_size);
}

// C++ wrapper for Fortran mtx addition subroutine INT
void gpmp::linalg::Mtx::mtx_add_f90(int *A,
                                    int *B,
                                    int *C,
                                    std::size_t mtx_size) {
    mtx_add_routine_int_(A, B, C, &mtx_size);
}

// C++ wrapper for Fortran mtx multiplication subroutine INT
void gpmp::linalg::Mtx::mtx_mult_f90(int *A,
                                     int *B,
                                     int *C,
                                     std::size_t rows_a,
                                     std::size_t cols_a,
                                     std::size_t cols_b) {
    mtx_mult_routine_int_(A, B, C, &rows_a, &cols_a, &cols_b);
}

#endif
