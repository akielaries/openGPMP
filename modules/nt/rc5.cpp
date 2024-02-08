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

#include "../../include/nt/rc5.hpp"
#include <cstdint>

gpmp::nt::RC5::RC5(uint32_t rounds, uint32_t wordSize, uint32_t blockSize)
    : r(rounds), w(wordSize), b(blockSize) {
    init();
}

void gpmp::nt::RC5::init() {
    S.resize(2 * r + 2);
    S[0] = P;
    for (uint32_t i = 1; i < 2 * r + 2; ++i) {
        S[i] = S[i - 1] + Q;
    }
}

void gpmp::nt::RC5::encrypt(uint32_t &A, uint32_t &B) {
    A += S[0];
    B += S[1];
    for (uint32_t i = 1; i <= r; ++i) {
        A = rotl((A ^ B), B) + S[2 * i];
        B = rotl((B ^ A), A) + S[2 * i + 1];
    }
}

void gpmp::nt::RC5::decrypt(uint32_t &A, uint32_t &B) {
    for (uint32_t i = r; i > 0; --i) {
        B = rotr(B - S[2 * i + 1], A) ^ A;
        A = rotr(A - S[2 * i], B) ^ B;
    }
    B -= S[1];
    A -= S[0];
}

uint32_t gpmp::nt::RC5::rotl(uint32_t value, uint32_t shift) {
    return (value << shift) | (value >> (w - shift));
}

uint32_t gpmp::nt::RC5::rotr(uint32_t value, uint32_t shift) {
    return (value >> shift) | (value << (w - shift));
}
