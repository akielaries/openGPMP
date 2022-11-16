/* RM-pkg
 * TESTING BASIC ARITHMETIC OPERATIONS
 */
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cassert>
#include "../include/RM_arith.hpp"

template<typename T>
inline T rm_sum(T t){
    return t;
}

template<typename T, typename... Ts>
inline auto rm_sum(T t, Ts... ts){
    return t+rm_sum(ts...);
}

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
     */

    // declare our arithmetic class object
//    rm_sum<int>();

    // declare some variables
    int a = 10;
    int b = 8;
    int c = 3;

    double d = 1.25;
    float e = 1.85;
    float f = 2.75;
    long g = 1.35;

    // you can assign your result as a different type than the params
    float r0 = rm_sum(a, b, c);
    int r1 = rm_sum(d, e, f, g);
    float r2 = rm_sum(d, e, f, g);

    std::cout << "Sum 0 = " << r0 << '\n';
    std::cout << "Sum 1 = " << r1 << '\n';
    std::cout << "Sum 2 = " << r2 << '\n';

    // you can also directly print
    // 
    /*
    std::cout << ar.rm_sum(2.5, 2) <<'\n'
            << ar.rm_sum(2, 2.5) <<'\n'
            << ar.rm_sum(1u, 2.5, 3.f, '0') <<'\n'
            << ar.rm_sum(4.2, 1, 1.223) <<'\n';
    */
    return 0;
}

