/*
 * taking a look at implementing regression in c++
 */
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "LR.h"

using namespace std;

/*
 * Constructor to provide the default values to all the terms in the object 
 * of class regression
 */
regression::regression() {
    coeff = 0;
    constant = 0;
    sum_y = 0;
    sum_y_square = 0;
    sum_x_square = 0;
    sum_x = 0;
    sum_xy = 0;
}
 
// Function that calculate the coefficient/slope of the best fitting line
void regression::calculate_coeffecient() {
    float N = x.size();
    float numerator = (N * sum_xy - sum_x * sum_y);
    float denominator = (N * sum_x_square - sum_x * sum_x);
    coeff = numerator / denominator;
}

/*     
 * Member function that will calculate the constant term of the best 
 * fitting line
 */
void regression::calculate_constant() {
    float N = x.size();
    float numerator = (sum_y * sum_x_square - sum_x * sum_xy);
    float denominator = (N * sum_x_square - sum_x * sum_x);
    constant = numerator / denominator;
}

// Function that return the number of entries (xi, yi) in the data set
int regression::data_size() {
    return x.size();
}

// Function that return the coefficient/slope of the best fitting line
float regression::return_coeffecient() {
    if (coeff == 0)
        calculate_coeffecient();
    return coeff;
}
 
// Function that return the constant term of the best fitting line
float regression::return_constant() {
    if (constant == 0)
        calculate_constant();
    return constant;
}

// Function that print the best fitting line
void regression::best_fit() {
    if (coeff == 0 && constant == 0) {
        calculate_coeffecient();
        calculate_constant();
    }
    cout << "The best fitting line is y = "
        << coeff << "x + " << constant << endl;
    }
 
// Function to take input from the dataset
void regression::get_input(int n) {
    for (int i = 0; i < n; i++) {
        /*
         * In a csv file all the values of xi and yi are separated by 
         * commas
         */
        char comma;
        float xi;
        float yi;
        cin >> xi >> comma >> yi;
        sum_xy += xi * yi;
        sum_x += xi;
        sum_y += yi;
        sum_x_square += xi * xi;
        sum_y_square += yi * yi;
        x.push_back(xi);
        y.push_back(yi);
    }
}

// Function to show the data set    
void regression::show_data() {
    for (int i = 0; i < 62; i++) {
        printf("_");
    }
    printf("\n\n");
    printf("|%15s%5s %15s%5s%20s\n", "X", "", "Y", "", "|");

    for (int i = 0; i < x.size(); i++) {
        printf("|%20f %20f%20s\n", x[i], y[i], "|");
    }
 
    for (int i = 0; i < 62; i++) {
        printf("_");
    }
    printf("\n");
}
 
// Function to predict the value corresponding to some input
float regression::predict(float x) {
    return coeff * x + constant;
}
 
// Function that returns overall sum of square of errors
float regression::error_square() {
    float ans = 0;
    for (int i = 0; i < x.size(); i++) {
        ans += ((predict(x[i]) - y[i]) * (predict(x[i]) - y[i]));
    }
    return ans;
}
/*
 * Functions that return the error i.e the difference between the actual 
 * value and value predicted by our model
 */
float regression::error_in(float num) {
    for (int i = 0; i < x.size(); i++) {
        if (num == x[i]) {
            return (y[i] - predict(x[i]));
        }
    }
    return 0;
}

int num_rows(const char* input) {
    int num = 0;
    string row;
    
    // create input file stream
    ifstream file(input);

    while (getline(file, row)) {
        num++;
    }

    return num;

} 
/*
int num_col(const char* input) {
    int num = 0;
    string col;
    ifstream file(input);

    return col;

}
*/

