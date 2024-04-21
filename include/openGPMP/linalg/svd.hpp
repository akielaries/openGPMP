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

#ifndef SVD_HPP
#define SVD_HPP

#include <iostream>
#include <vector>

namespace gpmp {

namespace linalg {

class SVD {
  public:
    /**
     * @brief Constructor to compute SVD for a given matrix
     * @param matrix The input matrix for SVD
     * @throw std::invalid_argument if the matrix is empty
     */
    explicit SVD(std::vector<std::vector<double>> &matrix);

    /**
     * @brief Get the singular values of the matrix
     * @return Vector containing singular values in descending order
     */
    std::vector<double> getSingularValues() const;

    /**
     * @brief Get the left singular vectors of the matrix
     * @return Matrix containing left singular vectors as columns
     */
    std::vector<std::vector<double>> getLeftSingularVectors() const;

    /**
     * @brief Get the right singular vectors of the matrix
     * @return Matrix containing right singular vectors as columns
     */
    std::vector<std::vector<double>> getRightSingularVectors() const;

  private:
    std::vector<double> singularValues_;
    std::vector<std::vector<double>> leftSingularVectors_;
    std::vector<std::vector<double>> rightSingularVectors_;

    // Helper functions for SVD computation
    void computeSVD(std::vector<std::vector<double>> &matrix);
    void bidiagonalize(std::vector<std::vector<double>> &matrix,
                       std::vector<double> &diagonal,
                       std::vector<double> &superdiagonal);

    void computeHouseholderReflection(const std::vector<double> &x,
                                      std::vector<double> &v,
                                      double &beta);
    void applyHouseholder(std::vector<std::vector<double>> &matrix,
                          const std::vector<double> &v,
                          double beta,
                          size_t fromRow,
                          size_t fromCol);
};
} // namespace linalg

} // namespace gpmp

#endif
