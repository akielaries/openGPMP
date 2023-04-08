/*
 * Driver for showing how to use the core basic and elementary
 * functionalities of the Number Theory module
 *
 */
#include <iostream>
//#include <openMTPK/nt/factorization.hpp>
//#include <openMTPK/threadpool.hpp>
#include "../../include/nt/factorization.hpp"
#include "../../include/threadpool.hpp"

int main() {
    std::vector<int64_t> nums_to_factorize = {
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

    const int num_threads = 4; // specify number of threads to use
    const int batch_size =
        num_threads * 2; // calculate batch size based on number of threads

    std::vector<std::future<int64_t>> results;
    mtpk::ThreadPool pool(num_threads);
    mtpk::Factorization factors;

    for (int i = 0; i < nums_to_factorize.size(); i += batch_size) {
        std::vector<int64_t>::const_iterator start =
            nums_to_factorize.begin() + i;
        std::vector<int64_t>::const_iterator end =
            nums_to_factorize.begin() +
            std::min(i + batch_size, (int)nums_to_factorize.size());

        for (const auto &num : std::vector<int64_t>(start, end)) {
            results.emplace_back(pool.enqueue(
                &mtpk::Factorization::pollard_rho, &factors, num));
        }

        for (auto &res : results) {
            std::cout << res.get() << std::endl;
        }
        results.clear();
    }

    return 0;
}
