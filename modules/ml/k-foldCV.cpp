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
 * testing our implemented k-fold cross-validation
 */

#include "k-foldCV.h"
using namespace std;

TEST_CASE("KF_CV-testSmallSample10Fold") {
    vector<string> small_sample =
        {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    KF_CV<string> kF_CV = KF_CV<string>(smallSample, 10, 1);
    vector<string> test_sample = kF_CV.get_test_fold(0);
    REQUIRE(test_sample[0] == "2");
}

TEST_CASE("KF_CV-testSmallSample5Fold") {
    vector<string> small_sample =
        {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    KF_CV<string> kF_CV = KF_CV<string>(small_sample, 5, 1);
    vector<string> test_sample = kF_CV.get_test_fold(0);
    REQUIRE(test_sample[0] == "2");
    REQUIRE(test_sample[1] == "7");
}

TEST_CASE("KF_CV-testLargeSample10Fold") {
    vector<int64_t> large_sample;
    for (int64_t i = 0; i < 1000; i++) {
        large_sample.emplace_back(i);
    }
    KF_CV<int64_t> kF_CV = KF_CV<int64_t>(large_sample, 10, 1);
    for (int64_t i = 0; i < 10; i++) {
        REQUIRE(100 == kF_CV.get_test_fold(i).size());
        REQUIRE(900 == kF_CV.get_train_fold(i).size());
    }
}

TEST_CASE("KFCV-testLargeSample5Fold") {
    vector<int64_t> large_sample;
    for (int64_t i = 0; i < 1000; i++) {
        large_sample.emplace_back(i);
    }
    KF_CV<int64_t> kF_CV = KF_CV<int64_t>(large_sample, 5, 1);
    for (int64_t i = 0; i < 5; i++) {
        REQUIRE(200 == kF_CV.get_test_fold(i).size());
        REQUIRE(800 == kF_CV.get_train_fold(i).size());
    }
}
