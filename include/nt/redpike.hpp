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

#ifndef REDPIKE_HPP
#define REDPIKE_HPP

#include <cstdint>

namespace gpmp {

namespace nt {

/**
 * @class RedPike
 *
 * @brief Class for encryption and decryption using the RedPike algorithm
 */
class RedPike {
  public:
    /**
     * @brief Encrypts the given data using the RedPike algorithm
     *
     * @param x Pointer to the data to be encrypted
     * @param k Pointer to the key used for encryption
     */
    void encrypt(uint32_t *x, const uint32_t *k);

    /**
     * @brief Decrypts the given data using the RedPike algorithm
     *
     * @param x Pointer to the data to be decrypted
     * @param k Pointer to the key used for decryption
     */
    void decrypt(uint32_t *x, const uint32_t *k);

  private:
    /**
     * @brief Constant value used in the RedPike algorithm
     */
    uint32_t CONST = 0x9E3779B9;

    /**
     * @brief Number of rounds in the RedPike algorithm
     */
    int ROUNDS = 16;

    /**
     * @brief Performs left rotation on the given value
     *
     * @param X Value to be rotated
     * @param R Number of bits to rotate left by
     *
     * @return Rotated value
     */
    uint32_t rotl(uint32_t X, int R);

    /**
     * @brief Performs right rotation on the given value
     *
     * @param X Value to be rotated
     * @param R Number of bits to rotate right by
     *
     * @return Rotated value
     */
    uint32_t rotr(uint32_t X, int R);
};

} // namespace nt

} // namespace gpmp

#endif
