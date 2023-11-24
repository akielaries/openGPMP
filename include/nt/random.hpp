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
/**
 * @file random.hpp
 * @brief Pseudorandom Number Generators
 */
#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdint>
#include <chrono>

/** PRNG CONSTANTS */
#define __8MAX 127                          /** 8 bit signed max    */
#define __U8MAX 255                         /** 8 bit unsigned max */

#define __16MAX 32767                       /** 16 bit signed max   */
#define __U16MAX 65535                      /** 16 bit unsigned max */

#define __32MAX 2147483647L                 /** 32 bit signed max   */
#define __U32MAX 4294967295U                /** 32 bit unsigned max */

#define __64MAX 9223372036854775807LL       /** 64 bit signed max   */
#define __U64MAX 18446744073709551615ULL    /** 64 bit unsigned max */

/*#define __PCG_STATE 0x4d595df4d0f33173
#define __PCG_MULTPLR 6364136223846793005u
#define __PCG_INCR 1442695040888963407u
*/
static uint64_t __PCG_STATE      = 0x4d595df4d0f33173;      // Or something seed-dependent
static uint64_t const __PCG_MULTPLR = 6364136223846793005u;
static uint64_t const __PCG_INCR  = 1442695040888963407u;   // Or an arbitrary odd constant


namespace gpmp {

namespace core {

/**
 * @class
 */
namespace rndm {
/**
 * @brief Linear Congruential Generator
 * @param lower lower bound of range
 * @param upper upper bound of range
 * @param seed
 *      - m = modulus      : 32-bit int max
 *      - a = multiplier   : 1664525 (from Knuth & H.W. Lewis)
 *      - c = increment    : 1013904223 (from Knuth & H.W. Lewis)
 */
uint32_t LCG(uint32_t lower = 0, 
            uint32_t upper = std::numeric_limits<uint32_t>::max(), 
            uint32_t seed = 0);
/**
 * @brief Linear Congruential Generator (64-bit)
 * @param lower lower bound of range
 * @param upper upper bound of range
 * @param seed
 *      - m = modulus      : 64-bits
 *      - a = multiplier   : 6364136223846793005 (from Knuth MMIX)
 *      - c = increment    : 1442695040888963407 (from Knuth MMIX)
 */
uint64_t LCG_64(uint64_t lower = 0, 
            uint64_t upper = std::numeric_limits<uint64_t>::max(), 
            uint64_t seed = 0);

uint32_t rotr32(uint32_t x, unsigned r);

uint32_t pcg32(void);

void pcg32_init(uint64_t seed);


} // namespace rndm

} // namespace core

} // namespace gpmp

#endif
