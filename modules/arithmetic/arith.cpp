/*
 * stubbed out implementation file for arithmetic operations
 */
#include "../../include/arithmetic/arith_ops.hpp"
    

int64_t mtpk::Basics::greatest_power(int64_t n, int64_t p) {
    int64_t result = 0;

    // Calculate x = n/p + n/(p^2) + n/(p^3) + ....
    while (n) {
        n /= p;
        result += n;
    }
    return result;
}

int64_t mtpk::Basics::op_gcd(int64_t x, int64_t y) {
    if(x < y)
        return op_gcd(y, x);

    else if(x % y == 0)
        return y;

    else
        return op_gcd(y, x % y);
}

