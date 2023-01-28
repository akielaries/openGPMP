/**
 * @file
 *
 * Definitions for operations related to prime numbers
 */

#ifndef PRIMES_HPP
#define PRIMES_HPP
#include <cstdint>
#include <stdio.h>
#include <vector>

namespace mtpk {
/**
 * Primality Class dealing with prime number manipulations
 */
class Primality {
    public:
    /**
     * @brief Determine if an integer is prime
     *
     * @param[in] n : any number (int64_t)
     *
     * @return : true/false (bool)
     */
    bool is_prime(int64_t n);

    /**
     * @brief Algorithm determining liklihood a number is prime
     *
     * @param[in] d : target number (int64_t)
     * @param[in] n : target - 1 (int64_t)
     *
     * @pre miller_rabin_prime()
     *
     * @return true/false (bool)
     */
    bool compute_miller_rabin(int64_t d, int64_t n);

    /**
     * @brief Modified primes algorithm
     *
     * @param[in] n : target number (int64_t)
     * @param[in] iters : iterations determine accuracy (int64_t)
     *
     * @pre miller_rabin()
     *
     * return true/false (bool)
     */
    bool miller_rabin_prime(int64_t n, int64_t iters);

    /**
     * @brief Miller-Rabin driver, prints values that satisfy
     * conditions
     * @note Finds the primes in a given range
     *
     * @param[in] iters : iterations determine accuracy (int64_t)
     * @param[in] min_val : bottom end of range (int64_t)
     * @param[in] max_val : top end of range (int64_t)
     * @param[out] result : values within range that satisfy
     *
     * @return Void
     */
    void miller_rabin(int64_t iters, int64_t min_val, int64_t max_val);

    /* algorithms finding a prime number */
    int64_t jacobian_number(int64_t a, int64_t n);

    /* determine if var_p is composite or probably prime */
    bool solovoy_strassen(int64_t p, int64_t iters);

    /* modulo + power of input */
    int64_t mod_pow(int64_t base, int64_t exponent, int64_t mod);

    /* satifies congruence relation:b^n - 1 = b (mod n) */
    bool carmichael_num(int64_t n);

    /* finds the prime numbers up to a limit */
    void sieve_of_eratosthenes(int64_t n);

    /* integer factorization */
    int64_t pollard_rho(int64_t n);

    /* Eulers Totient Function */
    int64_t ETF(uint64_t n);
};

} // namespace mtpk

#endif
