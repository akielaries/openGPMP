#include "../../include/nt/random.hpp"
#include <cstdint>
#include <iostream>

int main() {
    // generates a random 32 bit unsigned integer using a linear
    // congruential generator (LCG)
    uint32_t res = gpmp::core::rndm::LCG();
    std::cout << res << std::endl;

    // generates a random 64 bit unsigned integer using a linear
    // congruential generator (LCG)
    uint64_t res2 = gpmp::core::rndm::LCGl();
    std::cout << res2 << std::endl;

    return 0;
}
