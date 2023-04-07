/*
 * Driver for showing how to use the core basic and elementary
 * functionalities of the Number Theory module
 *
 */
#include <iostream>
#include <openMTPK/nt/factorization.hpp>

int main() {
    mtpk::Factorization factorization;

    // find prime factor of 123456789
    int64_t n = 123456789;
    int64_t factor = factorization.pollard_rho(n);

    // print the result
    std::cout << "The smallest prime factor of " << n << " is " << factor
              << std::endl;

    return 0;
}
