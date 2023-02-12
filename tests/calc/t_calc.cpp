/*
 * Testing Calculus Operations
 */
#include "../../include/calculus/deriv.hpp"
#include <gtest/gtest.h>
#include <limits.h>
#include <string>

using ::testing::DoubleLE;
using ::testing::FloatLE;
using ::testing::InitGoogleTest;

namespace {
mtpk::Calculus calc;

// Test Derivative Operations
TEST(deriv_test, deriv_at_val) {
    std::string string_0 = "4x^3 + 3x^1 + 2x^2 + 5x^1 + 2x^4";
    int x_0 = 2;

    EXPECT_EQ(128, calc.deriv_at(string_0, x_0));
}

} // namespace
/*
int main() {
    InitGoogleTest();

    return RUN_ALL_TESTS();
}
*/
