/**
 * Driver for showing how to use the core functionalities of the Number Theory
 * module by itself. This features tools related to distrete logarithmic
 * functions.
 *
 * @example logarithms.cpp
 */
#include <iostream>
#include <openGPMP/nt/logarithms.hpp>

int main() {
    gpmp::Logarithms logs;
    int64_t g = 3;
    int64_t y = 7;
    int64_t p = 11;
    int64_t x = logs.pollard_rho_log(g, y, p);
    std::cout << "The discrete logarithm of " << y
              << " with respect to the base " << g << " in the group of order "
              << p << " is " << x << std::endl;

    int64_t a = 2, b = 3, m = 5;
    std::cout << logs.BSGS(a, b, m) << std::endl;

    a = 3, b = 7, m = 11;
    std::cout << logs.BSGS(a, b, m) << std::endl;

    return 0;
}
