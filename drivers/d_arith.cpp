/* RM-pkg
 * TESTING BASIC ARITHMETIC OPERATIONS
 */
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <cassert>
#include "../include/arithmetic/arith.hpp"


int main(){
    std::cout << "TESTING ARITHMETIC OPERATIONS\n" << std::endl;
    /*
     * This functionality was really only implemented for practice 
     * for dealing with complex algorithms and equations later. There
     * a plethora of ways to store data and then perform basic arithmetic 
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
    float y = 9743298223.945;
    float z = 34895542235.8854;

    /* 
     * starting with addition operations with different data types. 
     */
    clock_t adding;
    adding = clock();

    float r0 = ar.add(a, b, c);
    int r1 = ar.add(d, e, f, g);
    float r2 = ar.add(d, e, f, g);
    float r99 = ar.add(a,b,c,d,e,f,g,a,b,c,d,e,f,g,y,z);

    adding = clock() - adding;
    double add_time = ((double)adding) / CLOCKS_PER_SEC;
    printf("rm_add() performed in: %f seconds\n\n", add_time);

    printf("%d + %d + %d = %f\n", a, b, c, r0);
    printf("%f + %f + %f + %ld = %d\n", d, e, f, g, r1);
    printf("%f + %f + %f + %ld = %f\n\n", d, e, f, g, r2);
    printf("Big result #1 = %f\n\n", r99);

    /*
     * subtraction  
     */
    clock_t subbing;
    subbing = clock();

    int r3 = ar.sub(a, b, c);
    int r4 = ar.sub(d, e, f ,g);
    float r5 = ar.sub(d ,e, f, g);

    subbing = clock() - subbing;
    double sub_time = ((double)subbing) / CLOCKS_PER_SEC;
    printf("rm_sub() performed in: %f seconds\n\n", sub_time);
    
    printf("%d - %d - %d = %d\n", a, b, c, r3);
    printf("%f - %f - %f - %ld = %d\n", d, e, f, g, r4);
    printf("%f - %f - %f - %ld = %f\n\n", d, e, f, g, r5);

    /*
     * multiplication 
     */
    clock_t multing;
    multing = clock();

    int r6 = ar.mult(a, b, c);
    int r7 = ar.mult(d, e, f ,g);
    double r8 = ar.mult(d ,e, f, g);
    float r98 = ar.mult(a,b,c,d,e,f,g,a,b,c,d,e,f,g,y,z);

    multing = clock() - multing;
    double mult_time = ((double)multing) / CLOCKS_PER_SEC;
    printf("rm_mult() performed in: %f seconds\n\n", mult_time);

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

    return 0;
}

