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
 * Testing Arithmetic Operations
 */
#include "../../include/arithmetic.hpp"
#include <gtest/gtest.h>
#include <limits.h>

using ::testing::DoubleLE;
using ::testing::FloatLE;
using ::testing::InitGoogleTest;

/*
namespace {
gpmp::Arith ar;


// test case, test name
TEST(arith_test, add_positive) {
    EXPECT_EQ(46094, ar.add(93, 106, 3551, 42344));
    EXPECT_EQ(21, ar.add(10, 8, 3));
    EXPECT_EQ(6.85, ar.add(1.25, 1.85, 2.75, 1));
}

// multiplication (product) testing
TEST(arith_test, mult_positive) {
    EXPECT_EQ(240, ar.mult(10, 8, 3));
    EXPECT_EQ(6.359375, ar.mult(1.25, 1.85, 2.75, 1));
}

// subtraction
TEST(arith_test, sub_positive) {
    EXPECT_EQ(5, ar.sub(10, 8, 3));
    EXPECT_EQ(2.15, ar.sub(1.25, 1.85, 2.75));
    EXPECT_EQ(7, ar.sub(3, 3, 7));
}
} // namespace
*/
namespace {
// gpmp::Arith<int> ar;

}

namespace {
gpmp::Basics ba;

// greatest power
TEST(BasicsTest, greatest_pow) {
    EXPECT_EQ(4, ba.greatest_power(10, 3));
    EXPECT_EQ(2, ba.greatest_power(7, 3));
}

// greatest common divisor
TEST(BasicsTest, greatest_common_divisor) {
    EXPECT_EQ(2, ba.op_gcd(2, 4));
    EXPECT_EQ(6, ba.op_gcd(2198466, 96096));
    EXPECT_EQ(11, ba.op_gcd(66, 11));
    EXPECT_EQ(8, ba.op_gcd(232, 96));
    EXPECT_EQ(10, ba.op_gcd(1703210, 20320));
}
} // namespace
/*
int main() {
    InitGoogleTest();

    return RUN_ALL_TESTS();
}
*/
