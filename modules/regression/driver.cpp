/*
 * test driver program for our implementation of linear regression 
 */
#include <iostream>
#include <stdio.h>
#include "LR.h"

using namespace std;


int main() {
    const char* test_file = "../data/test_input.csv";
    freopen(test_file, "r", stdin);
    regression reg;
 
    // Number of pairs of (xi, yi) in the dataset
    // int n;
    // cin >> n;
 
    int n = num_rows(test_file);
    // cin >> n;

    printf("Number of rows in data set: %d\n", n);
    // Calling function takeInput to take input of n pairs
    reg.get_input(n);
 
    // Printing the best fitting line
    reg.best_fit();

    
    /* CALCULATING PREDICTIONS */
    cout << "Predicted value at 250 = "
         << reg.predict(250) << endl;

    cout << "Predicted value at 500 = "
         << reg.predict(500) << endl;
    
    cout << "Predicted value at 1000 = "
         << reg.predict(1000) << endl;
    
    cout << "Predicted value at 1500 = "
         << reg.predict(1500) << endl;
    
    cout << "Predicted value at 2000 = "
         << reg.predict(2000) << endl;
    
    cout << "Predicted value at 2500 = "
         << reg.predict(2500) << endl;
    
    cout << "Predicted value at 3000 = "
         << reg.predict(3000) << endl;

    cout << "Predicted value at 3500 = "
         << reg.predict(3500) << endl;
    
    cout << "Predicted value at 4000 = "
         << reg.predict(4000) << endl;
    
    cout << "Predicted value at 4500 = "
         << reg.predict(4500) << endl;
    
    cout << "Predicted value at 5000 = "
         << reg.predict(5000) << endl;
    
    cout << "Predicted value at 5500 = "
         << reg.predict(5500) << endl;

    cout << "The errorSquared  = "
         << reg.error_square() << endl;
    

    /* CALCULATING ERRORS */

    cout << "Error value at 250 = "
         << reg.error_in(250) << endl;

    cout << "Error value at 500 = "
         << reg.error_in(500) << endl;
    
    cout << "Error value at 1000 = "
         << reg.error_in(1000) << endl;
    
    cout << "Error value at 1500 = "
         << reg.error_in(1500) << endl;
    
    cout << "Error value at 2000 = "
         << reg.error_in(2000) << endl;
    
    cout << "Error value at 2500 = "
         << reg.error_in(2500) << endl;

    cout << "Error value at 3000 = "
         << reg.error_in(3000) << endl;

    cout << "Error value at 3500 = "
         << reg.error_in(3500) << endl;
    
    cout << "Error value at 4000 = "
         << reg.error_in(4000) << endl;
    
    cout << "Error value at 4500 = "
         << reg.error_in(4500) << endl;
    
    cout << "Error value at 5000 = "
         << reg.error_in(5000) << endl;
    
    cout << "Error value at 5500 = "
         << reg.error_in(5500) << endl;

}

