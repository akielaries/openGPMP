/**
 * @file
 *
 * Definitions for operations related to prime numbers
 */

#ifndef PRIMES_HPP
#define PRIMES_HPP
#include <vector>
#include <stdio.h>


namespace mtpk {
/**
 * Primality Class dealing with prime number manipulations
 */
class Primality {
    
    public:
        /**
         * @brief Determine if an integer is prime
         *
         * @param[in] n : any number (int)
         *
         * @return : true/false (bool)
         */
        bool is_prime(int n);

        /**
         * @brief Algorithm determining liklihood a number is prime
         *
         * @param[in] d : target number (int)
         * @param[in] n : target - 1 (int)
         *
         * @pre miller_rabin_prime()
         * 
         * @return true/false (bool)
         */
        bool compute_miller_rabin(int d, int n);

        /**
         * @brief Modified primes algorithm
         *
         * @param[in] n : target number (int)
         * @param[in] iters : iterations determine accuracy (int)
         *
         * @pre miller_rabin()
         *
         * return true/false (bool)
         */
        bool miller_rabin_prime(int n, int iters);

        /**
         * @brief Miller-Rabin driver, prints values that satisfy conditions
         * @note Finds the primes in a given range
         *
         * @param[in] iters : iterations determine accuracy (int)
         * @param[in] min_val : bottom end of range (int)
         * @param[in] max_val : top end of range (int)
         * @param[out] result : values within range that satisfy
         *
         * @return Void 
         */
        void miller_rabin(int inters, int min_val, int max_val);

        /* algorithms finding a prime number */
        int jacobian_number(long long a, long long n);
        
        /* determine if var_p is composite or probably prime */
        bool solovoy_strassen(long long p, int iters);
        
        /* modulo + power of input */
        long long int mod_pow(long long int base,
                long long int exponent,
                long long int mod);
        
        /* satifies congruence relation:b^n - 1 = b (mod n) */
        bool carmichael_num(int n);
        
        /* finds the prime numbers up to a limit */
        void sieve_of_eratosthenes(int n);
        
        /* integer factorization */
        long long int pollard_rho(long long int n);
        
        /* Eulers Totient Function */
        int ETF(unsigned int n);
};

} // namespace


#endif

