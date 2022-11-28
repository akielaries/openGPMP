/*
 * definitions for basic arithmetic operations 
 */

#ifndef RMPRIMESH
#define RMPRIMESH
#include <vector>
#include <stdio.h>


class basics {

    public:
        /* raise to a power */
        int power (int x, unsigned int y, int p);
        /* greatest power of two given integers */
        int greatest_power(int n, int p);
        /* greatest common factor */
        int gcd(int x, int y);
};

class primality {
    
    public:
        /* determine if var_n is a prime number */
        bool is_prime(int n);

        /* algorithm determining if a given number is likely to be prime */
        bool miller_rabin(int n, int k);
        
        /* algorithms finding a prime number */
        int jacobian_number(long long a, long long n);
        
        /* determine if var_p is composite or probably prime */
        bool solovoy_strassen(long long p, int iters);
        
        /* perform binary exponentiation */
        long long modulo(long long base, 
                long long exponent, 
                long long mod);
        
        /* satifies congruence relation:b^n - 1 = b (mod n) */
        bool carmichael_num(int n);
        
        /* finds the prime numbers up to a limit */
        void sieve_of_eratosthenes(int n);
        
        /* integer factorization */
        void pollard_rho(long long int n);
        
        /* Eulers Totient Function */
        int ETF(unsigned int n);
};

#endif

