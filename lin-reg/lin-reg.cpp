/*
 * taking a look at implementing regression in c++
 */
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>

using namespace std;

class regression {
    // Dynamic array which is going to contain all (i-th x)
    vector<float> x;

    // Dynamic array which is going to contain all (i-th y)
    vector<float> y;
    
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
    /*
     * Constructor to provide the default values to all the terms in the object 
     * of class regression
     */
    regression() {
        coeff = 0;
        constant = 0;
        sum_y = 0;
        sum_y_square = 0;
        sum_x_square = 0;
        sum_x = 0;
        sum_xy = 0;
    }
 
    // Function that calculate the coefficient/slope of the best fitting line
    void calculate_coefficient() {
        float N = x.size();
        float numerator
            = (N * sum_xy - sum_x * sum_y);
        float denominator
            = (N * sum_x_square - sum_x * sum_x);
        coeff = numerator / denominator;
    }
 
    /*
     * Member function that will calculate the constant term of the best 
     * fitting line
     */
    void calculate_constant() {
        float N = x.size();
        float numerator
            = (sum_y * sum_x_square - sum_x * sum_xy);
        float denominator
            = (N * sum_x_square - sum_x * sum_x);
        constant = numerator / denominator;
    }
 
    // Function that return the number of entries (xi, yi) in the data set
    int data_size() {
        return x.size();
    }
 
    // Function that return the coefficient/slope of the best fitting line
    float return_coefficient() {
        if (coeff == 0)
            calculate_coefficient();
        return coeff;
    }
 
    // Function that return the constant term of the best fitting line
    float return_constant() {
        if (constant == 0)
            calculate_constant();
        return constant;
    }
 
    // Function that print the best fitting line
    void best_fit() {
        if (coeff == 0 && constant == 0) {
            calculate_coefficient();
            calculate_constant();
        }
        cout << "The best fitting line is y = "
             << coeff << "x + " << constant << endl;
    }
 
    // Function to take input from the dataset
    void get_input(int n) {
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
    void show_data() {
        for (int i = 0; i < 62; i++) {
            printf("_");
        }
        printf("\n\n");
        printf("|%15s%5s %15s%5s%20s\n",
               "X", "", "Y", "", "|");
 
        for (int i = 0; i < x.size(); i++) {
            printf("|%20f %20f%20s\n",
                   x[i], y[i], "|");
        }
 
        for (int i = 0; i < 62; i++) {
            printf("_");
        }
        printf("\n");
    }
 
    // Function to predict the value corresponding to some input
    float predict(float x) {
        return coeff * x + constant;
    }
 
    // Function that returns overall sum of square of errors
    float error_square() {
        float ans = 0;
        for (int i = 0;
             i < x.size(); i++) {
            ans += ((predict(x[i]) - y[i])
                    * (predict(x[i]) - y[i]));
        }
        return ans;
    }
    /*
     * Functions that return the error i.e the difference between the actual 
     * value and value predicted by our model
     */
    float error_in(float num) {
        for (int i = 0;
             i < x.size(); i++) {
            if (num == x[i]) {
                return (y[i] - predict(x[i]));
            }
        }
        return 0;
    }
};

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

