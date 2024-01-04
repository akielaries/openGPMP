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

#ifdef __HAS_NVCC__

#include "lib/montecarlo.cuh" // CUDA monte carlo methods
#include "lib/primes.cuh"     // CUDA prime number methods
#include <cuda.h>             // CUDA C header
#include <curand_kernel.h>    // RAND for CUDA devices
#include <stdio.h>            // C STD IO

#endif

#include <chrono>   // cpp timing related methods
#include <cstring>  // C styled strings
#include <ctime>    // C time related methods
#include <fstream>  // for file RW
#include <iostream> // for std IO
#include <limits.h> // defined limit constants
#include <thread>   // for thread access
#include <unistd.h> // POSIX API
#include <vector>   // vector DS

// large list of prime numbers
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

    // print the results
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

// if host has NVCC installed
#ifdef __HAS_NVCC__

// does not achieve same accuracy as CPU based Miller-Rabin
void gpu_bench_miller_rabin() {
    clock_t start, stop;
    int n = nums.size();
    int iters = 120000;

    // Allocate device memory for input and output arrays
    uint32_t *d_input;
    bool *d_output;

    start = clock();

    cudaMalloc((void **)&d_input, n * sizeof(uint32_t));
    cudaMalloc((void **)&d_output, n * sizeof(bool));

    // Copy input data to device
    cudaMemcpy(d_input,
               nums.data(),
               n * sizeof(uint32_t),
               cudaMemcpyHostToDevice);

    // Launch a separate thread for each element in the array
    int threads = 256;
    int blocks = (n + threads - 1) / threads;

    run_gpu_miller_rabin(d_input, d_output, iters, threads, blocks);

    // miller_rabin_kernel<<<blocks, threads>>>(d_input,
    //                                                         d_output,
    //                                                         iters);

    // Copy the results back to the host
    bool *results = new bool[n];
    cudaMemcpy(results, d_output, n * sizeof(bool), cudaMemcpyDeviceToHost);

    stop = clock();

    // print results
    for (int i = 0; i < n; ++i) {
        if (results[i]) {
            std::cout << nums[i] << " is PRIME...\n";
        } else {
            std::cout << nums[i] << " is COMPOSITE...\n";
        }
    }

    // Clean up
    cudaFree(d_input);
    cudaFree(d_output);
    delete[] results;

    printf("Finished in %f s.\n", (stop - start) / (float)CLOCKS_PER_SEC);
}

void gpu_bench_monte_carlo() {
    clock_t start, stop;
    float host[BLOCKS * THREADS];
    float *dev;
    curandState *devStates;
    int total_trials = TRIALS_PER_THREAD * BLOCKS * THREADS;

    printf("# of trials per thread = %d, # of blocks = %d, # of threads/block "
           "= %d, total trials %d.\n",
           TRIALS_PER_THREAD,
           BLOCKS,
           THREADS,
           total_trials);

    start = clock();

    cudaMalloc((void **)&dev,
               BLOCKS * THREADS *
                   sizeof(float)); // allocate device mem. for counts

    cudaMalloc((void **)&devStates, THREADS * BLOCKS * sizeof(curandState));

    start = clock();

    run_gpu_monte_carlo(dev, devStates);

    cudaMemcpy(host,
               dev,
               BLOCKS * THREADS * sizeof(float),
               cudaMemcpyDeviceToHost); // return results

    float pi_gpu;
    for (int i = 0; i < BLOCKS * THREADS; i++) {
        pi_gpu += host[i];
    }

    pi_gpu /= (BLOCKS * THREADS);

    stop = clock();

    printf("GPU pi calculated in %f s.\n",
           (stop - start) / (float)CLOCKS_PER_SEC);

    printf("CUDA estimate of PI = %f [error of %f]\n", pi_gpu, pi_gpu - PI);
}

#endif

