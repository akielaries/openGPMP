/**
 * Driver for showing how to use the core functionalities of the Number Theory
 * module by itself as well as with the openMTPK ThreadPool. This features
 * functions related to primes specifically generation and testing.
 *
 * @example primes.cpp
 */
#include <chrono>
#include <cmath>
#include <iostream>
#include <openMTPK/core/threadpool.hpp>
#include <openMTPK/nt/prime_gen.hpp>
#include <openMTPK/nt/prime_test.hpp>
#include <vector>

void testing_miller(std::vector<int64_t> nums) {
    /* SEQUENTIAL MILLER-RABIN TEST */
    //    std::chrono::steady_clock::time_point start_time =
    //        std::chrono::steady_clock::now();
    auto start = std::chrono::high_resolution_clock::now();

    mtpk::PrimalityTest prims;
    std::cout << "Miller-Rabin sequentially without ThreadPool" << std::endl;

    for (uint64_t n : nums) {
        if (prims.miller_rabin_prime(n, 120000))
            std::cout << n << " is prime" << std::endl;
        else
            std::cout << n << " is composite" << std::endl;
    }

    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::nano> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " ns\n";

    //    std::cout << "Time elapsed: "
    //              << std::chrono::duration_cast<std::chrono::milliseconds>(
    //                     end_time - start_time)
    //                     .count()
    //              << " ms" << std::endl;
}

void testing_miller_thread(std::vector<int64_t> nums) {
    /* MILLER-RABIN TEST USING THREADPOOL WITH MANUAL ENQUEUE */
    //    std::chrono::steady_clock::time_point start_time =
    //        std::chrono::steady_clock::now();
    auto start = std::chrono::high_resolution_clock::now();

    // declares a threadpool with 4 threads
    mtpk::core::ThreadPool *pool = new mtpk::core::ThreadPool(4);

    std::vector<std::future<bool>> miller_results;
    mtpk::PrimalityTest prim;
    for (auto n : nums) {
        miller_results.emplace_back(pool->enqueue(
            [&prim, n]() { return prim.miller_rabin_prime(n, 120000); }));
    }

    // Print the results
    std::cout << "\nResults:\n";
    std::cout << "Miller-Rabin with ThreadPool" << std::endl;
    for (size_t i = 0; i < miller_results.size(); i++) {
        bool is_prime = miller_results[i].get();
        std::cout << nums[i] << " is " << (is_prime ? "prime" : "composite")
                  << "\n";
    }
    delete pool;

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::nano> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " ns\n";

    //    std::chrono::steady_clock::time_point end_time =
    //        std::chrono::steady_clock::now();

    //    std::cout << "Time elapsed: "
    //              << std::chrono::duration_cast<std::chrono::milliseconds>(
    //                     end_time - start_time)
    //                    .count()
    //              << " ms" << std::endl;
}

void testing_new_miller(std::vector<int64_t> nums) {
    /* MILLER-RABIN USING THREADPOOL DISPATCH UTILITY FUNCTION */
    //    std::chrono::steady_clock::time_point start_time =
    //        std::chrono::steady_clock::now();
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::future<bool>> miller_results;

    mtpk::PrimalityTest prim;
    mtpk::core::ThreadPool *pool = new mtpk::core::ThreadPool(4);

    for (auto n : nums) {
        // enqueue the function call to the thread pool using the
        // ThreadDispatch.dispatch() function
        miller_results.emplace_back(mtpk::core::ThreadDispatch().dispatch(
            *pool, &mtpk::PrimalityTest::miller_rabin_prime, &prim, n, 120000));
    }

    // Print the results
    std::cout << "\nResults:\n";
    std::cout << "Miller-Rabin with ThreadPool using ThreadDispatch.dispatch()"
              << std::endl;

    for (size_t i = 0; i < miller_results.size(); i++) {
        bool is_prime = miller_results[i].get();
        std::cout << nums[i] << " is " << (is_prime ? "prime" : "composite")
                  << "\n";
    }
    delete pool;
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::nano> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " ns\n";

    //    std::chrono::steady_clock::time_point end_time =
    //        std::chrono::steady_clock::now();

    //    std::cout << "Time elapsed: "
    //              << std::chrono::duration_cast<std::chrono::milliseconds>(
    //                     end_time - start_time)
    //                     .count()
    //              << " ms" << std::endl;
}

