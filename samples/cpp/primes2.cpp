#include <chrono>
#include <cmath>
#include <iostream>
#include <openGPMP/nt/prime_gen.hpp>
#include <vector>
#include <random>



int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    int max_number = 50000;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> primes = gpmp::PrimalityGen::sieve_of_eratosthenes(max_number);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Prime numbers generated: " << primes.size() << std::endl;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    // Generate a random prime number from the list
    if (!primes.empty()) {
        std::uniform_int_distribution<> distrib(0, primes.size() - 1);
        int random_index = distrib(gen);
        std::cout << "Random prime number: " << primes[random_index] << std::endl;
    } else {
        std::cout << "No prime numbers generated." << std::endl;
    }

    return 0;
}

