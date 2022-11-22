/*
 * taking a look at different mathematical operations seen in Linear
 * Algebra in C++
 */
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "../../include/lao.hpp"


/*
 * Constructor to provide the default values to all the terms in the object 
 * of class la_ops
 */
la_ops::la_ops() {
    coeff = 0;
    constant = 0;
    sum_y = 0;
    sum_y_square = 0;
    sum_x_square = 0;
    sum_x = 0;
    sum_xy = 0;
}
 
// adding two or more vectors
float la_ops::vector_add(vector0, vector1) {
    int i = 0;

    // declare data structure to store sums of vectors indices
    // arr?

    // traverse vectors, add elements
    for (i; i < vector0.size(); i++) {
        int sum = vector0[i] + vector1[i];
        // append arr?
    }
    // return arr?
    return sum;

}


