/* RM-pkg
 * TESTING BASIC ARITHMETIC OPERATIONS
 * test driver program on the implementations for some basic Linear Algebra
 * operations. 
 */
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cassert>
#include "../include/RM_arith.hpp"


template<typename T>
inline T sum(T t){
    return t;
}

template<typename T, typename... Ts>
inline auto sum(T t, Ts... ts){
    return t+sum(ts...);
}

#include<iostream>
int main(){
    /*
     * This functionality was really only implemented for practice 
     * for dealing with complex algorithms and equations later. There
     * a plethora of way to store data and then perform basic arithmetic 
     * operations so it is trivial to reinvent the wheel for these types
     * of operations. 
     * Ideally if you want to perform the summation or product on a list
     * type structure of numbers you would implement it on your own, this
     * is purely visual :)
     */

    // summation of different data types
    std::cout << sum(2.5, 2) <<'\n'
            << sum(2, 2.5) <<'\n'
            << sum(1u, 2.5, 3.f, '0') <<'\n'
            << sum(4.2, 1, 1.223) <<'\n';

    return 0;
}

