/**
 * @file
 *
 * openMTPK Machine Learning Module Regularization Algorithms
 *
 */
#ifndef ML_REGULIZERS_HPP
#define ML_REGULIZERS_HPP
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
class Regularizers {
    public:
    /**
     * @brief Elastic net regularization
     */
    void elastic_net();
};

} // namespace ml

} // namespace mtpk

#endif
