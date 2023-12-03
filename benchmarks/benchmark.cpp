/**
 * Driver for this benchmarks project featuring cmd line options and functions
 * for benchmark program runs...
 *
 * -d (DAEMON)      live system monitoring
 * -b (BENCHMARK)   run benchmark system stress programs
 */

#include "lib/montecarlo.hpp" // monte carlo methods
#include "lib/primes.hpp"     // prime number methods
#include "lib/sys.hpp"        // system information methods
#include "lib/threadpool.hpp" // threadpool methods
#include <chrono>             // cpp timing related methods
#include <cstring>            // C styled strings
#include <ctime>              // C time related methods
#include <fstream>            // for file RW
#include <iostream>           // for std IO
#include <limits.h>           // defined limit constants
#include <thread>             // for thread access
#include <unistd.h>           // POSIX API
#include <vector>             // vector DS

void bench_naive_primes(std::vector<uint32_t> nums) {
    // TODO at the end of each benchmark run we should log memory
    std::cout << "Miller-Rabin sequential...\n";
    // TIME START
    std::chrono::steady_clock::time_point start_time =
        std::chrono::steady_clock::now();

    for (uint32_t n : nums) {
        if (miller_rabin(n, 120000)) {
            std::cout << n << " is PRIME...\n";
        } else {
            std::cout << n << " is COMPOSITE...\n";
        }
    }

    // TIME END
    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    std::cout << "Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " ms" << std::endl;
}

void bench_threadpool_primes(std::vector<uint32_t> nums) {
    // declares a threadpool with 4 threads
    ThreadPool *pool = new ThreadPool(4);

    std::vector<std::future<bool>> miller_results;

    std::chrono::steady_clock::time_point start_time =
        std::chrono::steady_clock::now();
    for (auto n : nums) {
        miller_results.emplace_back(
            pool->enqueue([n]() { return miller_rabin(n, 120000); }));
    }

    // Print the results
    std::cout << "\nResults:\n";
    std::cout << "Miller-Rabin with ThreadPool" << std::endl;
    for (size_t i = 0; i < miller_results.size(); i++) {
        bool is_prime = miller_results[i].get();
        std::cout << nums[i] << " is " << (is_prime ? "PRIME" : "COMPOSITE")
                  << "\n";
    }
    delete pool;

    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    std::cout << "Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " ms" << std::endl;
}

void bench_threadpool_primes_dispatch(std::vector<uint32_t> nums) {
    std::vector<std::future<bool>> miller_results;

    ThreadPool *pool = new ThreadPool(4);

    std::chrono::steady_clock::time_point start_time =
        std::chrono::steady_clock::now();

    for (auto n : nums) {
        // enqueue the function call to the thread pool using the
        // ThreadDispatch.dispatch() function
        miller_results.emplace_back(
            ThreadDispatch().dispatch(*pool, miller_rabin, n, 120000));
    }

    for (size_t i = 0; i < miller_results.size(); i++) {
        bool is_prime = miller_results[i].get();
        std::cout << nums[i] << " is " << (is_prime ? "PRIME" : "COMPOSITE")
                  << "\n";
    }
    delete pool;

    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    std::cout << "Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " ms" << std::endl;
}

void bench_monte_carlo() {
    int trials_per_thread = 4096;
    int threads = 256;
    int blocks = 256;
    int total_trials = trials_per_thread * threads * blocks;

    std::cout << "Trials/thread: " << trials_per_thread << std::endl;
    std::cout << "Threads: " << threads << std::endl;
    std::cout << "Blocks: " << blocks << std::endl;
    std::cout << "Total trials: " << total_trials << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    double predicted_pi = monte_carlo(total_trials);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;

    std::cout << "Estimated value of pi: " << predicted_pi
              << " in : " << elapsed_time.count() << " seconds" << std::endl;

    long double err = predicted_pi - PI;
    std::cout << "Error of " << err << std::endl;
}

#if defined(__linux__)
// if host has NVCC installed
#ifdef __NVCC__
void gpu_bench_monte_carlo() {
    std::cout << "This should be a call to some GPU monte carlo method...\n";
}
#endif
#endif

