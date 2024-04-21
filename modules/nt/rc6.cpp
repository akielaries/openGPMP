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
 * LICENSE file.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/
#include <openGPMP/nt/rc6.hpp>
#include <cmath>
#include <cstdint>
#include <stdexcept>

RC6::RC6(const std::vector<uint8_t> &key) {
    key_schedule(key);
}

void RC6::key_schedule(const std::vector<uint8_t> &key) {
    std::vector<uint32_t> L = expand(key);
    S.resize(2 * (r + 1));
    const uint32_t P = 0xB7E15163;
    const uint32_t Q = 0x9E3779B9;
    S[0] = P;
    for (int i = 1; i < 2 * (r + 1); ++i) {
        S[i] = S[i - 1] + Q;
    }
    uint32_t A = 0, B = 0;
    int i = 0, j = 0;
    for (int k = 0; k < 3 * std::max(b, 2 * (r + 1)); ++k) {
        A = S[i] = rotl((S[i] + A + B), 3);
        B = L[j] = rotl((L[j] + A + B), (A + B));
        i = (i + 1) % (2 * (r + 1));
        j = (j + 1) % b;
    }
}

std::vector<uint32_t> RC6::expand(const std::vector<uint8_t> &key) {
    std::vector<uint32_t> L(b / 4);
    for (size_t i = 0; i < key.size(); i++) {
        L[i / 4] |= (static_cast<uint32_t>(key[i]) << (8 * (i % 4)));
    }
    return L;
}

uint32_t RC6::rotl(uint32_t val, int shift) {
    return (val << shift) | (val >> (w - shift));
}

uint32_t RC6::rotr(uint32_t val, int shift) {
    return (val >> shift) | (val << (w - shift));
}

void RC6::encrypt_block(const uint32_t plaintext[2], uint32_t ciphertext[2]) {
    uint32_t A = plaintext[0], B = plaintext[1];
    A += S[0];
    B += S[1];
    for (int i = 1; i <= r; ++i) {
        A = rotl(A ^ B, B) + S[2 * i];
        B = rotl(B ^ A, A) + S[2 * i + 1];
    }
    ciphertext[0] = A;
    ciphertext[1] = B;
}

void RC6::decrypt_block(const uint32_t ciphertext[2], uint32_t plaintext[2]) {
    uint32_t A = ciphertext[0], B = ciphertext[1];
    for (int i = r; i >= 1; --i) {
        B = rotr(B - S[2 * i + 1], A) ^ A;
        A = rotr(A - S[2 * i], B) ^ B;
    }
    B -= S[1];
    A -= S[0];
    plaintext[0] = A;
    plaintext[1] = B;
}

std::vector<uint8_t> RC6::encrypt(const std::vector<uint8_t> &plaintext) {
    if (plaintext.size() % 8 != 0) {
        throw std::invalid_argument(
            "Plaintext length must be a multiple of 8 bytes");
    }
    std::vector<uint8_t> ciphertext;
    ciphertext.reserve(plaintext.size());
    for (size_t i = 0; i < plaintext.size(); i += 8) {
        uint32_t block[2];
        uint32_t encrypted_block[2];
        for (int j = 0; j < 8; ++j) {
            block[j / 4] |=
                (static_cast<uint32_t>(plaintext[i + j]) << (8 * (j % 4)));
        }
        encrypt_block(block, encrypted_block);
        for (int j = 0; j < 2; ++j) {
            ciphertext.push_back((encrypted_block[j] >> 24) & 0xFF);
            ciphertext.push_back((encrypted_block[j] >> 16) & 0xFF);
            ciphertext.push_back((encrypted_block[j] >> 8) & 0xFF);
            ciphertext.push_back(encrypted_block[j] & 0xFF);
        }
    }
    return ciphertext;
}

std::vector<uint8_t> RC6::decrypt(const std::vector<uint8_t> &ciphertext) {
    if (ciphertext.size() % 8 != 0) {
        throw std::invalid_argument(
            "Ciphertext length must be a multiple of 8 bytes");
    }
    std::vector<uint8_t> plaintext;
    plaintext.reserve(ciphertext.size());
    for (size_t i = 0; i < ciphertext.size(); i += 8) {
        uint32_t block[2];
        uint32_t decrypted_block[2];
        for (int j = 0; j < 2; ++j) {
            block[j] =
                (static_cast<uint32_t>(ciphertext[i + 4 * j]) << 24) |
                (static_cast<uint32_t>(ciphertext[i + 4 * j + 1]) << 16) |
                (static_cast<uint32_t>(ciphertext[i + 4 * j + 2]) << 8) |
                static_cast<uint32_t>(ciphertext[i + 4 * j + 3]);
        }
        decrypt_block(block, decrypted_block);
        for (int j = 0; j < 8; ++j) {
            plaintext.push_back((decrypted_block[j / 4] >> (8 * (j % 4))) &
                                0xFF);
        }
    }
    return plaintext;
}
