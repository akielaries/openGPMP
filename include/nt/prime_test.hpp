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

/**
 * @file
 *
 * Definitions for operations related to prime numbers
 */
#ifndef PRIMES_TEST_HPP
#define PRIMES_TEST_HPP

#include <cstdint>
#include <stdio.h>
#include <vector>

namespace mtpk {
/**
 * Primality Class dealing with prime number manipulations
 */
class PrimalityTest {
  public:
    /**
     * @brief Determine if an integer is prime
     *
     * @param[in] n : any number (uint64_t)
     *
     * @return : true/false (bool)
     */
    bool is_prime(uint64_t n);

    /**
     * @brief Algorithm determining liklihood a number is prime
     *
     * @param[in] d : target number (uint64_t)
     * @param[in] n : target - 1 (uint64_t)
     *
     * @pre miller_rabin_prime()
     *
     * @return true/false (bool)
     */
    bool compute_miller_rabin(uint64_t d, uint64_t n);

    /**
     * @brief Modified primes algorithm
     *
     * @param[in] n : target number (uint64_t)
     * @param[in] iters : iterations determine accuracy (uint64_t)
     *
     * @pre miller_rabin()
     *
     * return true/false (bool)
     */
    bool miller_rabin_prime(uint64_t n, uint64_t iters);

    /**
     * @brief Miller-Rabin driver, prints values that satisfy
     * conditions
     * @note Finds the primes in a given range
     *
     * @param[in] iters : iterations determine accuracy (uint64_t)
     * @param[in] min_val : bottom end of range (uint64_t)
     * @param[in] max_val : top end of range (uint64_t)
     * @param[out] result : values within range that satisfy
     *
     * @return Void
     */
    void miller_rabin(uint64_t iters, uint64_t min_val, uint64_t max_val);

    bool witness(uint64_t n, uint64_t d, uint64_t a, uint64_t s);

    /* Agrawal–Kayal–Saxena primality deterministic algorithm */
    bool AKS(uint64_t n);

    /* Lucas Primality Test */
    // uint64_t lucas(uint64_t n);

    /* algorithms finding a prime number */
    uint64_t jacobian_number(uint64_t a, uint64_t n);

    /* determine if var_p is composite or probably prime */
    bool solovoy_strassen(uint64_t p, uint64_t iters);

    /* modulo + power of input */
    uint64_t mod_mul(uint64_t a, uint64_t b, uint64_t m);

    uint64_t mod_pow(uint64_t a, uint64_t b, uint64_t m);

    // uint64_t mod_pow(uint64_t base, uint64_t exponent, uint64_t mod);
    /* satifies congruence relation:b^n - 1 = b (mod n) */
    bool carmichael_num(uint64_t n);

    /* finds the prime numbers up to a limit */
    // void sieve_of_eratosthenes(uint64_t n);

    /* Eulers Totient Function */
    uint64_t ETF(uint64_t n);
};

} // namespace mtpk

#endif
