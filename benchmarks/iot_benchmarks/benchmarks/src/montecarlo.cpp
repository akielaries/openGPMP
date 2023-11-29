/**
 * A Monte Carlo method is really a problem dealing with random distribution
 * and random sampling related technique. In this case and within this file
 * we use a "Monte Carlo Method" from what is talked about in the video below
 * specifically when the author talks about predicting the number pi π using
 * random sampling by "dropping marbles" into a square and determining how
 * many are dropped within 1/4 of the square. The number of successes divided
 * by the number of total attempts will our prediction of pi π
 *
 * https://www.youtube.com/watch?v=7ESK5SaP-bc
 */
#include "../lib/montecarlo.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>

#define PI 3.1415926535

double monte_carlo(int total_trials) {
    int successes = 0;
    double x, y;

    // Initialize a random number generator
    // TODO set a seed to be used for this PRNG and in montecarlo.cu
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < total_trials; i++) {
        x = dis(gen);
        y = dis(gen);
        // Check if the point is inside the unit circle
        successes += (x * x + y * y <= 1.0);
    }

    // Estimate pi
    double predicted_pi = 4.0 * static_cast<double>(successes) / total_trials;

    return predicted_pi;
}

float host_monte_carlo(long trials) {
    float x, y;
    long points_in_circle;
    for (long i = 0; i < trials; i++) {
        x = rand() / (float)RAND_MAX;
        y = rand() / (float)RAND_MAX;
        points_in_circle += (x * x + y * y <= 1.0f);
    }
    return 4.0f * points_in_circle / trials;
}
/*
int main() {
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

    return 0;
}
*/
