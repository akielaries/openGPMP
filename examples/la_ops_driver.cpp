/*
 * test driver program on the implementations for some basic Linear Algebra
 * operations. 
 */
#include <iostream>
#include <stdio.h>
#include "../include/la_ops.hpp"

using namespace std;


int main() {
    //la_ops la;
 
    //printf("BASIC LINEAR ALGEBRA OPERATIONS \n");

    // create vectors like arrays
    std::vector<int> a = {0, 7, 3};
    std::vector<int> b = {1, 2, 0};

    int c = a + b;

    printf("result : %d\n", c);
    // perform standard vector addition on the vectors
    //la.vec_add(a, b);

}

