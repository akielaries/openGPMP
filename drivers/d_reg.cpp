/* RM-pkg
 * TESTING LINEAR REGRESSION
 * test driver program for our implementation of linear regression 
 */
#include <iostream>
#include <stdio.h>
#include "../include/linreg.hpp"


int main() {
    const char* test_file = "data/school_scores.csv";
    freopen(test_file, "r", stdin);
    regression reg;
 
    // Number of pairs of (xi, yi) in the dataset
    // int n;
    // cin >> n;
 
    int n = num_rows(test_file);
    // cin >> n;
    printf("LINEAR REGRESSION EXAMPLE ON YEAR/GPA DATA IN MATHEMATICS\n");

    printf("Number of rows in data set: %d\n", n);
    // Calling function takeInput to take input of n pairs
    reg.get_input(n);
 
    // Printing the best fitting line
    reg.best_fit();

    
    /* CALCULATING PREDICTIONS */
    int v1 = 1995;
    float v1_v = reg.predict(v1);
    float v1_e = reg.error_in(v1);
    printf("Predicted value at %d   = %f\n", v1, v1_v);
    printf("Error value at %d       = %f\n\n", v1, v1_e);

    int v2 = 1997;
    float v2_v = reg.predict(v2);
    float v2_e = reg.error_in(v2);
    printf("Predicted value at %d   = %f\n", v2, v2_v);
    printf("Error value at %d       = %f\n\n", v2, v2_e);

    int v3 = 1999;
    float v3_v = reg.predict(v3);
    float v3_e = reg.error_in(v3);
    printf("Predicted value at %d   = %f\n", v3, v3_v);
    printf("Error value at %d       = %f\n\n", v3, v3_e);

    int v4 = 2001;
    float v4_v = reg.predict(v4);
    float v4_e = reg.error_in(v4);
    printf("Predicted value at %d   = %f\n", v4, v4_v);
    printf("Error value at %d       = %f\n\n", v4, v4_e);

    int v5 = 2003;
    float v5_v = reg.predict(v5);
    float v5_e = reg.error_in(v5);
    printf("Predicted value at %d   = %f\n", v5, v5_v);
    printf("Error value at %d       = %f\n\n", v5, v5_e);

    int v6 = 2005;
    float v6_v = reg.predict(v6);
    float v6_e = reg.error_in(v6);
    printf("Predicted value at %d   = %f\n", v6, v6_v);
    printf("Error value at %d       = %f\n\n", v6, v6_e);

    int v7 = 2006;
    float v7_v = reg.predict(v7);
    float v7_e = reg.error_in(v7);
    printf("Predicted value at %d   = %f\n", v7, v7_v);
    printf("Error value at %d       = %f\n\n", v7, v7_e);

    int v8 = 2007;
    float v8_v = reg.predict(v8);
    float v8_e = reg.error_in(v8);
    printf("Predicted value at %d   = %f\n", v8, v8_v);
    printf("Error value at %d       = %f\n\n", v8, v8_e);

    int v10 = 2016;
    float v10_v = reg.predict(v10);
    float v10_e = reg.error_in(v10);
    printf("Predicted value at %d   = %f\n", v10, v10_v);
    printf("Error value at %d       = %f\n\n", v10, v10_e);

    int v11 = 2017;
    float v11_v = reg.predict(v11);
    float v11_e = reg.error_in(v11);
    printf("Predicted value at %d   = %f\n", v11, v11_v);
    printf("Error value at %d       = %f\n\n", v11, v11_e);

}

