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
#include <gtest/gtest.h>
#include <limits.h>
#include <openGPMP/calculus/differential.hpp>
#include <string>

using ::testing::DoubleLE;
using ::testing::FloatLE;
using ::testing::InitGoogleTest;

namespace {

TEST(DifferentialTests, AddTerm) {
    gpmp::Differential poly;
    poly.add_term(3, 2);
    poly.add_term(2, 1);
    poly.add_term(1, 0);

    ASSERT_EQ(poly.terms.size(), 3);

    // Add more assertions based on the specific behavior you expect
}

TEST(DifferentialTests, PowerRule) {
    gpmp::Differential poly;
    poly.add_term(3, 2);
    poly.add_term(2, 1);
    poly.add_term(1, 0);

    gpmp::Differential result = poly.power_rule();

    // Assert the result based on the expected derivative
    ASSERT_EQ(result.terms.size(), 2);
    ASSERT_EQ(result.terms[0].coefficient, 6);
    ASSERT_EQ(result.terms[0].exponent, 1);
    ASSERT_EQ(result.terms[1].coefficient, 2);
    ASSERT_EQ(result.terms[1].exponent, 0);
}

} // namespace
