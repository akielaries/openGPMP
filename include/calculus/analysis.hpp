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

/**
 * @file
 *
 * @brief Numerical Analysis Methods. A blend of Calculus and
 * Linear Algebra
 */
#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include <string>
#include <vector>

namespace gpmp {
class NumericalAnalysis {
  public:
    /* A numerical method for derivatives is used. This may be subject
    to change, as an analytical method for calculating derivatives
    will most likely be used in the future.
    */
    double numDiff(double (*function)(double), double x);
    double numDiff_2(double (*function)(double), double x);
    double numDiff_3(double (*function)(double), double x);

    double constantApproximation(double (*function)(double), double c);

    double linearApproximation(double (*function)(double), double c, double x);

    double
    quadraticApproximation(double (*function)(double), double c, double x);

    double cubicApproximation(double (*function)(double), double c, double x);

    double numDiff(double (*function)(std::vector<double>),
                   std::vector<double> x,
                   int axis);

    double numDiff_2(double (*function)(std::vector<double>),
                     std::vector<double> x,
                     int axis1,
                     int axis2);

    double numDiff_3(double (*function)(std::vector<double>),
                     std::vector<double> x,
                     int axis1,
                     int axis2,
                     int axis3);

    double newtonRaphsonMethod(double (*function)(double),
                               double x_0,
                               double epoch_num);

    double
    halleyMethod(double (*function)(double), double x_0, double epoch_num);

    double invQuadraticInterpolation(double (*function)(double),
                                     std::vector<double> x_0,
                                     double epoch_num);

    double eulerianMethod(double (*derivative)(double),
                          std::vector<double> q_0,
                          double p,
                          double h); // Euler's method for solving
                                     // diffrential equations.

    double eulerianMethod(double (*derivative)(std::vector<double>),
                          std::vector<double> q_0,
                          double p,
                          double h); // Euler's method for solving
                                     // diffrential equations.

    double growthMethod(double C,
                        double k,
                        double t); // General growth-based diffrential equations
                                   // can be solved by seperation of variables.

    std::vector<double>
    jacobian(double (*function)(std::vector<double>),
             std::vector<double> x); // Indeed, for functions with scalar
                                     // outputs the Jacobians will be vectors.

    std::vector<std::vector<double>>
    hessian(double (*function)(std::vector<double>), std::vector<double> x);

    std::vector<std::vector<std::vector<double>>>
    thirdOrderTensor(double (*function)(std::vector<double>),
                     std::vector<double> x);

    double constantApproximation(double (*function)(std::vector<double>),
                                 std::vector<double> c);

    double linearApproximation(double (*function)(std::vector<double>),
                               std::vector<double> c,
                               std::vector<double> x);

    double quadraticApproximation(double (*function)(std::vector<double>),
                                  std::vector<double> c,
                                  std::vector<double> x);

    double cubicApproximation(double (*function)(std::vector<double>),
                              std::vector<double> c,
                              std::vector<double> x);

    double laplacian(double (*function)(std::vector<double>),
                     std::vector<double> x); // laplacian

    std::string
    secondPartialDerivativeTest(double (*function)(std::vector<double>),
                                std::vector<double> x);
};
} // namespace gpmp

#endif
