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

#include "../../include/number_theory/rc5.hpp"
#include <math.h>
#include <stdint.h>
#include <string.h>

uint32_t shift_left(uint32_t v, uint32_t n) {
}

uint32_t shift_right(uint32_t v, uint32_t n) {
}

uint32_t rotate_left(uint32_t v, uint32_t n) {
}

uint32_t rotate_right(uint32_t v, uint32_t n) {
}

void encrypt(uint32_t S[26], uint32_t inout[4]) {
}

void decrypt(uint32_t S[26], uint32_t inout[4]) {
}

// expand key into S array using magic numbers derived from e and phi
void expand(uint32_t L[4], uint32_t S[26]) {
}

// decrypt of encrypt should be the same
int test(uint32_t S[26], uint32_t messg[4]) {
}
