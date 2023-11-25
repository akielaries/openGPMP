#include "../../include/nt/random.hpp"
#include <cstdint>
#include <iostream>
#include <random>

int main() {
    // generates a random 32 bit unsigned integer using a linear
    // congruential generator (LCG)
    gpmp::core::rndm::LCG gen(1,
                              6364136223846793005ULL,
                              1442695040888963407ULL);

    uint64_t res = gen();

    std::cout << "Random value: " << res << std::endl;

    static std::linear_congruential_engine<uint64_t,
                                           6364136223846793005ULL,
                                           1442695040888963407ULL,
                                           std::numeric_limits<uint64_t>::max()>
        engine;

    // Get the next random number from the engine
    uint64_t std_lcg_res = static_cast<unsigned int>(engine());

    std::cout << "Random value: " << std_lcg_res << std::endl;

    return 0;
}
