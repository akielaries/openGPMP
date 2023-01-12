/**
 * @file
 * Definitions for Self-Organizing Map (SOM)
 */

#ifndef KOHONEN_NETWORK_HPP
#define KOHONEN_NETWORK_HPP
#include <vector>
#include <stdio.h>

namespace mtpk {

/**
 * @brief Kohonen Neural Network Cluster Class 
 *
 * Referred to as Self-Organizing Map
 */
class KohonenNet {
    int64_t choice(weights, sample);
    int64_t update(weights, sample, J, alpha);

};

} // namespace

#endif

