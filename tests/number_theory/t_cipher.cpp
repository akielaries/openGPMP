/*
 * Testing the implementation of random cipher algorithms
 */
#include "../../include/number_theory/cipher.hpp"
#include <limits.h>
#include <gtest/gtest.h>

using ::testing::InitGoogleTest;
using ::testing::FloatLE;
using ::testing::DoubleLE;


namespace {
    CIPHER cc;

    TEST(ccipher_test, caesar_0) {
        std::string text_0 = "Plaintext";
        int key_shift_0 = 5;
        std::string hashtext_0 = cc.C_cipher(text_0, key_shift_0);
        std::string expected_0 = "Uqfnsyjcy";

        EXPECT_EQ(expected_0, hashtext_0);
    }
    
    TEST(ccipher_test, caesar_1) {
        std::string text_1 = "ATTACKATONCE";
        int key_shift_1 = 4;
        std::string hashtext_1 = cc.C_cipher(text_1, key_shift_1);
        std::string expected_1 = "EXXEGOEXSRGI";
    
        EXPECT_EQ(expected_1, hashtext_1);
    }

    TEST(ccipher_test, caesar_2) {
        std::string text_2 = "EaSyPASsWorD";
        int key_shift_2 = 14;
        std::string hashtext_2 = cc.C_cipher(text_2, key_shift_2);
        std::string expected_2 = "SoGmDOGgKcfR";
    
        EXPECT_EQ(expected_2, hashtext_2);
    }
    
    TEST(kcipher_test, keyword_0) {
        std::string text_3 = "Password";
        std::string key_shift_3 = "Computer";

        // encode
        std::string encoded_text_0 = cc.KC_encode(key_shift_3);
        // cipher
        std::string hashtext_3 = cc.KC_cipher(text_3, encoded_text_0);
        
        std::string expected_3 = "JCNNWILP";
        
        EXPECT_EQ(expected_3, hashtext_3);
    }

    TEST(kcipher_test, keyword_1) {
        std::string text_4 = "Password";
        std::string key_shift_4 = "Password";

        // encode
        std::string encoded_text_1 = cc.KC_encode(key_shift_4);
        // cipher
        std::string hashtext_4 = cc.KC_cipher(text_4, encoded_text_1);
        
        std::string expected_4 = "KPNNVJMW";
        
        EXPECT_EQ(expected_4, hashtext_4);
    }
}

/*
int main() {
    InitGoogleTest();
    
    return RUN_ALL_TESTS();
}
*/

