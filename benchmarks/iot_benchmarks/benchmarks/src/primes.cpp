#include "../lib/primes.hpp"
#include <iostream>
#include <random>
#include <vector>

uint32_t mod_mul(uint32_t a, uint32_t b, uint32_t m) {
    uint32_t res = 0;
    while (b > 0) {
        if (b & 1) {
            res = (res + a) % m;
        }
        a = (2 * a) % m;
        b >>= 1;
    }
    return res;
}

uint32_t mod_pow(uint32_t a, uint32_t b, uint32_t m) {
    uint32_t res = 1;

    a %= m;
    while (b > 0) {
        if (b & 1) {
            res = mod_mul(res, a, m);
        }
        a = mod_mul(a, a, m);
        b >>= 1;
    }
    return res;
}

bool witness(uint32_t n, uint32_t d, uint32_t a, uint32_t s) {
    uint32_t x = mod_pow(a, d, n);

    // likely prime, return false
    if (x == 1 || x == n - 1) {
        return false;
    }

    for (uint32_t r = 1; r < s; r++) {
        x = mod_mul(x, x, n);
        if (x == n - 1) {
            return false;
        }
    }
    return true;
}

bool miller_rabin(uint32_t n, uint32_t iters = 10) {
    if (n < 2) {
        return false;
    }
    if (n == 2 || n == 3) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }
    uint32_t d = n - 1, s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    for (uint32_t i = 0; i < iters; i++) {
        uint32_t a = rand() % (n - 3) + 2;
        if (witness(n, d, a, s)) {
            return false;
        }
    }
    return true;
}
