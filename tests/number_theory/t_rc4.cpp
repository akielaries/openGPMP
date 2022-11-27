/*
 * Testing an implementation of RC4 encryption algorithm based off 
 * verified plaintext->hash conversions
 */
#include "../../include/number_theory/rc4.hpp"
#include <limits.h>
#include <gtest/gtest.h>

using ::testing::InitGoogleTest;
using ::testing::FloatLE;
using ::testing::DoubleLE;


namespace {
    RC4 rc;

    // BBF316E8D940AF0AD3
    char* key_0    = (char*)"Key";
    char* text_0   = (char*)"Plaintext";
    // 1021BF0420
    char* key_1    = (char*)"Wiki";
    char* text_1   = (char*)"pedia";        
    // 45A01F645FC35B383552544B9BF5
    char* key_2    = (char*)"Secret";
    char* text_2   = (char*)"Attack at dawn";
    
    TEST(rc4_test, hash_XOR) {
        int x_swap = 0;
        
        // allocate memory for the ciphertext pointer
        unsigned char *hashtext_0 = (unsigned char *)malloc(sizeof(int) * 
                strlen(text_0));


        EXPECT_EQ( , rc.compute( , ));
        EXPECT_EQ( , rc.compute( , ));
        EXPECT_EQ( , rc.compute( , ));
    }

    TEST(rc4_test, hash_TRAD) {
        int t_swap = 1;

    }

    TEST(rc4_test, hash_BYTE) {
        int b_swap = 2;

    }
}

/*
int main() {
    InitGoogleTest();
    
    return RUN_ALL_TESTS();
}
*/

