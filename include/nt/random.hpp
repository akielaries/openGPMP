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
/**
 * @file random.hpp
 * @brief Pseudorandom Number Generators
 */
#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdint>

/** RNG CONSTANTS,, adopted from glibc */
#define __16BIT     65536                   /** 2^16        */
#define __16BIT_1   65535                   /** 2^16 - 1    */
#define __32BIT     4294967296              /** 2^32        */
#define __32BIT_1   4294967295              /** 2^32 - 1    */
#define __64BIT     18446744073709600000    /** 2^64        */
#define __64BIT_1   18446744073709551615    /** 2^64 - 1    */

namespace mtpk {

namespace core {

/**
 * @class 
 */
namespace rndm {
    /**
     * @brief Linear Congruential Generator
     * m = modulus      : 32-bits
     * a = multiplier   : 1664525 (from Knuth)
     * c = increment    : 1013904223 (from Knuth)
     */
    uint32_t LCG(uint32_t lower = 0, uint32_t upper = __32BIT_1);

    /**
     * @brief Linear Congruential Generator (64-bit)
     * m = modulus      : 64-bits
     * a = multiplier   : 6364136223846793005 (from Knuth)
     * c = increment    : 1442695040888963407 (from Knuth)
     */
    uint64_t LCGl(uint64_t lower = 0, uint64_t upper = __64BIT_1); 

}

}

}

#endif
