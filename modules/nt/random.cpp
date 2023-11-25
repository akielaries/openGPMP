/*************************************************************************
 *
 *  Project
 *                        __  __ _______ _____  _  __
 *                       |  \/  |__   __|  __ \| |/ /
 *  ___  _ __   ___ _ __ | \  / |  | |  | |__) | ' /
 * / _ \| '_ \ / _ \ '_ \| |\/| |  | |  |  ___/|  <
 *| (_) | |_) |  __/ | | | |  | |  | |  | |    | . \
 * \___/| .__/ \___|_| |_|_|  |_|  |_|  |_|    |_|\_\
 *      | |
 *      |_|
 *
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openGPMP/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/
#include "../../include/nt/random.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>


// dfault constructor
gpmp::core::rndm::LCG::LCG()
    : state(1), multiplier(6364136223846793005ULL), increment(1442695040888963407ULL) {}

// constructor
gpmp::core::rndm::LCG::LCG(uint64_t seed, uint64_t a, uint64_t c) 
    : state(seed), multiplier(a), increment(c) {}

uint64_t gpmp::core::rndm::LCG::operator()() {
    // Ensure the state is non-negative
        state &= 0x7FFFFFFFFFFFFFFFULL;

        // Linear Congruential Generator algorithm
        state = multiplier * state + increment;

        // Overflow handling
        if (state < increment) {
            // Overflow occurred, adjust the state
            state += increment;
        }

        return state;
}

// set seed
void gpmp::core::rndm::LCG::seed(uint64_t new_seed) {
    state = new_seed;
}

// methods to retrieve parameters (optional)
uint64_t gpmp::core::rndm::LCG::get_multiplier() const {
    return multiplier;
}

uint64_t gpmp::core::rndm::LCG::get_increment() const {
    return increment;
}

uint64_t gpmp::core::rndm::LCG::get_seed() const {
    return state;
}

/*
uint32_t gpmp::core::rndm::LCG(uint32_t lower, uint32_t upper, uint32_t seed) {
    uint32_t mod = __32MAX;
    uint32_t mult = 1664525;
    uint32_t incr = 1013904223;

    // set seed = current time
    uint32_t time_seed =
        std::chrono::system_clock::now().time_since_epoch().count();

    uint32_t final_seed = (seed == 0) ? time_seed : seed;

    // Linear Congruential Generator algorithm
    uint32_t res = (mult * final_seed + incr) % mod;

    // trim to range
    res = lower + (res % (upper - lower + 1));

    return res;
}

uint64_t
gpmp::core::rndm::LCG_64(uint64_t lower, uint64_t upper, uint64_t seed) {
    uint64_t mod = __64MAX;
    uint64_t mult = 6364136223846793005ULL; // Large multiplier
    uint64_t incr = 1442695040888963407ULL; // Large increment

    // set seed = current time
    uint64_t time_seed =
        std::chrono::system_clock::now().time_since_epoch().count();

    uint64_t final_seed = (seed == 0) ? time_seed : seed;

    // Linear Congruential Generator algorithm
    uint64_t res = (mult * final_seed + incr) % mod;

    // Calculate the range size
    uint64_t range_size = upper - lower + 1;

    // Avoid division by zero
    if (range_size != 0) {
        // Ensure res is non-negative
        res = res & ((1ULL << 63) - 1);

        // trim to range
        res = lower + (res % range_size);
    }

    return res;
}*/

uint32_t gpmp::core::rndm::rotr32(uint32_t x, unsigned r) {
    return x >> r | x << (-r & 31);
}

uint32_t gpmp::core::rndm::pcg32(void) {
    uint64_t x = __PCG_STATE;
    unsigned count = (unsigned)(x >> 59); // 59 = 64 - 5

    __PCG_STATE = x * __PCG_MULTPLR + __PCG_INCR;
    x ^= x >> 18;                              // 18 = (64 - 27)/2
    return rotr32((uint32_t)(x >> 27), count); // 27 = 32 - 5
}

void gpmp::core::rndm::pcg32_init(uint64_t seed) {
    __PCG_STATE = seed + __PCG_INCR;
    (void)pcg32();
}
