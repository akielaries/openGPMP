#ifndef KOHONEN_NETWORK_HPP
#define KOHONEN_NETWORK_HPP
#include <vector>
#include <stdio.h>

class Kohonen_network {
    int choice(weights, sample);
    int update(weights, sample, J, alpha);

};

#endif

