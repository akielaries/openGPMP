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

gpmp::RedPike::word gpmp::RedPike::ROTL(gpmp::RedPike::word X, int R) {
    return (X << (R & 31)) | (X >> (32 - (R & 31)));
}

gpmp::RedPike::word gpmp::RedPike::ROTR(gpmp::RedPike::word X, int R) {
    return (X >> (R & 31)) | (X << (32 - (R & 31)));
}

void gpmp::RedPike::encrypt(gpmp::RedPike::word *x,
                            const gpmp::RedPike::word *k) {
    gpmp::RedPike::word rk0 = k[0];
    gpmp::RedPike::word rk1 = k[1];

    for (int i = 0; i < gpmp::RedPike::ROUNDS; i++) {
        rk0 += gpmp::RedPike::CONST;
        rk1 -= gpmp::RedPike::CONST;

        x[0] ^= rk0;
        x[0] += x[1];
        x[0] = gpmp::RedPike::ROTL(x[0], x[1]);

        x[1] = gpmp::RedPike::ROTR(x[1], x[0]);
        x[1] -= x[0];
        x[1] ^= rk1;
    }

    rk0 = x[0];
    x[0] = x[1];
    x[1] = rk0;
}

void gpmp::RedPike::decrypt(gpmp::RedPike::word *x,
                            const gpmp::RedPike::word *k) {
    gpmp::RedPike::word dk[2] = {
        k[1] - gpmp::RedPike::CONST * (gpmp::RedPike::ROUNDS + 1),
        k[0] + gpmp::RedPike::CONST * (gpmp::RedPike::ROUNDS + 1)};

    gpmp::RedPike::encrypt(x, dk);
}

int main() {
    // Example usage
    word plaintext[2] = {0x12345678, 0x9ABCDEF0};
    word key[2] = {0xA0B1C2D3, 0xE4F50607};

    encrypt(plaintext, key);

    return 0;
}
