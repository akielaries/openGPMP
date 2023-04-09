#include "../nt/primes.hpp"
#include "ThreadPool.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

bool IsPrime(int64_t n) {
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}

int main() {
    /*
    std::vector<int64_t> nums = {
        9999998900000007LL, 9999998900000003LL, 9999998900000001LL,
        9999998900000000LL, 9999998900000009LL, 9999998900000011LL,
        9999998900000027LL, 9999998900000033LL, 9999998900000087LL,
        9999998900000093LL, 9999998900000103LL, 9999998900000121LL,
        9999998900000143LL, 9999998900000169LL, 9999998900000181LL,
        9999998900000207LL, 9999998900000223LL, 9999998900000249LL,
        9999998900000257LL, 9999998900000277LL, 9999998900000291LL,
        9999998900000319LL, 9999998900000321LL, 9999998900000327LL,
        9999998900000331LL, 9999998900000333LL, 9999998900000349LL,
        9999998900000351LL, 9999998900000373LL, 9999998900000403LL};
        */
    std::vector<int64_t> nums = {
        9223372036854775803,   9223372036854775807,   9223372036854775303,
        4567890123456789LL,    5678901234567890LL,    6789012345678901LL,
        7890123456789012LL,    8901234567890123LL,    9999999967LL,
        12345678901234567LL,   987654321987654321LL,  2147483647LL,
        9223372036854775783LL, 1311768467463790320LL, 7237005577332262210LL,
        3037000499LL,          2305843009213693951LL, 2305843009213693967LL,
        2305843009213693971LL, 2305843009213693973LL, 2305843009213693977LL,
        2305843009213693989LL};

    std::chrono::steady_clock::time_point start_time =
        std::chrono::steady_clock::now();

    ThreadPool *pool = new ThreadPool(20);

    std::vector<std::future<bool>> miller_results;
    mtpk::Primality prim;
    for (auto n : nums) {
        miller_results.emplace_back(pool->enqueue(
            [&prim, n]() { return prim.miller_rabin_prime(n, 100); }));
    }

    // Print the results
    std::cout << "Results:\n";
    std::cout << "Miller-Rabin" << std::endl;
    for (size_t i = 0; i < miller_results.size(); i++) {
        bool is_prime = miller_results[i].get();
        std::cout << nums[i] << " is " << (is_prime ? "prime" : "composite")
                  << "\n";
    }

    delete pool;
    ThreadPool *new_pool = new ThreadPool(20);

    std::vector<std::future<bool>> AKS_results;

    for (auto n : nums) {
        AKS_results.emplace_back(
            new_pool->enqueue([&prim, n]() { return prim.AKS(n); }));
    }

    std::cout << "\nAKS" << std::endl;
    for (size_t i = 0; i < AKS_results.size(); i++) {
        bool is_prime = AKS_results[i].get();
        std::cout << nums[i] << " is " << (is_prime ? "prime" : "composite")
                  << "\n";
    }

    delete new_pool;
    /*

        std::vector<std::future<bool>> results;
        for (int64_t n : nums) {
            results.emplace_back(pool.enqueue(IsPrime, n));
        }

        for (size_t i = 0; i < results.size(); ++i) {
            std::cout << nums[i] << " is "
                      << (results[i].get() ? "" : "not ") << "prime"
                      << std::endl;
        }
    */

    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    std::cout << "Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " ms" << std::endl;

    return 0;
}
