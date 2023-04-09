#include <cmath>
#include <iostream>
#include <random>

using namespace std;

// Calculates (a * b) mod m
uint64_t mulmod(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t res = 0;
    while (b > 0) {
        if (b & 1) {
            res = (res + a) % m;
        }
        a = (2 * a) % m;
        b >>= 1;
    }
    return res;
}

// Calculates (a ^ b) mod m
uint64_t powmod(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) {
            res = mulmod(res, a, m);
        }
        a = mulmod(a, a, m);
        b >>= 1;
    }
    return res;
}

// Tests whether n is a witness for the compositeness of given number d
bool witness(uint64_t n, uint64_t d, uint64_t a, uint64_t s) {
    uint64_t x = powmod(a, d, n);
    if (x == 1 || x == n - 1) {
        return false;
    }
    for (uint64_t r = 1; r < s; r++) {
        x = mulmod(x, x, n);
        if (x == n - 1) {
            return false;
        }
    }
    return true;
}

// Returns true if n is probably prime, false otherwise
bool miller_rabin(uint64_t n, uint64_t k = 64) {
    if (n < 2) {
        return false;
    }
    if (n == 2 || n == 3) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }
    uint64_t d = n - 1, s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    for (uint64_t i = 0; i < k; i++) {
        uint64_t a = rand() % (n - 3) + 2;
        if (witness(n, d, a, s)) {
            return false;
        }
    }
    return true;
}

int main() {
    // vector<uint32_t> nums = { 32452843, 43737611, 28136491, 33187413,
    // 37042277,
    //                     28772807, 22446689, 39218447, 36844253,
    //                     35771017, 22741457, 26722153, 32413477,
    //                     31952227, 34053959, 38270761, 32896243,
    //                     26758763, 29806919, 28506727, 1024 };

    /*
    vector<uint64_t> nums = {
        9223372036854775803,   9223372036854775807,
        9223372036854775303,   4567890123456789ULL,
        5678901234567890ULL,    6789012345678901LL,
        7890123456789012ULL,    8901234567890123LL,
        9999999967ULL,          12345678901234567LL,
        987654321987654321ULL,  2147483647LL,
        9223372036854775783ULL, 1311768467463790320LL,
        7237005577332262210ULL, 3037000499LL,
        2305843009213693951ULL, 2305843009213693967LL,
        2305843009213693971ULL, 2305843009213693973LL,
        2305843009213693977ULL, 2305843009213693989LL};*/

    vector<uint64_t> nums = {2305843009213693973, 2305843009213693967,
                             2305843009213693951, 9223372036854775783,
                             9999999967,          2147483647};

    for (uint64_t n : nums) {
        if (miller_rabin(n, 100000))
            cout << n << " is prime" << endl;
        else
            cout << n << " is composite" << endl;
    }
    return 0;
}