// Function to run system monitor as a background process
// TODO this should be run even when -b is passed in but on a seperate
// thread?
void daemon(int interval) {
    // System class obj
    System sys;

    // CPU/PROC INFO, POPULATES VARIOUS CLASS VARS
    sys.cpu_info(); // get once outside of main loop
    // fetch hostname and current user
    char host[HOST_NAME_MAX];
    char user[LOGIN_NAME_MAX];
    gethostname(host, HOST_NAME_MAX);
    getlogin_r(user, LOGIN_NAME_MAX);

    // float starting_cpu_temp = sys.cpu_idle_temp();
    // float starting_cpu_usg = sys.cpu_load();
    // std::cout << starting_cpu_temp << starting_cpu_usg << std::endl;

    // infinite loop for continuous collection
    while (true) {
        // GET CURRENT DATE FMT IN mmddyyyy
        // this will rely on system timezone (/etc/timezone)
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm local_tm = *std::localtime(&time);

        // extract info for date and time
        char date_str[9]; // MMDDYYYY + '\0'
        char time_str[7]; // HHMMSS + '\0'

        std::strftime(date_str, sizeof(date_str), "%m%d%Y", &local_tm);
        std::strftime(time_str, sizeof(time_str), "%H%M%S", &local_tm);

        // CSV FILE NAME with only the date
        std::string filename = "HOST_" + std::string(user) + "_" +
                               std::string(host) + std::string(date_str) +
                               ".csv";

        // open CSV to append
        std::ofstream csvFile(filename, std::ios::app);

        if (csvFile.is_open()) {
            // If the file is empty, add headers
            if (csvFile.tellp() == 0) {
                csvFile << "TIME,CPU_MODEL,NUM_CPUs,PROCS,BogoMIPS,CPU_USG,"
                        << "CPU_TEMP,TOTAL_VRAM,USED_VRAM,FREE_VRAM,"
                        << "TOTAL_RAM,USED_RAM,FREE_RAM\n";
#ifdef __HAS_NVCC__
                csvFile << "GPU_MODEL,"
                        << ",TOTAL_GPU_MEM,USED_GPU_MEM, FREE_GPU_MEM";
#endif
            }

            // CURRENT MEMORY USAGE, THIS METHOD POPULATE VARIOUS CLASS VARS
            sys.mem_stats();
            // CPU/PROC INFO, POPULATES VARIOUS CLASS VARS
            sys.cpu_info();

#ifdef __HAS_NVCC__
            sys.gpu_info();
            sys.gpu_info_print();
#endif

            // WRITE ALL INFO TO CSV FILE
            csvFile << time << ","            // time
                    << sys.cpu_model << ","   // CPU model
                    << sys.num_proc << ","    // number of CPUs
                    << sys.ps_count() << ","  // process count
                    << sys.bogus_mips << ","  // bogoMIPS
                    << sys.cpu_load() << ","  // CPU load %
                    << sys.cpu_temp() << ","  // CPU temp
                    << sys.v_mem_total << "," // VRAM total
                    << sys.v_mem_used << ","  // VRAM used
                    << sys.v_mem_free << ","  // VRAM free
                    << sys.p_mem_total << "," // RAM total
                    << sys.p_mem_used << ","  // RAM USED
                    << sys.p_mem_free         // RAM free
                ;
#ifdef __HAS_NVCC__
            // WRITE NVIDIA GPU INFO TO CSV FILE
            csvFile << "," << sys.name << ",";
#endif

            // move to next line
            csvFile << "\n";
            // close file
            csvFile.close();
        } else {
            std::cerr << "Error: Unable to open file " << filename
                      << " for writing.\n";
        }

        // sleep
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
}

void usage(const char *bin) {
    std::cout << "Usage: " << bin << " [-d | -b cpu | gpu ] -o" << std::endl;

    std::cout << "  -d : daemon mode to monitor system information\n";
    std::cout << "  -b : benchmark mode to run system stress tests with live "
                 "monitoring\n";

    std::cout << "    cpu - run CPU-based benchmarks\n";
    std::cout << "    gpu - run GPU-based benchmarks\n";
    std::cout << "  -o : output file TODO\n"; // TODO
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    } else {
        if (strcmp(argv[1], "-b") == 0) {
            std::cout << "Starting benchmark...\n\n";
            if (argc < 3) {
                std::cerr
                    << "Error: Specify 'cpu' or 'gpu' after the -b flag.\n";
                exit(EXIT_FAILURE);
            }

            std::string mode(argv[2]);

            // System class obj
            System sys;

            // if -b cpu
            if (mode == "cpu") {
                std::cout << "<--------- CPU TESTS --------->\n";
                // display CPU information and number of running processes from
                // `ps`
                sys.cpu_info();
                sys.ps_count();

                sys.cpu_usage();
                sys.mem_info();
                sys.cpu_temp();
                // TODO get idle temperature at the start of this benchmark to
                // determine the "idle starting" temperature. store in struct?
                // when would it get called?
                // TODO FIXME I am thinking this system info should be logged
                // from a separate thread

                std::cout << "Primality tests with Miller-Rabin algorithm...\n";

                bench_naive_primes(nums);
                bench_threadpool_primes(nums);

                // TODO where/when should these be called? should these
                // functions update values located within a struct? think about
                // this...
                sys.cpu_usage();
                sys.mem_info();
                sys.cpu_temp();

                std::cout << "Pi estimation using Monte Carlo methods...\n";
                bench_monte_carlo();
                sys.cpu_usage();
                sys.mem_info();
                sys.cpu_temp();

                std::cout << "Discrete Fourier Transform...\n";

                std::cout << "Fast Fourier Transform...\n";

                // TODO: finish out some openGPMP matrix operations for this
                // to compare against the F90 methods, openBLAS, and finally
                // corresponding GPU implementations.
                // Include benchmarks against Naive Implementations as well
                std::cout << "Matrix...\n";
            }

            // if -b gpu
            else if (mode == "gpu") {
                // if host has NVCC installed

                std::cout << "<--------- GPU TESTS --------->\n";
#ifdef __HAS_NVCC__

                std::cout << "NVIDIA device found!\n";
                gpu_bench_monte_carlo();
                gpu_bench_miller_rabin();

#else
                std::cout << "No NVIDIA device found!\n";
#endif
            } else {
                std::cerr << "Error: Invalid mode. Specify 'cpu' or 'gpu' "
                             "after -b flag\n";
                exit(EXIT_FAILURE);
            }
        }

        // daemon
        if (strcmp(argv[1], "-d") == 0) {
            // TODO implement "daemon"
            std::cout << "Running as daemon...\n";
            daemon(2);
        }
    }
    return 0;
}
