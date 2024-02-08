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

/*
 * Implementation of the Red Pike block cipher algorithm
 */

#include "../../include/nt/redpike.hpp"
#include <cstdint>

uint32_t gpmp::nt::RedPike::rotl(uint32_t X, int R) {
    return ((X) << ((R)&31)) | ((X) >> (32 - ((R)&31)));
}

uint32_t gpmp::nt::RedPike::rotr(uint32_t X, int R) {
    return ((X) >> ((R)&31)) | ((X) << (32 - ((R)&31)));
}

void gpmp::nt::RedPike::encrypt(uint32_t *x, const uint32_t *k) {
    uint32_t rk0 = k[0];
    uint32_t rk1 = k[1];

    for (int i = 0; i < ROUNDS; i++) {
        rk0 += CONST;
        rk1 -= CONST;

        x[0] ^= rk0;
        x[0] += x[1];
        x[0] = rotl(x[0], x[1]);

        x[1] = rotr(x[1], x[0]);
        x[1] -= x[0];
        x[1] ^= rk1;
    }

    rk0 = x[0];
    x[0] = x[1];
    x[1] = rk0;
}

void gpmp::nt::RedPike::decrypt(uint32_t *x, const uint32_t *k) {
    uint32_t dk[2] = {k[1] - CONST * (ROUNDS + 1), k[0] + CONST * (ROUNDS + 1)};

    encrypt(x, dk);
}
