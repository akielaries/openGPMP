/*
 * Testing Arithmetic Operations
 */
#include "../../include/arithmetic/arith.hpp"
#include <limits.h>
#include <gtest/gtest.h>

using ::testing::InitGoogleTest;
using ::testing::FloatLE;
using ::testing::DoubleLE;


namespace {
    Arith ar;

    // test case, test name
    TEST(arith_test, add_positive) {
        EXPECT_EQ(46094, ar.add(93, 106, 3551, 42344));
        EXPECT_EQ(21, ar.add(10, 8, 3));
        EXPECT_EQ(6.85, ar.add(1.25, 1.85, 2.75, 1));
        
    }

    // multiplication (product) testing
    TEST(arith_test, mult_positive) {
        EXPECT_EQ(240, ar.mult(10, 8, 3));
        EXPECT_EQ(6.359375, ar.mult(1.25, 1.85, 2.75, 1));
    }

    // subtraction
    TEST(arith_test, sub_positive) {
        EXPECT_EQ(5, ar.sub(10, 8, 3));
        EXPECT_EQ(1, ar.sub(1.25, 1.85, 2.75));
        EXPECT_EQ(-7, ar.sub(3, 3, 7));
    }
}

/*
int main() {
    InitGoogleTest();
    
    return RUN_ALL_TESTS();
}
*/

