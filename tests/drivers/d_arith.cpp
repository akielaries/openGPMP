/*
 * TESTING BASIC ARITHMETIC OPERATIONS
 */
#include "../include/arithmetic/arith.hpp"
#include "../include/arithmetic/arithbase.hpp"
#include <cassert>
#include <iostream>
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

    // declare our arithmetic class object
    Arith ar;

    // declare some variables
    int a    = 10;
    int b    = 8;
    int c    = 3;
    double d = 1.25;
    float e  = 1.85;
    float f  = 2.75;
    long g   = 1.35;
    float y  = 9743298223.945;
    float z  = 34895542235.8854;

    /*
     * starting with addition operations with different data types.
     */
    float r0  = ar.add(a, b, c);
    int r1    = ar.add(d, e, f, g);
    float r2  = ar.add(d, e, f, g);
    float r99 = ar.add(a, b, c, d, e, f, g, a, b, c, d, e, f, g, y, z);

    printf("%d + %d + %d = %f\n", a, b, c, r0);
    printf("%f + %f + %f + %ld = %d\n", d, e, f, g, r1);
    printf("%f + %f + %f + %ld = %f\n\n", d, e, f, g, r2);
    printf("Big result #1 = %f\n\n", r99);

    /*
     * subtraction
     */
    int r3   = ar.sub(a, b, c);
    int r4   = ar.sub(d, e, f, g);
    float r5 = ar.sub(d, e, f, g);

    printf("%d - %d - %d = %d\n", a, b, c, r3);
    printf("%f - %f - %f - %ld = %d\n", d, e, f, g, r4);
    printf("%f - %f - %f - %ld = %f\n\n", d, e, f, g, r5);

    /*
     * multiplication
     */
    int r6    = ar.mult(a, b, c);
    int r7    = ar.mult(d, e, f, g);
    double r8 = ar.mult(d, e, f, g);
    float r98 = ar.mult(a, b, c, d, e, f, g, a, b, c, d, e, f, g, y, z);

    printf("%d * %d * %d = %d\n", a, b, c, r6);
    printf("%f * %f * %f * %ld = %d\n", d, e, f, g, r7);
    printf("%f * %f * %f * %ld = %f\n\n", d, e, f, g, r8);
    printf("Big result #2 = %f\n\n", r98);

    // you can also directly print
    /*
    std::cout << ar.rm_sum(2.5, 2) <<'\n'
            << ar.rm_sum(2, 2.5) <<'\n'
            << ar.rm_sum(1u, 2.5, 3.f, '0') <<'\n'
            << ar.rm_sum(4.2, 1, 1.223) <<'\n';
    */

    /*
     * arithmetic basics
     */
    Basics ba;
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
    int r18 = ba.rm_gcd(r16, r17);
    printf("The GCD of %d & %d = %d\n", r16, r17, r18);

    int r19 = 232;
    int r20 = 96;
    int r21 = ba.rm_gcd(r19, r20);
    printf("The GCD of %d & %d = %d\n", r19, r20, r21);

    return 0;
}
