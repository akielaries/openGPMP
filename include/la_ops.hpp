/*
 * definitions for basic Linear Algebra operations 
 */

#ifndef LAOPS_H
#define LAOPS_H
#include <vector>
#include <stdio.h>

using namespace std;

class la_operations {
    std::vector<int> x;
    std::vector<int> y;


    public:
        la_operations();
        
        /*
         * vectors of the same dimension size are just scalars as they only 
         * contain magnitude. vectors contain both magnitude + direction
         */
        // function to add two or more vectors
        // template <typename T>
        float scalar_add();
        // function to subtract two or more vectors
        float scalar_sub();
        // function to multiply two or more vectors
        float scalar_mult();
};


#endif

