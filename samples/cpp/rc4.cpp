/* Testing the openMTPK stream cipher encryption algorithm on fields
 * of text using a XOR and tradition swap method.
 */
#include <iostream>
#include <openMTPK/nt/rc4.hpp>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>
//#include "../../include/nt/rc4.hpp"

int main() {
    /*
     * The RC4 algorithm in this case used 5 methods all dependent off 
     * eachother with only 2 being required by the user and 1 optional. 
     *  1. compute(): requires 
     */
    std::cout << "<------------------------------------------------------>\n\n";
    std::cout << "RIVEST CIPHER (RC4) EXAMPLE\n\n";

    /*<--------------------------------INIT--------------------------------->*/

    // declare RC4 class obj
    mtpk::RC4 rc;

    /*
     * declare some key values and strings to hash
     * these first 3 plaintext strings are verified from the RC4 wiki
     * and will be displayed when using a traditional swap method 
     */
    // expected hash = BBF316E8D940AF0AD3
    char *key0 = (char *)"Key";
    char *text0 = (char *)"Plaintext";
    // expected hash = 1021BF0420
    char *key1 = (char *)"Wiki";
    char *text1 = (char *)"pedia";
    // expected hash = 45A01F645FC35B383552544B9BF5
    char *key2 = (char *)"Secret";
    char *text2 = (char *)"Attack at dawn";

    char *key3 = (char *)"1";
    char *text3 = (char *)"username";

    /*
     * char value for using one of the following 
     * XOR swap         0 
     * traditional swap 1
     * byte swap        2
     */
    int x_swap = 0;
    int t_swap = 1;
    int b_swap = 2;

    /*<------------------------------------------------------------------>*/

    // declare a ciphertext pointer and allocate memory
    unsigned char *hashtext_0 = (unsigned char *)malloc(sizeof(int) *
                                                        strlen(text0));

    std::cout << "HASHTEXT_0: " << hashtext_0 << std::endl;
    printf("String before hash : %s\n", text0);

    /*
     * the main arguments are <key> & <plaintext> + allocated memory of
     * ciphertext as well as the swap type (x_swap true/false)
     */
    clock_t a;
    a = clock();

    unsigned char *computed_text = rc.compute(key0,
                                              text0,
                                              hashtext_0,
                                              x_swap);
    std::cout << "computed_text addr: " << &computed_text << std::endl;
    /*
     * function to store the computed hash 
     */
    std::string display_text = rc.store_hash(text0, hashtext_0, x_swap);
    std::cout << "COMPUTED HASH(XSWAP) = " << display_text << std::endl;

    // free whats no longer in use
    free(hashtext_0);
    a = clock() - a;
    double a_time = ((double)a) / CLOCKS_PER_SEC;
    printf("a_time = %f sec(s)\n\n", a_time);
    /*<------------------------------------------------------------------>*/
    printf("String before hash: %s\n", text1);
    unsigned char *hashtext_1 = (unsigned char *)malloc(sizeof(int) *
                                                        strlen(text1));

    clock_t b;
    b = clock();

    unsigned char *computed_text1 = rc.compute(key1,
                                               text1,
                                               hashtext_1,
                                               t_swap);
    std::cout << "computed_text1 addr: " << &computed_text1 << std::endl;
    std::string display_text1 = rc.store_hash(text1, hashtext_1, t_swap);
    std::cout << "COMPUTED HASH (TSWAP) = " << display_text1 << std::endl;

    free(hashtext_1);
    b = clock() - b;
    double b_time = ((double)b) / CLOCKS_PER_SEC;
    printf("b_time = %f sec(s)\n\n", b_time);
    /*<------------------------------------------------------------------>*/
    printf("String before hash: %s\n", text2);
    unsigned char *hashtext_2 = (unsigned char *)malloc(sizeof(int) *
                                                        strlen(text2));

    clock_t c;
    c = clock();
    unsigned char *computed_text2 = rc.compute(key2,
                                               text2,
                                               hashtext_2,
                                               b_swap);
    std::cout << "computed_text2 addr: " << &computed_text2 << std::endl;
    std::string display_text2 = rc.store_hash(text2, hashtext_2, b_swap);
    std::cout << "COMPUTED HASH (BSWAP) = " << display_text2 << std::endl;

    free(hashtext_2);
    c = clock() - c;
    double c_time = ((double)c) / CLOCKS_PER_SEC;
    printf("c_time = %f sec(s)\n\n", c_time);

    /*<------------------------------------------------------------------>*/
    printf("String before hash: %s\n", text3);
    unsigned char *hashtext_3 = (unsigned char *)malloc(sizeof(int) *
                                                        strlen(text3));

    clock_t d;
    d = clock();
    unsigned char *computed_text3 = rc.compute(key3,
                                               text3,
                                               hashtext_3,
                                               x_swap);
    std::cout << "computed_text2 addr: " << &computed_text3 << std::endl;
    std::string display_text3 = rc.store_hash(text2, hashtext_3, x_swap);
    std::cout << "COMPUTED HASH (XSWAP) = " << display_text3 << std::endl;

    free(hashtext_3);
    d = clock() - d;
    double d_time = ((double)d) / CLOCKS_PER_SEC;
    printf("d_time = %f sec(s)\n\n", d_time);

    return EXIT_SUCCESS;
}
