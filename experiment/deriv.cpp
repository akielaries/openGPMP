#include <vector>
#include <iostream>
// Function to take the derivative of a polynomial
std::vector<int> differentiate(const std::vector<int>& coefficients) {
    std::vector<int> result;
    
    // Start from the second term (index 1)
    for (int i = 1; i < coefficients.size(); ++i) {
        int derivative_coefficient = coefficients[i] * i;
        result.push_back(derivative_coefficient);
    }
    
    return result;
}

int main() {
    // Coefficients of the polynomial: 3x^3 + 2x^2 - 5x + 1
    std::vector<int> coefficients = {1, -5, 2, 3};

    // Take the derivative
    std::vector<int> derivative = differentiate(coefficients);

    // Print the result with cleaned-up formatting
    std::cout << "Original polynomial: ";
    for (int i = coefficients.size() - 1; i >= 0; --i) {
        if (coefficients[i] != 0) {
            std::cout << coefficients[i] << "x^" << i << " ";
            if (i > 0 && coefficients[i - 1] != 0) {
                std::cout << "+ ";
            }
        }
    }

    std::cout << "\nDerivative: ";
    for (int i = derivative.size() - 1; i >= 0; --i) {
        if (derivative[i] != 0) {
            std::cout << derivative[i] << "x";
            if (i > 0) {
                std::cout << "^" << i << " ";
                if (i > 1 && derivative[i - 1] != 0) {
                    std::cout << "+ ";
                }
            } else {
                if (i == 0) {
                    std::cout << " ";
                }
            }
        }
    }

    return 0;
}

