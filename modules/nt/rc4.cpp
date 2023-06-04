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

/*
 * This file shows the implementation of the Rivest Cipher 4 (RC4)
 * encryption algorithm created by Ron Rivest using either a
 * traditional swap method or with the XOR operator
 */
#include "../../include/nt/rc4.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

void gpmp::RC4::byte_swap(uint8_t *a, uint8_t *b) {
    uint8_t swapped = *a;
    swapped = *a;
    *a = *b;
    *b = swapped;
}

void gpmp::RC4::trad_swap(unsigned char *a, unsigned char *b) {
    int swapped = *a;
    *a = *b;
    *b = swapped;
}

void gpmp::RC4::XOR_swap(unsigned char *a, unsigned char *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void gpmp::RC4::KSA(char *key, unsigned char *S, int swap_type) {
    uint32_t len = strlen(key);
    int j = 0;

    for (int i = 0; i < BYTE_LIMIT; i++) {
        S[i] = i;
    }

    for (int i = 0; i < BYTE_LIMIT; i++) {
        j = (j + S[i] + key[i % len]) & BITS;

        // choose swap algorithm based off swap_type
        if (swap_type == 0) {
            XOR_swap(&S[i], &S[j]);
        } else if (swap_type == 1) {
            trad_swap(&S[i], &S[j]);
        } else if (swap_type == 2) {
            byte_swap(&S[i], &S[j]);
        }
    }
}

void gpmp::RC4::PRGA(unsigned char *S, char *plaintext,
                     unsigned char *ciphertext, int swap_type) {
    int i = 0;
    int j = 0;

    for (size_t n = 0, len = strlen(plaintext); n < len; n++) {
        i = (i + 1) & BITS;
        j = (j + S[i]) & BITS;

        // choose swap algorithm based off swap_type
        if (swap_type == 0) {
            XOR_swap(&S[i], &S[j]);
        } else if (swap_type == 1) {
            trad_swap(&S[i], &S[j]);
        } else if (swap_type == 2) {
            byte_swap(&S[i], &S[j]);
        }

        uint32_t rnd = S[(S[i] + S[j]) & BITS];

        ciphertext[n] = rnd ^ plaintext[n];
    }
}

std::string gpmp::RC4::store_hash(char *plaintext, unsigned char *hashtext,
                                  int swap_type) {
    // length of our plaintext
    int len = strlen((char *)plaintext);
    // for snprintf declare a buffer
    char buffer[len + 1];
    int size = sizeof(buffer);

    // initialize empty string
    std::string stored_text = "";

    // traverse the hashtext appending each block to a string
    for (size_t index = 0, len = strlen(plaintext); index < len; index++) {
        if (swap_type == 0) {
            snprintf(buffer, size, "|x%02hhx|", hashtext[index]);
        }
        // to format our hash to a string for future manipulation
        else {
            snprintf(buffer, size, "%02hhX", hashtext[index]);
        }
        // append the declared string
        stored_text += std::string(buffer);
    }
    return stored_text;
}

unsigned char *gpmp::RC4::compute(char *key, char *plaintext,
                                  unsigned char *ciphertext, int swap_type) {
    if (ciphertext == NULL) {
        throw std::runtime_error("[-] Error Allocating Memory");
    }

    // check for swap types 1-3
    if (0 <= swap_type && swap_type <= 2) {
        unsigned char S[BYTE_LIMIT];
        KSA(key, S, swap_type);
        PRGA(S, plaintext, ciphertext, swap_type);
    }

    else if (swap_type > 2) {
        throw std::runtime_error("[-] Invalid swap_type");
    }

    return ciphertext;
}
