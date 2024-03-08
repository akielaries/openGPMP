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

/** Double precision GEneral Matrix-Matrix product kernel without accl */

#include "../../include/linalg/_dgemm.hpp"

// micro kernel that multiplies panels from A and B
void gpmp::linalg::DGEMM::dgemm_micro_kernel(int kc,
                                             double alpha,
                                             const double *A,
                                             const double *B,
                                             double beta,
                                             double *C,
                                             int incRowC,
                                             int incColC) {
    double AB[BLOCK_SZ_MR * BLOCK_SZ_NR];

    int i, j, l;

    // Compute AB = A*B
    for (l = 0; l < BLOCK_SZ_MR * BLOCK_SZ_NR; ++l) {
        AB[l] = 0;
    }
    for (l = 0; l < kc; ++l) {
        for (j = 0; j < BLOCK_SZ_NR; ++j) {
            for (i = 0; i < BLOCK_SZ_MR; ++i) {
                AB[i + j * BLOCK_SZ_MR] += A[i] * B[j];
            }
        }
        A += BLOCK_SZ_MR;
        B += BLOCK_SZ_NR;
    }

    // Update C <- beta*C
    if (fabs(beta - 0.0) < std::numeric_limits<double>::epsilon()) {
        for (j = 0; j < BLOCK_SZ_NR; ++j) {
            for (i = 0; i < BLOCK_SZ_MR; ++i) {
                C[i * incRowC + j * incColC] = 0.0;
            }
        }
    } else if (fabs(beta - 1.0) > std::numeric_limits<double>::epsilon()) {
        for (j = 0; j < BLOCK_SZ_NR; ++j) {
            for (i = 0; i < BLOCK_SZ_MR; ++i) {
                C[i * incRowC + j * incColC] *= beta;
            }
        }
    }

    // Update C <- C + alpha*AB (note: the case alpha==0.0 was already treated
    // in
    //                                  the above layer dgemm_nn)
    if (fabs(alpha - 1.0) < std::numeric_limits<double>::epsilon()) {
        for (j = 0; j < BLOCK_SZ_NR; ++j) {
            for (i = 0; i < BLOCK_SZ_MR; ++i) {
                C[i * incRowC + j * incColC] += AB[i + j * BLOCK_SZ_MR];
            }
        }
    }

    else {
        for (j = 0; j < BLOCK_SZ_NR; ++j) {
            for (i = 0; i < BLOCK_SZ_MR; ++i) {
                C[i * incRowC + j * incColC] += alpha * AB[i + j * BLOCK_SZ_MR];
            }
        }
    }
}

