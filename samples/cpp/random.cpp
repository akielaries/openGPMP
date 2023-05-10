#include "../../include/nt/random.hpp"
#include <iostream>
#include <cstdint>

int main() {
    // generates a random 32 bit unsigned integer using a linear 
    // congruential generator (LCG)
    uint32_t res = mtpk::core::rndm::LCG();
    std::cout << res << std::endl;

    // generates a random 64 bit unsigned integer using a linear 
    // congruential generator (LCG)
    uint64_t res2 = mtpk::core::rndm::LCGl();
    std::cout << res2 << std::endl;
    



    return 0;
}

