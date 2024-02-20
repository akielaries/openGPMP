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

/** Single precision GEneral Matrix-Matrix product */

#include "../../include/linalg/_sgemm.hpp"
#include <cmath>
#include <limits>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// MATRIX BUFFERS
float gpmp::linalg::SGEMM::SGEMM_BUFF_A[BLOCK_SZ_M * BLOCK_SZ_K];
float gpmp::linalg::SGEMM::SGEMM_BUFF_B[BLOCK_SZ_K * BLOCK_SZ_N];
float gpmp::linalg::SGEMM::SGEMM_BUFF_C[BLOCK_SZ_MR * BLOCK_SZ_NR];

// pack micro panels of size BLOCK_SZ_MR rows by k columns from A without
// padding
void gpmp::linalg::SGEMM::pack_micro_A(int k,
                                       const float *A,
                                       int incRowA,
                                       int incColA,
                                       float *buffer) {
    int i, j;

    for (j = 0; j < k; ++j) {
        for (i = 0; i < BLOCK_SZ_MR; ++i) {
            buffer[i] = A[i * incRowA];
        }
        buffer += BLOCK_SZ_MR;
        A += incColA;
    }
}

// packs panels from A with padding if needed
void gpmp::linalg::SGEMM::pack_buffer_A(int mc,
                                        int kc,
                                        const float *A,
                                        int incRowA,
                                        int incColA,
                                        float *buffer) {
    int mp = mc / BLOCK_SZ_MR;
    int _mr = mc % BLOCK_SZ_MR;

    int i, j;

    for (i = 0; i < mp; ++i) {
        pack_micro_A(kc, A, incRowA, incColA, buffer);
        buffer += kc * BLOCK_SZ_MR;
        A += BLOCK_SZ_MR * incRowA;
    }
    if (_mr > 0) {
        for (j = 0; j < kc; ++j) {
            for (i = 0; i < _mr; ++i) {
                buffer[i] = A[i * incRowA];
            }
            for (i = _mr; i < BLOCK_SZ_MR; ++i) {
                buffer[i] = 0.0f;
            }
            buffer += BLOCK_SZ_MR;
            A += incColA;
        }
    }
}

// packing complete panels from B of size BLOCK_SZ_NR by k columns
void gpmp::linalg::SGEMM::pack_micro_B(int k,
                                       const float *B,
                                       int incRowB,
                                       int incColB,
                                       float *buffer) {
    int i, j;

    for (i = 0; i < k; ++i) {
        for (j = 0; j < BLOCK_SZ_NR; ++j) {
            buffer[j] = B[j * incColB];
        }
        buffer += BLOCK_SZ_NR;
        B += incRowB;
    }
}

// packing panels from B with padding if needed
void gpmp::linalg::SGEMM::pack_buffer_B(int kc,
                                        int nc,
                                        const float *B,
                                        int incRowB,
                                        int incColB,
                                        float *buffer) {
    int np = nc / BLOCK_SZ_NR;
    int _nr = nc % BLOCK_SZ_NR;

    int i, j;

    for (j = 0; j < np; ++j) {
        pack_micro_B(kc, B, incRowB, incColB, buffer);
        buffer += kc * BLOCK_SZ_NR;
        B += BLOCK_SZ_NR * incColB;
    }
    if (_nr > 0) {
        for (i = 0; i < kc; ++i) {
            for (j = 0; j < _nr; ++j) {
                buffer[j] = B[j * incColB];
            }
            for (j = _nr; j < BLOCK_SZ_NR; ++j) {
                buffer[j] = 0.0f;
            }
            buffer += BLOCK_SZ_NR;
            B += incRowB;
        }
    }
}

