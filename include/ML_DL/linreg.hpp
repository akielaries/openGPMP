/*
 * Linear regression is a statistical method for modeling relationships 
 * between a dependent variable with a given set of independent variables.
 */

#ifndef LINREG_H
#define LINREG_H
#include <vector>
#include <stdio.h>


class regression {
    // Dynamic array which is going to contain all (i-th x)
    std::vector<float> x;
    // Dynamic array which is going to contain all (i-th y)
    std::vector<float> y;
    // Store the coefficient/slope in the best fitting line
    float coeff;
    // Store the constant term in the best fitting line
    float constant;
    // Contains sum of product of all (i-th x) and (i-th y)
    float sum_xy;
    // Contains sum of all (i-th x)
    float sum_x;
    // Contains sum of all (i-th y)
    float sum_y;
    // Contains sum of square of all (i-th x)
    float sum_x_square;
    // Contains sum of square of all (i-th y)
    float sum_y_square;

    public:
        regression();
        /*{
            coeff;
            constant;
            sum_y;
            sum_y_square;
            sum_x_square;
            sum_x;
            sum_xy;
        }*/

        // Function that calculate the coefficient/slope of the best fitting line
        void calculate_coeffecient();
        /*
         * Member function that will calculate the constant term of the best 
         * fitting line
         */
        void calculate_constant();
        // Function that return the number of entries (xi, yi) in the data set
        int data_size();
        // Function that return the coefficient/slope of the best fitting line
        float return_coeffecient();
        // Function that return the constant term of the best fitting line
        float return_constant();
        // Function that print the best fitting line
        void best_fit();
        // Function to take input from the dataset
        void get_input(int n);
        // Function to show the data set
        void show_data();
        // Function to predict the value corresponding to some input
        float predict(float x);
        // Function that returns overall sum of square of errors
        float error_square(); 
        /*
         * Functions that return the error i.e the difference between the actual 
         * value and value predicted by our model
         */
        float error_in(float num);
};

// function that calculates the number of rows in a file
int num_rows(const char* input);


#endif

