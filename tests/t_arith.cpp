/*
 * Testing Arithmetic Operations
 */
#include "../include/arith.hpp"
#include <limits.h>
#include <gtest/gtest.h>

using ::testing::InitGoogleTest;
using ::testing::FloatLE;
using ::testing::DoubleLE;


namespace {

    // test case, test name
    TEST(arith_test, Positive) {
        arith ar;
        EXPECT_EQ(21, ar.rm_add(10, 8, 3));
    }
}

int main() {
    InitGoogleTest();
    
    return RUN_ALL_TESTS();
}

