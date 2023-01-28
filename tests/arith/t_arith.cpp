/*
 * Testing Arithmetic Operations
 */
#include "../../include/arithmetic.hpp"
#include <gtest/gtest.h>
#include <limits.h>

using ::testing::DoubleLE;
using ::testing::FloatLE;
using ::testing::InitGoogleTest;

/*
namespace {
mtpk::Arith ar;


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
    EXPECT_EQ(2.15, ar.sub(1.25, 1.85, 2.75));
    EXPECT_EQ(7, ar.sub(3, 3, 7));
}
} // namespace
*/
namespace {
mtpk::Arith<int> ar;

}

namespace {
mtpk::Basics ba;

// greatest power
TEST(basics, greatest_pow) {
    EXPECT_EQ(4, ba.greatest_power(10, 3));
    EXPECT_EQ(2, ba.greatest_power(7, 3));
}

// greatest common divisor
TEST(basics, greatest_common_divisor) {
    EXPECT_EQ(2, ba.op_gcd(2, 4));
    EXPECT_EQ(6, ba.op_gcd(2198466, 96096));
    EXPECT_EQ(11, ba.op_gcd(66, 11));
    EXPECT_EQ(8, ba.op_gcd(232, 96));
    EXPECT_EQ(10, ba.op_gcd(1703210, 20320));
}
} // namespace
/*
int main() {
    InitGoogleTest();

    return RUN_ALL_TESTS();
}
*/
