/**
 * Driver for showing how to use the core functionalities of the Number Theory
 * module by itself as well as with the openMTPK ThreadPool. This features
 * functions related to integer factorization.
 *
 * @example factors.cpp
 */
#include <chrono>
#include <cmath>
#include <iostream>
#include <openMTPK/core/threadpool.hpp>
#include <openMTPK/nt/factorization.hpp>
#include <vector>

int main() {
    mtpk::Factorization factorization;

    // find prime factor of 123456789
    int64_t n = 9223372036854775803;
    int64_t factor = factorization.pollard_rho(n);

    // print the result
    std::cout << "The smallest prime factor of " << n << " is " << factor
              << std::endl;

    /******* EXAMPLE USING openMTPK's THREADPOOL *******/
    //
    // specify the numbers to factorize
    // pollard_rho accepts 64 bit integers
    // std::vector<int64_t> nums_to_factorize = {
    //    9223372036854775803, 9223372036854775807, 9223372036854775303,
    //    4567890123456789LL,  5678901234567890LL,  6789012345678901LL,
    //    7890123456789012LL,  8901234567890123LL};
    std::vector<uint64_t> nums_to_factorize = {
        9223372036854775803,   9223372036854775807,   9223372036854775303,
        4567890123456789LL,    5678901234567890LL,    6789012345678901LL,
        7890123456789012LL,    8901234567890123LL,    9999999967LL,
        12345678901234567LL,   987654321987654321LL,  2147483647LL,
        9223372036854775783LL, 1311768467463790320LL, 7237005577332262210LL,
        3037000499LL,          2305843009213693951LL, 2305843009213693967LL,
        2305843009213693971LL, 2305843009213693973LL, 2305843009213693977LL,
        2305843009213693989LL};

    // std::vector<std::future<int64_t>> results =
    //    factorization.pollard_rho_thread(nums_to_factorize);

    //    for (auto &res : results) {
    //        std::cout << res.get() << std::endl;
    //    }

    std::vector<std::future<uint64_t>> results;
    mtpk::core::ThreadPool *pool = new mtpk::core::ThreadPool(2);
    mtpk::Factorization factors;
    for (const auto &num : nums_to_factorize) {
        results.emplace_back(mtpk::core::ThreadDispatch().dispatch(
            *pool, &mtpk::Factorization::pollard_rho, &factors, num));
    }

    for (auto &res : results) {
        std::cout << res.get() << std::endl;
    }

    delete pool;

    return 0;
}
