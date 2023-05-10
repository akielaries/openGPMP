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
 * seen here : https://akielaries.github.io/openMTPK/ along with
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
#include <iostream>
#include <cstdint>

uint32_t mtpk::core::rndm::LCG(uint32_t lower, uint32_t upper) {
    uint32_t mod = __32BIT_1;
    uint32_t mult = 1664525;
    uint32_t incr = 1013904223;
    // set seed = current time
    uint32_t seed = 
        std::chrono::system_clock::now().time_since_epoch().count();
    
    // Linear Congruential Generator algorithm
    uint32_t res = (mult * seed + incr) % mod; 

    return res;
}

uint64_t mtpk::core::rndm::LCGl(uint64_t lower, uint64_t upper) {
    uint64_t mod = __64BIT_1;
    uint64_t mult = 6364136223846793005;
    uint64_t incr = 1442695040888963407;
    // set seed = current time
    uint64_t seed = 
        std::chrono::system_clock::now().time_since_epoch().count();
     
    // Linear Congruential Generator algorithm
    uint64_t res = (mult * seed + incr) % mod; 

    return res;
}


