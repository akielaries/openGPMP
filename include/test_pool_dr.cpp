#include "nt/factorization.hpp"
#include "test_pool.hpp"
#include <cstdint>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

Function_pool func_pool;

class quit_worker_exception : public std::exception {};

void example_function() {
    std::cout << "bla" << std::endl;
}

int main() {
    std::cout << "starting operation" << std::endl;
    int num_threads = std::thread::hardware_concurrency();
    std::cout << "number of threads = " << num_threads << std::endl;
    std::vector<std::thread> thread_pool;
    for (int i = 0; i < num_threads; i++) {
        thread_pool.push_back(
            std::thread(&Function_pool::infinite_loop_func, &func_pool));
    }

    /*
    std::vector<int64_t> nums_to_factorize = {
        9223372036854775803, 9223372036854775807, 9223372036854775303,
        4567890123456789,  5678901234567890,  6789012345678901,
        7890123456789012,  8901234567890123};*/
    /*    std::vector<uint64_t> nums_to_factorize = {
            9223372036854775803LL,   9223372036854775805LL,
            9223372036854775303LL,   4567890123456789LL,
            5678901234567890LL,    6789012345678901LL,
            7890123456789012LL,    8901234567890123LL,
            9999999967LL,          12345678901234567LL,
            987654321987654321LL,  2147483647LL,
            9223372036854775783LL, 1311768467463790320LL,
            7237005577332262210LL, 3037000499LL,
            2305843009213693951LL, 2305843009213693967LL,
            2305843009213693971LL, 2305843009213693973LL,
            2305843009213693977LL, 2305843009213693989LL};*/
    std::vector<int32_t> nums_to_factorize = {
        2147483647, 123456789, 987654321, 1234567,  7654321,  31415926,
        27182818,   17171717,  88888888,  55555555, 33333333, 22222222,
        44444444,   99999999,  77777777,  88888888, 66666666, 33333333,
        55555555,   22222222,  77777777};

    mtpk::Factorization factorization;

    // here we should send our functions
    for (int64_t num : nums_to_factorize) {
        // func_pool.push(example_function);
        // func_pool.push([&factorization, num](){
        // factorization.pollard_rho(num); });
        func_pool.push([&factorization, num]() {
            int64_t result = factorization.pollard_rho(num);
            std::cout << result << std::endl;
        });
    }
    func_pool.done();
    for (uint64_t i = 0; i < thread_pool.size(); i++) {
        thread_pool.at(i).join();
    }
    // return 0;
}
