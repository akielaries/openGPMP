extern "C" {
#include <TestU01.h>
#include <bbattery.h>
#include <smarsa.h>
#include <ulcg.h>
#include <unif01.h>
}

#include "../../include/nt/random.hpp"
#include <iostream>
#include <random>

// Wrapper function with the correct signature for TestU01
unsigned int LCG_wrapper() {
    // You may want to provide appropriate default values for lower, upper, and
    // seed
    gpmp::core::rndm::LCG gen(1,
                              6364136223846793005ULL,
                              1442695040888963407ULL);

    return gen();
}

// Wrapper function for std::linear_congruential_engine
unsigned int linear_congruential_engine_wrapper() {
    // Create a linear congruential engine with default parameters
    static std::linear_congruential_engine<uint64_t,
                                           6364136223846793005ULL,
                                           1442695040888963407ULL,
                                           std::numeric_limits<uint64_t>::max()>
        engine;

    // Get the next random number from the engine
    return static_cast<unsigned int>(engine());
}

int main() {
    // Initialize the LCG generator
    unif01_Gen *gen_LCG = unif01_CreateExternGenBits("LCG", LCG_wrapper);

    // Run the SmallCrush battery of tests for LCG
    std::cout << "Testing LCG\n";
    bbattery_SmallCrush(gen_LCG);

    // Clean up
    unif01_DeleteExternGenBits(gen_LCG);

    // Initialize the std::linear_congruential_engine generator
    unif01_Gen *gen_stdLCG =
        unif01_CreateExternGenBits("std::linear_congruential_engine",
                                   linear_congruential_engine_wrapper);

    // Run the SmallCrush battery of tests for std::linear_congruential_engine
    std::cout << "\nTesting std::linear_congruential_engine\n";
    bbattery_SmallCrush(gen_stdLCG);

    // Clean up
    unif01_DeleteExternGenBits(gen_stdLCG);

    return 0;
}
