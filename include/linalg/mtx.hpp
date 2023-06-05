#ifndef MTX_HPP
#define MTX_HPP

#include <vector>

namespace gpmp {

namespace linalg {

class Mtx {
    public:
/**
 * @brief If system is x86 / Intel overall
 */
#if defined(__x86_64__) || defined(i386) || defined(__i386__) ||               \
    defined(__i386) || defined(__amd64__) || defined(__amd64)

    void mtx_add(const std::vector<std::vector<int>> &A,
                               const std::vector<std::vector<int>> &B,
                               std::vector<std::vector<int>> &C);

/**
 * @brief If system is ARM
 */
#elif defined(__ARM_ARCH_ISA_A64) || defined(__ARM_NEON) ||                    \
    defined(__ARM_ARCH) || defined(__aarch64__)

    void mtx_add(const std::vector<std::vector<int>> &A,
                                const std::vector<std::vector<int>> &B,
                               std::vector<std::vector<int>> &C);
/**
 * @brief If system is not detected use this naive implementation of MTX ADD
 */
#endif

    void std_mtx_add(const std::vector<std::vector<int>> &A,
                                const std::vector<std::vector<int>> &B,
                               std::vector<std::vector<int>> &C);


    void std_mtx_mult(const std::vector<std::vector<int>> &A,
                               const std::vector<std::vector<int>> &B,
                               std::vector<std::vector<int>> &C);
};

} // namespace linalg

} // namespace gpmp

#endif
