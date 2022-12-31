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
    int choice(weights, sample);
    int update(weights, sample, J, alpha);

};

} // namespace

#endif

