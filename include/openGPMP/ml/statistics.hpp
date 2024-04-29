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

#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <vector>

namespace gpmp {

namespace ml {

class Stats {
  public:
    // These functions are for univariate lin reg module- not for
    // users.
    double b0Estimation(const std::vector<double> &x,
                        const std::vector<double> &y);
    double b1Estimation(const std::vector<double> &x,
                        const std::vector<double> &y);
    // Statistical Functions
    double mean(const std::vector<double> &x);
    double median(std::vector<double> x);
    std::vector<double> mode(const std::vector<double> &x);
    double range(const std::vector<double> &x);
    double midrange(const std::vector<double> &x);
    double absAvgDeviation(const std::vector<double> &x);
    double standardDeviation(const std::vector<double> &x);
    double variance(const std::vector<double> &x);
    double covariance(const std::vector<double> &x,
                      const std::vector<double> &y);
    double correlation(const std::vector<double> &x,
                       const std::vector<double> &y);
    double R2(const std::vector<double> &x, const std::vector<double> &y);
    double chebyshevIneq(const double k);
    double weightedMean(const std::vector<double> &x,
                        const std::vector<double> &weights);
    double geometricMean(const std::vector<double> &x);
    double harmonicMean(const std::vector<double> &x);
    double RMS(const std::vector<double> &x);
    double powerMean(const std::vector<double> &x, const double p);
    double lehmerMean(const std::vector<double> &x, const double p);
    double weightedmean_lehmer(const std::vector<double> &x,
                               const std::vector<double> &weights,
                               const double p);
    double contramean_harmonic(const std::vector<double> &x);
    double heronianMean(const double A, const double B);
    double heinzMean(const double A, const double B, const double x);
    double neumanSandorMean(const double a, const double b);
    double stolarskyMean(const double x, const double y, const double p);
    double identricMean(const double x, const double y);
    double logMean(const double x, const double y);

    // hypothesis test
    std::tuple<bool, double> chiSquareTest(std::vector<double> observed,
                                           std::vector<double> expected);
};

} // namespace ml

} // namespace gpmp

#endif
