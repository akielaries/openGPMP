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
 * Testing the implementation of random cipher algorithms
 */
#include "../../include/nt/cipher.hpp"
#include <gtest/gtest.h>
#include <limits.h>

using ::testing::DoubleLE;
using ::testing::FloatLE;
using ::testing::InitGoogleTest;

namespace {
gpmp::Cipher cc;

TEST(CipherTest, caesar_0) {
    std::string text_0 = "Plaintext";
    int key_shift_0 = 5;
    std::string hashtext_0 = cc.caesar(text_0, key_shift_0);
    std::string expected_0 = "Uqfnsyjcy";

    EXPECT_EQ(expected_0, hashtext_0);
}

TEST(CipherTest, caesar_1) {
    std::string text_1 = "ATTACKATONCE";
    int key_shift_1 = 4;
    std::string hashtext_1 = cc.caesar(text_1, key_shift_1);
    std::string expected_1 = "EXXEGOEXSRGI";

    EXPECT_EQ(expected_1, hashtext_1);
}

TEST(CipherTest, caesar_2) {
    std::string text_2 = "EaSyPASsWorD";
    int key_shift_2 = 14;
    std::string hashtext_2 = cc.caesar(text_2, key_shift_2);
    std::string expected_2 = "SoGmDOGgKcfR";

    EXPECT_EQ(expected_2, hashtext_2);
}

TEST(CipherTest, keyword_0) {
    std::string text_3 = "Password";
    std::string key_shift_3 = "Computer";

    // encode
    std::string encoded_text_0 = cc.keyword_encode(key_shift_3);
    // cipher
    std::string hashtext_3 = cc.keyword(text_3, encoded_text_0);

    std::string expected_3 = "JCNNWILP";

    EXPECT_EQ(expected_3, hashtext_3);
}

TEST(CipherTest, keyword_1) {
    std::string text_4 = "Password";
    std::string key_shift_4 = "Password";

    // encode
    std::string encoded_text_1 = cc.keyword_encode(key_shift_4);
    // cipher
    std::string hashtext_4 = cc.keyword(text_4, encoded_text_1);

    std::string expected_4 = "KPNNVJMW";

    EXPECT_EQ(expected_4, hashtext_4);
}

TEST(CipherTest, error_cipher_text) {
    std::string text_4 = "P455W0RD";
    std::string key_shift_4 = "IN1T_d";

    // encode
    std::string encoded_text_1 = cc.keyword_encode(key_shift_4);
    // cipher
    std::string hashtext_4 = cc.keyword(text_4, encoded_text_1);

    std::string expected_4 = "O455W0QD";

    EXPECT_EQ(expected_4, hashtext_4);
}
} // namespace

/*
int main() {
    InitGoogleTest();

    return RUN_ALL_TESTS();
}
*/
