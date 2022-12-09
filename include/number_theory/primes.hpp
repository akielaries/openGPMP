/*
 * definitions for basic arithmetic operations 
 */

#ifndef RMPRIMESH
#define RMPRIMESH
#include <vector>
#include <stdio.h>


class Primality {
    
    public:
        /* determine if var_n is a prime number */
        bool is_prime(int n);

        /* algorithm determining if a given number is likely to be prime */
        bool compute_miller_rabin(int d, int n);

        /* modified primes algorithm using the compute_miller_rabin method */
        bool miller_rabin_prime(int n, int iters);

        /* miller-rabin driver, prints values that satisfy */
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

#endif