int main() {
    std::cout << "BASIC NUMBER THEORY OPERATIONS\n" << std::endl;
    // declare primality class object
    mtpk::PrimalityTest p;

    std::cout << "<--------- IS IT PRIME? --------->\n";
    int a = 9;
    // check if an integer is prime or not
    bool is_it = p.is_prime(a);

    std::cout << a << " is prime? : ";
    is_it ? std::cout << "true\n" : std::cout << "false\n" << std::endl;

    int b = 2;
    bool is_it2 = p.is_prime(b);

    std::cout << b << " is prime? : ";
    is_it2 ? std::cout << "true\n" : std::cout << "false\n" << std::endl;
    std::cout << "\n";

    std::cout << "<--------- MILLER-RABIN METHOD --------->\n";
    int min_num = 1;
    // display the prime numbers smaller than a given value
    int max_num = 100;
    // number of iterations
    int iters = 4;
    /*
     * calculate the solution, the method doesn't return a value,
     * prints the values
     */
    p.miller_rabin(iters, min_num, max_num);
    p.miller_rabin(iters, 25, 50);
    p.miller_rabin(iters, 30, 3000);

    std::cout << "\n";

    std::cout << "<--------- CARMICHAEL NUMBERS --------->\n";
    int cm_test = 500;
    bool carm_num = p.carmichael_num(cm_test);

    int cm_test1 = 561;
    bool carm_num1 = p.carmichael_num(cm_test1);

    int cm_test2 = 1105;
    bool carm_num2 = p.carmichael_num(cm_test2);

    std::cout << cm_test << " is a carmichael number : ";
    carm_num ? std::cout << "true\n" : std::cout << "false\n";

    std::cout << cm_test1 << " is a carmichael number : ";
    carm_num1 ? std::cout << "true\n" : std::cout << "false\n";

    std::cout << cm_test2 << " is a carmichael number : ";
    carm_num2 ? std::cout << "true\n" : std::cout << "false\n";

    std::cout << "\n";
    /*
     * Power Modulo function
     */
    int pow_a = 3;
    int pow_b = 2;
    int pow_c = 2;
    // returns (a^b) % c
    int pow_res = p.mod_pow(pow_a, pow_b, pow_c);
    printf("%d ^ %d %% %d = %d\n", pow_a, pow_b, pow_c, pow_res);

    int pow_d = 5;
    int pow_e = 2;
    int pow_f = 7;

    int pow_res_1 = p.mod_pow(pow_d, pow_e, pow_f);
    printf("%d ^ %d %% %d = %d\n", pow_d, pow_e, pow_f, pow_res_1);

    int pow_g = 8;
    int pow_h = 9;
    int pow_i = 3;

    int pow_res_2 = p.mod_pow(pow_g, pow_h, pow_i);
    printf("%d ^ %d %% %d = %d\n", pow_g, pow_h, pow_i, pow_res_2);

    bool cmp = p.miller_rabin_prime(5, 4);
    std::cout << "miller_rabin_prime: " << cmp << "\n";
    std::cout << "\n";
    /*
     * Jacobian
     */

    /*
     * Solovay-Strassen Primality Test
     */
    int ss_0 = 15;
    if (p.solovoy_strassen(ss_0, 50))
        printf("%d is prime\n", ss_0);
    else
        printf("%d is composite\n", ss_0);

    std::cout << "\n";

    // example vector of 64 bit integers
    std::vector<int64_t> nums = {
        9223372036854775803,   9223372036854775807,   9223372036854775303,
        4567890123456789LL,    5678901234567890LL,    6789012345678901LL,
        7890123456789012LL,    8901234567890123LL,    9999999967LL,
        12345678901234567LL,   987654321987654321LL,  2147483647LL,
        9223372036854775783LL, 1311768467463790320LL, 7237005577332262210LL,
        3037000499LL,          2305843009213693951LL, 2305843009213693967LL,
        2305843009213693971LL, 2305843009213693973LL, 2305843009213693977LL,
        2305843009213693989LL};

    testing_miller(nums);
    std::cout << "<--------- USING THREADPOOL --------->\n";

    testing_miller_thread(nums);
    testing_new_miller(nums);
    testing_miller_thread(nums);

    // vector if 64 bit integers

    return 0;
}
