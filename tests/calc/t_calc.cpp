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
 * Testing Calculus Operations
 */
#include "../../include/calculus/differential.hpp"
#include <gtest/gtest.h>
#include <limits.h>
#include <string>

using ::testing::DoubleLE;
using ::testing::FloatLE;
using ::testing::InitGoogleTest;

namespace {
gpmp::Differential calc;

// Test Derivative Operations
TEST(deriv_test, deriv_at_val) {
    std::string string_0 = "4x^3 + 3x^1 + 2x^2 + 5x^1 + 2x^4";
    int x_0 = 2;

    EXPECT_EQ(128, calc.deriv_at(string_0, x_0));
}

} // namespace
  //
