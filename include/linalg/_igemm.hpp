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
#ifndef _IGEMM_HPP
#define _IGEMM_HPP

/** BLOCK SIZES */
#define BLOCK_SZ_M 384  /**< Rows of A and C */
#define BLOCK_SZ_K 384  /**< Columns of A and rows of B */
#define BLOCK_SZ_N 4096 /**< Columns of B and C */
#define BLOCK_SZ_MR 4   /**< Rows of the micro-panel of A and C */
#define BLOCK_SZ_NR 4   /**< Columns of the micro-panel of B and C */

namespace gpmp {
namespace linalg {

/**
 * @class IGEMM
 * @brief Class for performing matrix multiplication on int type arrays
 */
class IGEMM {
  public:
    /**< Buffer for storing packed micro panels of A  */
    static int IGEMM_BUFF_A[BLOCK_SZ_M * BLOCK_SZ_K];
    /**< Buffer for storing packed micro panels of B  */
    static int IGEMM_BUFF_B[BLOCK_SZ_K * BLOCK_SZ_N];
    /**< Buffer for storing intermediate results  */
    static int IGEMM_BUFF_C[BLOCK_SZ_MR * BLOCK_SZ_NR];

    /**
     * @brief Packs micro panels of size BLOCK_SZ_MR rows by k columns from A
     * without padding
     *
     * @param k Number of columns to pack
     * @param A Pointer to the source matrix A
     * @param incRowA Increment between consecutive rows of A
     * @param incColA Increment between consecutive columns of A
     * @param buffer Pointer to the buffer to store the packed micro panels
     */
    void
    pack_micro_A(int k, const int *A, int incRowA, int incColA, int *buffer);

    /**
     * @brief Packs panels from A with padding if needed
     *
     * @param mc Number of rows to pack
     * @param kc Number of columns to pack
     * @param A Pointer to the source matrix A
     * @param incRowA Increment between consecutive rows of A
     * @param incColA Increment between consecutive columns of A
     * @param buffer Pointer to the buffer to store the packed panels
     */
    void pack_buffer_A(int mc,
                       int kc,
                       const int *A,
                       int incRowA,
                       int incColA,
                       int *buffer);

    /**
     * @brief Packs micro panels of size BLOCK_SZ_NR columns by k rows from B
     * without padding
     *
     * @param k Number of rows to pack
     * @param B Pointer to the source matrix B
     * @param incRowB Increment between consecutive rows of B
     * @param incColB Increment between consecutive columns of B
     * @param buffer Pointer to the buffer to store the packed micro panels
     */
    void
    pack_micro_B(int k, const int *B, int incRowB, int incColB, int *buffer);

    /**
     * @brief Packs panels from B with padding if needed
     *
     * @param kc Number of rows to pack
     * @param nc Number of columns to pack
     * @param B Pointer to the source matrix B
     * @param incRowB Increment between consecutive rows of B
     * @param incColB Increment between consecutive columns of B
     * @param buffer Pointer to the buffer to store the packed panels
     */
    void pack_buffer_B(int kc,
                       int nc,
                       const int *B,
                       int incRowB,
                       int incColB,
                       int *buffer);

    /**
     * @brief Computes the micro kernel that multiplies panels from A and B
     *
     * @param kc Number of columns
     * @param alpha Scalar alpha
     * @param A Pointer to the packed panel A
     * @param B Pointer to the packed panel B
     * @param beta Scalar beta
     * @param C Pointer to the output matrix C
     * @param incRowC Increment between consecutive rows of C
     * @param incColC Increment between consecutive columns of C
     */
    void igemm_micro_kernel(int kc,
                            int alpha,
                            const int *A,
                            const int *B,
                            int beta,
                            int *C,
                            int incRowC,
                            int incColC);

    /**
     * @brief Computes Y += alpha*X (int precision AX + Y)
     *
     * @param m Number of rows
     * @param n Number of columns
     * @param alpha Scalar alpha
     * @param X Pointer to matrix X
     * @param incRowX Increment between consecutive rows of X
     * @param incColX Increment between consecutive columns of X
     * @param Y Pointer to matrix Y
     * @param incRowY Increment between consecutive rows of Y
     * @param incColY Increment between consecutive columns of Y
     */
    void igeaxpy(int m,
                 int n,
                 int alpha,
                 const int *X,
                 int incRowX,
                 int incColX,
                 int *Y,
                 int incRowY,
                 int incColY);

    /**
     * @brief Scales elements of X by alpha
     *
     * @param m Number of rows
     * @param n Number of columns
     * @param alpha Scalar alpha
     * @param X Pointer to matrix X
     * @param incRowX Increment between consecutive rows of X
     * @param incColX Increment between consecutive columns of X
     */
    void igescal(int m, int n, int alpha, int *X, int incRowX, int incColX);

    /**
     * @brief Macro kernel for the multiplication of blocks of A and B
     *
     * @param mc Number of rows in the block of C
     * @param nc Number of columns in the block of C
     * @param kc Number of columns in the blocks of A and rows of B
     * @param alpha Scalar alpha
     * @param beta Scalar beta
     * @param C Pointer to the output matrix C
     * @param incRowC Increment between consecutive rows of C
     * @param incColC Increment between consecutive columns of C
     */
    void igemm_macro_kernel(int mc,
                            int nc,
                            int kc,
                            int alpha,
                            int beta,
                            int *C,
                            int incRowC,
                            int incColC);

    /**
     * @brief Main IGEMM entrypoint, computes C <- beta*C + alpha*A*B
     *
     * @param m Number of rows of A and rows of C
     * @param n Number of columns of B and columns of C
     * @param k Number of columns of A and rows of B
     * @param alpha Scalar alpha
     * @param A Pointer to matrix A
     * @param incRowA Increment between consecutive rows of A
     * @param incColA Increment between consecutive columns of A
     * @param B Pointer to matrix B
     * @param incRowB Increment between consecutive rows of B
     * @param incColB Increment between consecutive columns of B
     * @param beta Scalar beta
     * @param C Pointer to matrix C
     * @param incRowC Increment between consecutive rows of C
     * @param incColC Increment between consecutive columns of C
     */
    void igemm_nn(int m,
                  int n,
                  int k,
                  int alpha,
                  const int *A,
                  int incRowA,
                  int incColA,
                  const int *B,
                  int incRowB,
                  int incColB,
                  int beta,
                  int *C,
                  int incRowC,
                  int incColC);
};

} // namespace linalg
} // namespace gpmp

#endif
