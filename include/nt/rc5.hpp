/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
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

#ifndef RC5_HPP
#define RC5_HPP

#include <cstdint>
#include <vector>

namespace gpmp {

namespace nt {

/**
 * @brief RC5 encryption and decryption class
 */
class RC5 {
  public:
    /**
     * @brief Constructs an RC5 object
     *
     * @param rounds Number of rounds
     * @param wordSize Size of the word in bits
     * @param blockSize Size of the block in bytes
     */
    RC5(uint32_t rounds = 12, uint32_t wordSize = 32, uint32_t blockSize = 16);

    /**
     * @brief Encrypts the given block
     *
     * @param A First half of the block
     * @param B Second half of the block
     */
    void encrypt(uint32_t &A, uint32_t &B);

    /**
     * @brief Decrypts the given block
     *
     * @param A First half of the block
     * @param B Second half of the block
     */
    void decrypt(uint32_t &A, uint32_t &B);

  private:
    uint32_t rotl(uint32_t value, uint32_t shift);
    uint32_t rotr(uint32_t value, uint32_t shift);
    void init();

    uint32_t w, r, b;
    std::vector<uint32_t> S;

    const uint32_t P = 0xB7E15163;
    const uint32_t Q = 0x9E3779B9;
};

} // namespace nt

} // namespace gpmp

#endif