// Function to run system monitor as a background process
void daemon() {
    // System class obj
    System sys;
    // float starting_cpu_temp = sys.cpu_idle_temp();
    // float starting_cpu_usg = sys.cpu_stats();
    //  std::cout << starting_cpu_temp << starting_cpu_usg << std::endl;

    // infinite loop for continuous collection
    while (true) {
        // GET CURRENT DATE FMT IN mmddyyyy
        // this will rely on system timezone (/etc/timezone)
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm local_tm = *std::localtime(&time);

        // Separate variables for date and time
        char date_str[9]; // MMDDYYYY + '\0'
        char time_str[7]; // HHMMSS + '\0'

        std::strftime(date_str, sizeof(date_str), "%m%d%Y", &local_tm);
        std::strftime(time_str, sizeof(time_str), "%H%M%S", &local_tm);

        // Print date and time
        std::cout << "Current date: " << date_str << std::endl;
        std::cout << "Current time: " << time_str << std::endl;

        // CSV FILE NAME with only the date
        std::string filename = "sysinfo_" + std::string(date_str) + ".csv";

        // open the CSV file for appending
        std::ofstream csvFile(filename, std::ios::app);

        if (csvFile.is_open()) {
            // CURRENT CPU TEMPERATURE
            float curr_cpu_temp = sys.cpu_temp();
            // CURRENT CPU USAGE (%)
            float curr_cpu_usg = sys.cpu_stats();
            // CURRENT MEMORY USAGE, THIS METHOD POPULATE VARIOUS CLASS VARS
            sys.mem_stats();

            std::cout << curr_cpu_temp << "\n" << curr_cpu_usg << std::endl;

            // virtual memory
            std::cout << "TOTAL VMEM: " << sys.v_mem_total
                      << "\n FREE VMEM: " << sys.v_mem_free
                      << "\n USED VMEM: " << sys.v_mem_used << std::endl;
            // physical memory
            std::cout << "TOTAL PMEM: " << sys.p_mem_total
                      << "\n FREE PMEM: " << sys.p_mem_free
                      << "\n USED PMEM: " << sys.p_mem_used << std::endl;

            // WRITE ALL INFO TO CSV FILE
            csvFile << curr_cpu_temp << ","; // Add other data as needed
            // Add more fields and data to the CSV file as needed

            csvFile << "\n"; // Move to the next line for the next entry
            csvFile.close(); // Close the file after writing
        } else {
            std::cerr << "Error: Unable to open file " << filename
                      << " for writing.\n";
        }

        std::cout << "SLEEPING\n";
        // sleep
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void usage(const char *programName) {
    std::cout << "Usage: " << programName << " [-d | -b]" << std::endl;
    std::cout << "  -d : daemon mode to monitor system information\n";
    std::cout << "  -b : benchmark mode to run system stress tests with live "
                 "monitoring\n";
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    } else {
        if (strcmp(argv[1], "-b") == 0) {
            std::cout << "Starting benchmark...\n\n";

            System sys;

            // display CPU information and number of running processes from `ps`
            sys.cpu_info();
            sys.proc_info();

            sys.cpu_usage();
            sys.mem_info();
            sys.cpu_temp();
            // TODO get idle temperature at the start of this benchmark to
            // determine the "idle starting" temperature. store in struct? when
            // would it get called?
            // TODO FIXME I am thinking this system info should be logged from a
            // separate thread

            std::cout
                << "Starting with primality testing using the Miller-Rabin "
                   "algorithm...\n";

            std::vector<uint32_t> nums = {
                1000000007, // A large 32-bit integer PRIME
                2147483647, // The largest 32-bit signed integer PRIME
                97,         // A PRIME number
                123456789,  // Another large 32-bit integer
                19,         // A PRIME number
                42,         // Just a random number
                31,         // A PRIME number
                987654321,  // Yet another large 32-bit integer
                37,         // A PRIME number
                123,        // Just another number
                17,         // A PRIME number
                999999999,  // And another large 32-bit integer
                23,         // A PRIME number
                777777777,  // Large 32-bit integer
                13,         // A PRIME number
                234567890,  // Large 32-bit integer
                11,         // A PRIME number
                987654321,  // Repeating value for demonstration
                7,          // A PRIME number
                8675309,    // Another large 32-bit integer
                709,        // A PRIME number
                5381,       // A PRIME number
                52711,      // A PRIME number
                167449,     // A PRIME number
                648391,     // A PRIME number
                1128889,    // A PRIME number
                2269733,    // A PRIME number
                3042161,    // A PRIME number
                4535189,    // A PRIME number
                7474967,    // A PRIME number
                9737333,    // A PRIME number
                14161729,   // A PRIME number
                17624813,   // A PRIME number
                19734581,   // A PRIME number
                23391799,   // A PRIME number
                29499439,   // A PRIME number
                37139213    // A PRIME number
            };

            bench_naive_primes(nums);
            bench_threadpool_primes(nums);

            // TODO where/when should these be called? should these functions
            // update values located within a struct? think about this...
            sys.cpu_usage();
            sys.mem_info();
            sys.cpu_temp();

            bench_threadpool_primes_dispatch(nums);

            sys.cpu_usage();
            sys.mem_info();
            sys.cpu_temp();

// if host has NVCC installed
#ifdef __NVCC__
            std::cout << "NVIDIA DEVICE!\n";
#endif

            // monte_carlo();
        }
        if (strcmp(argv[1], "-d") == 0) {
            // TODO implement "daemon"
            std::cout << "Running as daemon...\n";
            daemon();
        }
    }
    return 0;
}
