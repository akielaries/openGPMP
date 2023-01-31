/**
 * @file
 *
 * openMTPK Machine Learning Module Optimizers
 *
 */
#ifndef ML_OPTIMIZERS_HPP
#define ML_OPTIMIZERS_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "mlp_net.hpp"

namespace mtpk {

namespace ml {

/**
 * @class Optimizers
 * @details Class featuring several optimization algorithms
 */
class Optimizers {
    public:
    /**
     * @brief Gradient Descent algorithm
     */
    void gradient_descent();

    /**
     * @brief Stochastic Gradient Descent algorithm
     */
    void stochastic_descent();

    /**
     * @brief Coordinate Descent algorithm
     */
    void coordinate_descent();

    /**
     * @brief Broyden–Fletcher–Goldfarb–Shanno algorithm
     */
    void BFGS();
};

} // namespace ml

} // namespace mtpk

#endif
