/*
 * TESTING BASIC ARITHMETIC OPERATIONS
 */
#include <cassert>
#include <iostream>
//#include <openMTPK/arithmetic.hpp>
#include "../../include/arithmetic.hpp"
#include <stdio.h>
#include <time.h>
#include <vector>

int main() {
    std::cout << "TESTING ARITHMETIC OPERATIONS\n" << std::endl;
    /*
     * This functionality was really only implemented for practice
     * for dealing with complex algorithms and equations later. There
     * a plethora of ways to store data and then perform basic
     * arithmetic operations so it is trivial to reinvent the wheel
     * for these types of operations. Ideally if you want to perform
     * the summation or product on a list type structure of numbers
     * you may want to implement it on your own, this implementation
     * is just for fun :)
     *
     * steps to perform arithmetic operations:
     * 1. declare arith object (see RM_arith.hpp)
     * 2. declare some variables initializing to values
     * 3. using the declared arith object call the operations,
     * rm_add, rm_sub, rm_mult
     * 4. print out the values if you want or manipulate them further
     */

    // declare our arithmetic class object, template class keep in mind
    // numeric datatypes
    mtpk::Arith<int> ar;

    // declare some variables
    int a = 10;
    int b = 8;
    int c = 3;
    double d = 1.25;
    float e = 1.85;
    float f = 2.75;
    long g = 1.35;
    float y = 9743298223.945;
    float z = 34895542235.8854;

    /*
     * starting with addition operations with different data types.
     */
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << ar.arr_add(arr, n) << '\n';
    std::cout << ar.arr_sub(arr, n) << '\n';
    std::cout << ar.arr_mlt(arr, n) << '\n';

    /*
     * arithmetic basics
     */
    mtpk::Basics ba;
    int r10 = 10;
    int r11 = 3;
    int r12 = ba.greatest_power(r10, r11);
    printf("The greatest power of %d that divides %d! = %d\n", r10, r11,
           r12);

    int r13 = 7;
    int r14 = 3;
    int r15 = ba.greatest_power(r13, r14);
    printf("The greatest power of %d that divides %d! = %d\n", r13, r14,
           r15);

    int r16 = 2;
    int r17 = 4;
    int r18 = ba.op_gcd(r16, r17);
    printf("The GCD of %d & %d = %d\n", r16, r17, r18);

    int r19 = 232;
    int r20 = 96;
    int r21 = ba.op_gcd(r19, r20);
    printf("The GCD of %d & %d = %d\n", r19, r20, r21);

    return 0;
}
