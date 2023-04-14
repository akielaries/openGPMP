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

/**
 * @ file
 *
 * Definitions for Matrix, Scalar, Vector, and other Linear Alebra
 * related operations
 */

#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <cmath>
#include <vector>

namespace mtpk {

/**
 * @class Vectors
 * @brief Operations related to Vectors and Scalars
 */
class Vectors {
    std::vector<int64_t> x;
    std::vector<int64_t> y;

  public:
    /*
     * vectors of the same dimension size are just scalars as they
     * only contain magnitude. vectors contain both magnitude +
     * direction
     */
    // function to add two 1D vectors
    // template <typename T>
    // float scalar_add();
    // function to subtract two 1D vectors
    // float scalar_sub();
    // function to multiply two 1D vectors
    // float scalar_mult();
    int64_t add(int64_t a, int64_t b);
};

} // namespace mtpk

#endif
