/*
 * definitions for basic arithmetic operations 
 */

#ifndef RM_NT_BASICS_H
#define RM_NT_BASICS_H
#include <vector>
#include <stdio.h>


class basics {

    public:
        int power (int x, unsigned int y, int p);
        int greatest_power(int n, int p);
        int gcd(int x, int y);
};

class primality {
    
    public:
        bool isPrime(int num);
        bool miller_rabin(int n, int k);
        int jacobian_number(long long a, long long n);
        bool solovoy_strassen(long long p, int iterations);
        long long modulo(long long base, 
                long long exponent, 
                long long mod);
        bool carmichael_num(int n);
        void sieve_of_eratosthenes(int n);
        void pollard_rho(long long int n);
        int ETF(unsigned int n);

};

#endif

