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

#ifndef RC6_HPP
#define RC6_HPP

#include <cstdint>
#include <vector>

/**
 * @class RC6
 * @brief Class implementing the RC6 cipher algorithm
 */
class RC6 {
  public:
    /**
     * @brief Constructor for RC6 class
     * @param key The encryption key
     */
    RC6(const std::vector<uint8_t> &key);

    /**
     * @brief Encrypts plaintext using RC6 algorithm
     * @param plaintext The plaintext to encrypt
     * @return The encrypted ciphertext
     */
    std::vector<uint8_t> encrypt(const std::vector<uint8_t> &plaintext);

    /**
     * @brief Decrypts ciphertext using RC6 algorithm
     * @param ciphertext The ciphertext to decrypt
     * @return The decrypted plaintext
     */
    std::vector<uint8_t> decrypt(const std::vector<uint8_t> &ciphertext);

  private:
    const int w = 32; /**< Word size */
    const int r = 20; /**< Number of rounds */
    const int b = 16; /**< Number of bytes in key */

    std::vector<uint32_t> S; /**< Internal state array */

    /**
     * @brief Generates the key schedule from the given key
     * @param key The encryption key
     */
    void key_schedule(const std::vector<uint8_t> &key);

    /**
     * @brief Performs key expansion
     * @param key The encryption key
     * @return The expanded key schedule
     */
    std::vector<uint32_t> expand(const std::vector<uint8_t> &key);

    /**
     * @brief Performs left rotation
     * @param val The value to rotate
     * @param shift The number of bits to rotate by
     * @return The rotated value
     */
    uint32_t rotl(uint32_t val, int shift);

    /**
     * @brief Performs right rotation
     * @param val The value to rotate
     * @param shift The number of bits to rotate by
     * @return The rotated value
     */
    uint32_t rotr(uint32_t val, int shift);

    /**
     * @brief Encrypts a single block of plaintext
     * @param plaintext The plaintext block to encrypt
     * @param ciphertext The resulting ciphertext block
     */
    void encrypt_block(const uint32_t plaintext[2], uint32_t ciphertext[2]);

    /**
     * @brief Decrypts a single block of ciphertext
     * @param ciphertext The ciphertext block to decrypt
     * @param plaintext The resulting plaintext block
     */
    void decrypt_block(const uint32_t ciphertext[2], uint32_t plaintext[2]);
};

#endif
