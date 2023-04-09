#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// Calculates (a * b) % mod, taking care of overflow
uint64_t mulmod(uint64_t a, uint64_t b, uint64_t mod) {
    uint64_t res = 0;
    while (b > 0) {
        if (b & 1) {
            res = (res + a) % mod;
        }
        a = (a * 2) % mod;
        b >>= 1;
    }
    return res;
}

// Calculates (a^b) % mod, taking care of overflow
uint64_t powmod(uint64_t a, uint64_t b, uint64_t mod) {
    uint64_t res = 1;
    while (b > 0) {
        if (b & 1) {
            res = mulmod(res, a, mod);
        }
        a = mulmod(a, a, mod);
        b >>= 1;
    }
    return res;
}

// Calculates the Jacobi symbol (a/n)
int jacobi(uint64_t a, uint64_t n) {
    int res = 1;
    while (a > 1) {
        a %= n;
        if (a <= 1 || a == n - 1) {
            break;
        }
        if (a % 2 == 0) {
            res *= (n % 8 == 1 || n % 8 == 7) ? 1 : -1;
            a /= 2;
        } else {
            res *= (a % 4 == 3 && n % 4 == 3) ? -1 : 1;
            uint64_t temp = a;
            a = n;
            n = temp;
        }
    }
    return (n == 1) ? res : 0;
}

// Returns true if n is a Lucas probable prime with parameters P and Q
bool isLucasProbablePrime(uint64_t n, uint64_t P, uint64_t Q) {
    int J = jacobi(Q, n);
    if (J == 0) {
        return false;
    }
    uint64_t D = P * P - 4 * Q;
    if (J == -1) {
        D = -D;
    }
    uint64_t U = (n + 1) % n;
    uint64_t V = P;
    for (uint64_t i = (uint64_t)63; i >= 0; i--) {
        uint64_t temp = mulmod(U, V, n);
        V = (mulmod(V, V, n) + mulmod(D, U, n)) % n;
        U = temp;
        if ((1ull << i) & (n - 1)) {
            temp = (P * U + V) % n;
            V = (Q * U + P * V) % n;
            U = temp;
        }
    }
    return U == 0;
}

// Returns true if n is prime using Lucas' primality test
bool isPrime(uint64_t n) {
    if (n == 2) {
        return true;
    }
    if (n < 2 || n % 2 == 0) {
        return false;
    }
    // Find P and Q such that D = P^2 - 4Q is not a perfect square
    uint64_t D = 5;
    while (true) {
        int J = jacobi(D, n);
        if (J == -1) {
            break;
        }
        D = (D == n - 1) ? 5 : D + 2;
    }
    uint64_t P = 1, Q = (D - P * P) / 4;
    return isLucasProbablePrime(n, P, Q);
}

int main() {
    std::vector<int64_t> nums = {
        9223372036854775803,   9223372036854775807,
        9223372036854775303,   4567890123456789LL,
        5678901234567890LL,    6789012345678901LL,
        7890123456789012LL,    8901234567890123LL,
        9999999967LL,          12345678901234567LL,
        987654321987654321LL,  2147483647LL,
        9223372036854775783LL, 1311768467463790320LL,
        7237005577332262210LL, 3037000499LL,
        2305843009213693951LL, 2305843009213693967LL,
        2305843009213693971LL, 2305843009213693973LL,
        2305843009213693977LL, 2305843009213693989LL};

    for (auto num : nums) {
        std::cout << num << " is "
                  << (isPrime(num) ? "prime" : "composite") << std::endl;
    }

    return 0;
}
