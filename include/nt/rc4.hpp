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
 * @file
 * Definitions for derivative operations operations
 * @details The RC4 algorithm in this case used 5 methods all
 * dependent off eachother with only 2 being available to the user and
 * 1 optional. Required:
 * 1. mtpk::RC4::compute():
 *      - key (char *)
 *      - text (char *)
 *      - hashtext (allocated unsigned char * w/ size & length of
 * text)
 *      - swap type (int 0-2)
 *          - XOR swap, char swap, byte swap
 * 2. mtpk::RC4::store_hash():
 *      - text
 *      - hashtext : previously declared and passed into compute()
 *      - swap type
 */

#ifndef RC4_H
#define RC4_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

// (2^8)-1, bitmask for a byte
#define BITS 255
#define BYTE_LIMIT 256

namespace mtpk {

/**
 * @class
 * @brief Rivest-Cipher 4 Encryption Algorithm Class
 */
class RC4 {
  public:
    /* swaps two values using uint8_t type */
    void byte_swap(uint8_t *a, uint8_t *b);
    /* swaps two values in a traditional way using chars */
    void trad_swap(unsigned char *a, unsigned char *b);
    /* swaps two values using the XOR operator */
    void XOR_swap(unsigned char *a, unsigned char *b);
    /* Key Scheduling Algorithm */
    void KSA(char *key, unsigned char *S, int swap_type);
    /* Pseudo-Random Generation Algorithm */
    void PRGA(unsigned char *S, char *plaintext, unsigned char *ciphertext,
              int swap_type);
    /* function to display our hashed text */
    std::string store_hash(char *plaintext, unsigned char *hashtext,
                           int swap_type);
    /* compute our hash using the the RC4 encryption algorithm */
    unsigned char *compute(char *key, char *plaintext,
                           unsigned char *hashtext, int swap_type);
};

} // namespace mtpk

#endif
