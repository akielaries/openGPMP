/*
 * Testing Calculus Operations
 */
#include "../../include/calculus/deriv.hpp"
#include <string>
#include <limits.h>
#include <gtest/gtest.h>

using ::testing::InitGoogleTest;
using ::testing::FloatLE;
using ::testing::DoubleLE;


namespace {
    calculus calc;

    // Test Derivative Operations
    TEST(deriv_test, deriv_at_val) {
        std::string string_0 = "4x^3 + 3x^1 + 2x^2 + 5x^1 + 2x^4";
        int x_0 = 2;

        EXPECT_EQ(128, calc.rm_deriv_at(string_0, x_0));

    }

}
/*
int main() {
    InitGoogleTest();
    
    return RUN_ALL_TESTS();
}
*/

