#ifndef MTX_HPP
#define MTX_HPP

#include <vector>

namespace gpmp {

namespace linalg {

/**
 * @brief Mtx class offers matrix arithmetic operations. Some methods are
 * element-wise while others make use of grouping and unrolling
 */
class Mtx {

  public:
#if defined(__x86_64__) || defined(i386) || defined(__i386__) ||               \
    defined(__i386) || defined(__amd64__) || defined(__amd64)

    /**
     * @brief Perform matrix addition using Intel intrinsics, accepts
     * vectors of type int
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void mtx_add(const std::vector<std::vector<int>> &A,
                 const std::vector<std::vector<int>> &B,
                 std::vector<std::vector<int>> &C);

    /**
     * @brief Perform matrix addition using Intel intrinsics, accepts
     * vectors of type double
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 4x4
     * @overload
     */
    void mtx_add(const std::vector<std::vector<double>> &A,
                 const std::vector<std::vector<double>> &B,
                 std::vector<std::vector<double>> &C);

    /**
     * @brief Perform matrix subtraction using Intel intrinsics, accepts
     * vectors of type int
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void mtx_sub(const std::vector<std::vector<int>> &A,
                 const std::vector<std::vector<int>> &B,
                 std::vector<std::vector<int>> &C);

    /**
     * @brief Perform matrix subtraction using Intel intrinsics, accepts
     * vectors of type double
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 4x4
     * @overload
     */
    void mtx_sub(const std::vector<std::vector<double>> &A,
                 const std::vector<std::vector<double>> &B,
                 std::vector<std::vector<double>> &C);

    /**
     * @brief Perform matrix multiplication using Intel intrinsics, accepts
     * vectors of type int
     * @param A input matrix A
     * @param B input matrix B
     * @param C output matrix C
     * @note matrices must be of at least size 8x8
     * @overload
     */
    void mtx_mult(const std::vector<std::vector<int>> &A,
                  const std::vector<std::vector<int>> &B,
                  std::vector<std::vector<int>> &C);

    /**
     * @brief Perform matrix multiplication using Intel intrinsics, accepts
     * vectors of type double
     * @param A input matrix A
     * @param B input matrix B
     * @param C output matrix C
     * @note matrices must be of at least size 4x4
     * @overload
     */
    void mtx_mult(const std::vector<std::vector<double>> &A,
                  const std::vector<std::vector<double>> &B,
                  std::vector<std::vector<double>> &C);
    /**
     * @brief Transpose matrices using Intel intrinsics
     * @param matrix Input matrix
     * @note Require matrices of at least size 8x8
     * @overload
     */
    void mtx_tpose(std::vector<std::vector<int>> &matrix);

/**
 * @brief If system is ARM
 */
#elif defined(__ARM_ARCH_ISA_A64) || defined(__ARM_NEON) ||                    \
    defined(__ARM_ARCH) || defined(__aarch64__)
    /**
     * @brief Perform matrix addition using ARM intrinsics, accepts
     * vectors of type int
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void mtx_add(const std::vector<std::vector<int>> &A,
                 const std::vector<std::vector<int>> &B,
                 std::vector<std::vector<int>> &C);

    /**
     * @brief Perform matrix addition using ARM intrinsics, accepts
     * vectors of type double
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 4x4
     * @overload
     */
    void mtx_add(const std::vector<std::vector<double>> &A,
                 const std::vector<std::vector<double>> &B,
                 std::vector<std::vector<double>> &C);

    /**
     * @brief Perform matrix subtraction using ARM intrinsics, accepts
     * vectors of type int
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void mtx_sub(const std::vector<std::vector<int>> &A,
                 const std::vector<std::vector<int>> &B,
                 std::vector<std::vector<int>> &C);

    /**
     * @brief Perform matrix subtraction using ARM intrinsics, accepts
     * vectors of type int
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 4x4
     * @overload
     */
    void mtx_sub(const std::vector<std::vector<double>> &A,
                 const std::vector<std::vector<double>> &B,
                 std::vector<std::vector<double>> &C);

    /**
     * @brief Perform matrix multiplication using ARM intrinsics, accepts
     * vectors of type int
     * @param A input matrix A
     * @param B input matrix B
     * @param C output matrix C
     * @note matrices must be of at least size 8x8
     * @overload
     */
    void mtx_mult(const std::vector<std::vector<int>> &A,
                  const std::vector<std::vector<int>> &B,
                  std::vector<std::vector<int>> &C);

    /**
     * @brief Perform matrix multiplication using ARM intrinsics, accepts
     * vectors of type double
     * @param A input matrix A
     * @param B input matrix B
     * @param C output matrix C
     * @note matrices must be of at least size 4x4
     * @overload
     */
    void mtx_mult(const std::vector<std::vector<double>> &A,
                  const std::vector<std::vector<double>> &B,
                  std::vector<std::vector<double>> &C);

    void mtx_mult_strass(const std::vector<std::vector<int>> &A,
                         const std::vector<std::vector<int>> &B,
                         std::vector<std::vector<int>> &C);

    void mtx_mult_strass(const std::vector<std::vector<double>> &A,
                         const std::vector<std::vector<double>> &B,
                         std::vector<std::vector<double>> &C);

    /**
     * @brief Transpose matrices using Intel intrinsics
     * @param matrix Input matrix
     * @note Require matrices of at least size 8x8
     * @overload
     */
    void mtx_tpose(std::vector<std::vector<int>> &matrix);

#endif

    /**
     * @brief Perform matrix addition on two matrices
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @overload
     */
    template <typename T>
    void std_mtx_add(const std::vector<std::vector<T>> &A,
                     const std::vector<std::vector<T>> &B,
                     std::vector<std::vector<T>> &C);

    /**
     * @brief Perform matrix subtraction on two matrices
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @overload
     */
    template <typename T>
    void std_mtx_sub(const std::vector<std::vector<T>> &A,
                     const std::vector<std::vector<T>> &B,
                     std::vector<std::vector<T>> &C);

    /**
     * @brief Perform matrix multiplication on two matrices
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @overload
     */
    template <typename T>
    void std_mtx_mult(const std::vector<std::vector<T>> &A,
                      const std::vector<std::vector<T>> &B,
                      std::vector<std::vector<T>> &C);

    /**
     * @brief Performs matrix multiplication using the Strassen algorithm
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note The input matrices A and B should be square matrices with
     * dimensions that are powers of 2
     * @overload
     */
    void std_mtx_mult_strass(const std::vector<std::vector<int>> &A,
                             const std::vector<std::vector<int>> &B,
                             std::vector<std::vector<int>> &C);
};

} // namespace linalg

} // namespace gpmp

#endif
