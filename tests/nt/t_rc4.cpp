/*
 * Testing an implementation of RC4 encryption algorithm based off 
 * verified plaintext->hash conversions
 */
#include "../../include/nt/rc4.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <limits.h>
#include <gtest/gtest.h>

using ::testing::InitGoogleTest;
using ::testing::FloatLE;
using ::testing::DoubleLE;


namespace {
    mtpk::RC4 rc;

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
        std::string ptext_0 = "|xbb||xf3||x16||xe8||xd9||x40||xaf||x0a||xd3|";
        // allocate memory for the ciphertext pointer
        unsigned char *hashtext_0 = (unsigned char *)malloc(sizeof(int) * 
                strlen(text_0));
        unsigned char *computed_0 = rc.compute(key_0, 
                                                text_0, 
                                                hashtext_0, 
                                                x_swap);
        std::string displayed_0 = rc.store_hash(text_0,
                                                hashtext_0,
                                                x_swap);
        EXPECT_EQ(ptext_0 , displayed_0);
        /*<------------------------------------------------------------------>*/
        std::string ptext_01 = "|x10||x21||xbf||x04||x20|";
        unsigned char *hashtext_01 = (unsigned char *)malloc(sizeof(int) *
                strlen(text_1));
        unsigned char *computed_01 = rc.compute(key_1,
                                                text_1,
                                                hashtext_01,
                                                x_swap);
        std::string displayed_01 = rc.store_hash(text_1,
                                                hashtext_01,
                                                x_swap);
        EXPECT_EQ(ptext_01, displayed_01);
        /*<------------------------------------------------------------------>*/
        std::string ptext_02 =
        "|x45||xa0||x1f||x64||x5f||xc3||x5b||x38||x35||x52||x54||x4b||x9b||xf5|";
        unsigned char *hashtext_02 = (unsigned char *)malloc(sizeof(int) *
                strlen(text_2));
        unsigned char *computed_02 = rc.compute(key_2,
                                                text_2,
                                                hashtext_02,
                                                x_swap);
        std::string displayed_02 = rc.store_hash(text_2,
                                                hashtext_02,
                                                x_swap);
        EXPECT_EQ(ptext_02, displayed_02);
    }
    
    TEST(rc4_test, hash_TRAD) {
        int t_swap = 1;
        std::string ptext_1 = "BBF316E8D940AF0AD3";
        unsigned char *hashtext_10 = (unsigned char *)malloc(sizeof(int) *
                strlen(text_0));
        unsigned char *computed_10 = rc.compute(key_0, 
                                                text_0, 
                                                hashtext_10, 
                                                t_swap);
        std::string displayed_10 = rc.store_hash(text_0,
                                                hashtext_10,
                                                t_swap);
        EXPECT_EQ(ptext_1, displayed_10);
        /*<------------------------------------------------------------------>*/
        std::string ptext_11 = "1021BF0420";
        unsigned char *hashtext_11 = (unsigned char *)malloc(sizeof(int) *
                strlen(text_1));
        unsigned char *computed_11 = rc.compute(key_1,
                                                text_1,
                                                hashtext_11,
                                                t_swap);
        std::string displayed_11 = rc.store_hash(text_1,
                                                hashtext_11,
                                                t_swap);
        EXPECT_EQ(ptext_11, displayed_11);
        /*<------------------------------------------------------------------>*/
        std::string ptext_12 = "45A01F645FC35B383552544B9BF5";
        unsigned char *hashtext_12 = (unsigned char *)malloc(sizeof(int) *
                strlen(text_2));
        unsigned char *computed_12 = rc.compute(key_2,
                                                text_2,
                                                hashtext_12,
                                                t_swap);
        std::string displayed_12 = rc.store_hash(text_2,
                                                hashtext_12,
                                                t_swap);
        EXPECT_EQ(ptext_12, displayed_12);
    }

    TEST(rc4_test, hash_BYTE) {
        int b_swap = 2;
        std::string ptext_2 = "BBF316E8D940AF0AD3";
        unsigned char *hashtext_20 = (unsigned char *)malloc(sizeof(int) *
                strlen(text_0));
        unsigned char *computed_20 = rc.compute(key_0, 
                                                text_0, 
                                                hashtext_20, 
                                                b_swap);
        std::string displayed_20 = rc.store_hash(text_0,
                                                hashtext_20,
                                                b_swap);
        EXPECT_EQ(ptext_2, displayed_20);
        /*<------------------------------------------------------------------>*/
        std::string ptext_21 = "1021BF0420";
        unsigned char *hashtext_21 = (unsigned char *)malloc(sizeof(int) *
                strlen(text_1));
        unsigned char *computed_21 = rc.compute(key_1,
                                                text_1,
                                                hashtext_21,
                                                b_swap);
        std::string displayed_21 = rc.store_hash(text_1,
                                                hashtext_21,
                                                b_swap);
        EXPECT_EQ(ptext_21, displayed_21);
        /*<------------------------------------------------------------------>*/
        std::string ptext_22 = "45A01F645FC35B383552544B9BF5";
        unsigned char *hashtext_22 = (unsigned char *)malloc(sizeof(int) *
                strlen(text_2));
        unsigned char *computed_22 = rc.compute(key_2,
                                                text_2,
                                                hashtext_22,
                                                b_swap);
        std::string displayed_22 = rc.store_hash(text_2,
                                                hashtext_22,
                                                b_swap);
        EXPECT_EQ(ptext_22, displayed_22);
    }

    TEST(rc4_test, SWAP_error_4) {
        int swap_FALSE = 4;
        std::string expected_error_text = "[-] Invalid swap_type";

        /*BEGIN RC4 ITERATIONS*/
        std::string ptext_FALSE = "1021BF0420";
        unsigned char *hashtext_FALSE = (unsigned char *)malloc(sizeof(int) *
                strlen(text_2));

        EXPECT_THROW(rc.compute(key_2, text_2, hashtext_FALSE, swap_FALSE),
                        std::runtime_error);

        ASSERT_THROW(rc.compute(key_2, text_2, hashtext_FALSE, swap_FALSE),
                        std::runtime_error);
    }

    TEST(rc4_test, SWAP_error_127) {
        int swap_FALSE_127 = 127;
        std::string expected_error_text_127 = "[-] Invalid swap_type";

        /*BEGIN RC4 ITERATIONS*/
        std::string ptext_FALSE_127 = "1021BF0420";
        unsigned char *hashtext_FALSE_127 = (unsigned char *)malloc(sizeof(int) *
                strlen(text_2));

        EXPECT_THROW(rc.compute(key_2, text_2, hashtext_FALSE_127, 
                    swap_FALSE_127), std::runtime_error);

        ASSERT_THROW(rc.compute(key_2, text_2, hashtext_FALSE_127, 
                    swap_FALSE_127), std::runtime_error);
    }

    TEST(rc4_test, NULL_ciphertext) {
        int swap_NULL = 0;
        std::string expected_error_text_127 = "[-] Error Allocating Memory";

        /*BEGIN RC4 ITERATIONS*/
        std::string ptext_NULL = "1021BF0420";
        unsigned char *hashtext_NULL = nullptr;
            //(unsigned char *)malloc(sizeof(int) *
            //    strlen(swap_NULL));

        EXPECT_THROW(rc.compute(key_2, text_2, hashtext_NULL, 
                    swap_NULL), std::runtime_error);

        ASSERT_THROW(rc.compute(key_2, text_2, hashtext_NULL, 
                    swap_NULL), std::runtime_error);
    }

}