// micro kernel that multiplies panels from A and B
void gpmp::linalg::SGEMM::sgemm_micro_kernel(int kc,
                                             float alpha,
                                             const float *A,
                                             const float *B,
                                             float beta,
                                             float *C,
                                             int incRowC,
                                             int incColC) {
    float AB[BLOCK_SZ_MR * BLOCK_SZ_NR];

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
    if (fabs(beta - 0.0f) < std::numeric_limits<float>::epsilon()) {
        for (j = 0; j < BLOCK_SZ_NR; ++j) {
            for (i = 0; i < BLOCK_SZ_MR; ++i) {
                C[i * incRowC + j * incColC] = 0.0f;
            }
        }
    } else if (fabs(beta - 1.0f) > std::numeric_limits<float>::epsilon()) {
        for (j = 0; j < BLOCK_SZ_NR; ++j) {
            for (i = 0; i < BLOCK_SZ_MR; ++i) {
                C[i * incRowC + j * incColC] *= beta;
            }
        }
    }

    // Update C <- C + alpha*AB (note: the case alpha==0.0f was already treated
    // in
    //                                  the above layer sgemm_nn)
    if (fabs(alpha - 1.0f) < std::numeric_limits<float>::epsilon()) {
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

// Compute Y += alpha*X (float precision AX + Y)
void gpmp::linalg::SGEMM::sgeaxpy(int m,
                                  int n,
                                  float alpha,
                                  const float *X,
                                  int incRowX,
                                  int incColX,
                                  float *Y,
                                  int incRowY,
                                  int incColY) {
    int i, j;

    if (fabs(alpha - 1.0f) > std::numeric_limits<float>::epsilon()) {

        for (j = 0; j < n; ++j) {
            for (i = 0; i < m; ++i) {
                Y[i * incRowY + j * incColY] +=
                    alpha * X[i * incRowX + j * incColX];
            }
        }
    }

    else {
        for (j = 0; j < n; ++j) {
            for (i = 0; i < m; ++i) {
                Y[i * incRowY + j * incColY] += X[i * incRowX + j * incColX];
            }
        }
    }
}

//  Compute X *= alpha (scale elements)
void gpmp::linalg::SGEMM::sgescal(int m,
                                  int n,
                                  float alpha,
                                  float *X,
                                  int incRowX,
                                  int incColX) {
    int i, j;

    if (fabs(alpha - 0.0f) > std::numeric_limits<float>::epsilon()) {
        for (j = 0; j < n; ++j) {
            for (i = 0; i < m; ++i) {
                X[i * incRowX + j * incColX] *= alpha;
            }
        }
    }

    else {
        for (j = 0; j < n; ++j) {
            for (i = 0; i < m; ++i) {
                X[i * incRowX + j * incColX] = 0.0f;
            }
        }
    }
}

// Macro Kernel for the multiplication of blocks of A and B.  We assume that
// these blocks were previously packed to buffers SGEMM_BUFF_A and SGEMM_BUFF_B.
void gpmp::linalg::SGEMM::sgemm_macro_kernel(int mc,
                                             int nc,
                                             int kc,
                                             float alpha,
                                             float beta,
                                             float *C,
                                             int incRowC,
                                             int incColC) {

    int mp = (mc + BLOCK_SZ_MR - 1) / BLOCK_SZ_MR;
    int np = (nc + BLOCK_SZ_NR - 1) / BLOCK_SZ_NR;

    int _mr = mc % BLOCK_SZ_MR;
    int _nr = nc % BLOCK_SZ_NR;

    int mr, nr;
    int i, j;

    for (j = 0; j < np; ++j) {
        nr = (j != np - 1 || _nr == 0) ? BLOCK_SZ_NR : _nr;

        for (i = 0; i < mp; ++i) {
            mr = (i != mp - 1 || _mr == 0) ? BLOCK_SZ_MR : _mr;

            if (mr == BLOCK_SZ_MR && nr == BLOCK_SZ_NR) {
                sgemm_micro_kernel(
                    kc,
                    alpha,
                    &SGEMM_BUFF_A[i * kc * BLOCK_SZ_MR],
                    &SGEMM_BUFF_B[j * kc * BLOCK_SZ_NR],
                    beta,
                    &C[i * BLOCK_SZ_MR * incRowC + j * BLOCK_SZ_NR * incColC],
                    incRowC,
                    incColC);
            } else {
                sgemm_micro_kernel(kc,
                                   alpha,
                                   &SGEMM_BUFF_A[i * kc * BLOCK_SZ_MR],
                                   &SGEMM_BUFF_B[j * kc * BLOCK_SZ_NR],
                                   0.0f,
                                   SGEMM_BUFF_C,
                                   1,
                                   BLOCK_SZ_MR);
                sgescal(
                    mr,
                    nr,
                    beta,
                    &C[i * BLOCK_SZ_MR * incRowC + j * BLOCK_SZ_NR * incColC],
                    incRowC,
                    incColC);
                sgeaxpy(
                    mr,
                    nr,
                    1.0f,
                    SGEMM_BUFF_C,
                    1,
                    BLOCK_SZ_MR,
                    &C[i * BLOCK_SZ_MR * incRowC + j * BLOCK_SZ_NR * incColC],
                    incRowC,
                    incColC);
            }
        }
    }
}

// Main SGEMM entrypoint, compute C <- beta*C + alpha*A*B
void gpmp::linalg::SGEMM::sgemm_nn(int m,
                                   int n,
                                   int k,
                                   float alpha,
                                   const float *A,
                                   int incRowA,
                                   int incColA,
                                   const float *B,
                                   int incRowB,
                                   int incColB,
                                   float beta,
                                   float *C,
                                   int incRowC,
                                   int incColC) {
    int mb = (m + BLOCK_SZ_M - 1) / BLOCK_SZ_M;
    int nb = (n + BLOCK_SZ_N - 1) / BLOCK_SZ_N;
    int kb = (k + BLOCK_SZ_K - 1) / BLOCK_SZ_K;

    int _mc = m % BLOCK_SZ_M;
    int _nc = n % BLOCK_SZ_N;
    int _kc = k % BLOCK_SZ_K;

    int mc, nc, kc;
    int i, j, l;

    float _beta;

    if (fabs(alpha) < std::numeric_limits<float>::epsilon() || k == 0) {
        sgescal(m, n, beta, C, incRowC, incColC);
        return;
    }

    for (j = 0; j < nb; ++j) {
        nc = (j != nb - 1 || _nc == 0) ? BLOCK_SZ_N : _nc;

        for (l = 0; l < kb; ++l) {
            kc = (l != kb - 1 || _kc == 0) ? BLOCK_SZ_K : _kc;
            _beta = (l == 0) ? beta : 1.0f;

            pack_buffer_B(
                kc,
                nc,
                &B[l * BLOCK_SZ_K * incRowB + j * BLOCK_SZ_N * incColB],
                incRowB,
                incColB,
                SGEMM_BUFF_B);

            for (i = 0; i < mb; ++i) {
                mc = (i != mb - 1 || _mc == 0) ? BLOCK_SZ_M : _mc;

                pack_buffer_A(
                    mc,
                    kc,
                    &A[i * BLOCK_SZ_M * incRowA + l * BLOCK_SZ_K * incColA],
                    incRowA,
                    incColA,
                    SGEMM_BUFF_A);

                sgemm_macro_kernel(
                    mc,
                    nc,
                    kc,
                    alpha,
                    _beta,
                    &C[i * BLOCK_SZ_M * incRowC + j * BLOCK_SZ_N * incColC],
                    incRowC,
                    incColC);
            }
        }
    }
}
