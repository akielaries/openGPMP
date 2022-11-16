/* RM-pkg
 * TESTING BASIC ARITHMETIC OPERATIONS
 */
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cassert>
#include "../include/RM_arith.hpp"


int main(){
    /*
     * This functionality was really only implemented for practice 
     * for dealing with complex algorithms and equations later. There
     * a plethora of way to store data and then perform basic arithmetic 
     * operations so it is trivial to reinvent the wheel for these types
     * of operations. 
     * Ideally if you want to perform the summation or product on a list
     * type structure of numbers you may want to implement it on your 
     * own, this implementation is just for fun :)
     * 
     * steps to perform arithmetic operations:
     * 1. declare arith object (see RM_arith.hpp)
     * 2. declare some variables initializing to values 
     * 3. using the declared arith object call the operations, 
     * rm_add, rm_sub, rm_mult
     * 4. print out the values if you want or manipulate them further
     */

    // declare our arithmetic class object
    arith ar;

    // declare some variables
    int a = 10;
    int b = 8;
    int c = 3;
    double d = 1.25;
    float e = 1.85;
    float f = 2.75;
    long g = 1.35;

    /* 
     * starting with addition operations with different data types. 
     * you can assign your result as a different type than the params
     */
    float r0 = ar.rm_add(a, b, c);
    int r1 = ar.rm_add(d, e, f, g);
    float r2 = ar.rm_add(d, e, f, g);

    printf("%d + %d + %d = %f\n", a, b, c, r0);
    printf("%f + %f + %f + %ld = %d\n", d, e, f, g, r1);
    printf("%f + %f + %f + %ld = %f\n\n", d, e, f, g, r2);

    /*
     * subtraction  
     */
    int r3 = ar.rm_sub(a, b, c);
    int r4 = ar.rm_sub(d, e, f ,g);
    float r5 = ar.rm_sub(d ,e, f, g);

    printf("%d - %d - %d = %d\n", a, b, c, r3);
    printf("%f - %f - %f - %d = %d\n", d, e, f, g, r4);
    printf("%f - %f - %f - %f = %f\n\n", d, e, f, g, r5);

    /*
     * multiplication 
     */
    int r6 = ar.rm_mult(a, b, c);
    int r7 = ar.rm_mult(d, e, f ,g);
    double r8 = ar.rm_mult(d ,e, f, g);

    printf("%d * %d * %d = %d\n", a, b, c, r6);
    printf("%f * %f * %f * %d = %d\n", d, e, f, g, r7);
    printf("%f * %f * %f * %ld = %f\n\n", d, e, f, g, r8);

    // you can also directly print
    /*
    std::cout << ar.rm_sum(2.5, 2) <<'\n'
            << ar.rm_sum(2, 2.5) <<'\n'
            << ar.rm_sum(1u, 2.5, 3.f, '0') <<'\n'
            << ar.rm_sum(4.2, 1, 1.223) <<'\n';
    */

    return 0;
}

