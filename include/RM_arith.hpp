/*
 * definitions for basic Linear Algebra operations 
 */

#ifndef RMARITH_H
#define RMARITH_H
#include <vector>
#include <stdio.h>


class la_operations {
    std::vector<int> x;
    std::vector<int> y;


    public:
        la_operations();
        
        /*
         * vectors of the same dimension size are just scalars as they only 
         * contain magnitude. vectors contain both magnitude + direction
         */
        // function to add two 1D vectors
        // template <typename T>
        float scalar_add();
        // function to subtract two 1D vectors
        float scalar_sub();
        // function to multiply two 1D vectors
        float scalar_mult();
};


#endif

