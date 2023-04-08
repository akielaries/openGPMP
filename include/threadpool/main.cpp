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
    std::vector<int64_t> nums = {
        9999998900000007, 9999998900000003, 9999998900000001,
        9999998900000000, 9999998900000009, 9999998900000011,
        9999998900000027, 9999998900000033, 9999998900000087,
        9999998900000093, 9999998900000103, 9999998900000121,
        9999998900000143, 9999998900000169, 9999998900000181,
        9999998900000207, 9999998900000223, 9999998900000249,
        9999998900000257, 9999998900000277, 9999998900000291,
        9999998900000319, 9999998900000321, 9999998900000327,
        9999998900000331, 9999998900000333, 9999998900000349,
        9999998900000351, 9999998900000373, 9999998900000403};

    std::chrono::steady_clock::time_point start_time =
        std::chrono::steady_clock::now();

    ThreadPool pool;

    std::vector<std::future<bool>> results;
    mtpk::Primality prim;
    for (auto n : nums) {
        results.emplace_back(pool.enqueue([&prim, n]() {
            return prim.miller_rabin_prime(n, 99999900);
        }));
    }

    // Print the results
    std::cout << "Results:\n";
    for (size_t i = 0; i < results.size(); i++) {
        bool is_prime = results[i].get();
        std::cout << nums[i] << " is "
                  << (is_prime ? "prime" : "composite") << "\n";
    }
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
