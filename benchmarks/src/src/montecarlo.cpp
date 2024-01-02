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
