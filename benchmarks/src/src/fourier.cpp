/**
 * Fast & Discrete Fourier Transforms
 */

#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

// compute the Discrete Fourier Transform (DFT) of a sequence
std::vector<std::complex<double>>
DFT(const std::vector<std::complex<double>> &x) {
    int N = x.size(); // Size of the input sequence
    std::vector<std::complex<double>> X(N);

    for (int k = 0; k < N; k++) {
        X[k] = 0;
        for (int n = 0; n < N; n++) {
            std::complex<double> exp_term =
                std::polar(1.0, -2 * M_PI * k * n / N);
            X[k] += x[n] * exp_term;
        }
    }

    return X;
}

/*
int main() {
    std::vector<std::complex<double>> input_signal =
        {1.0, 2.0, 3.0, 4.0, 9.0, 1.0, 20.0, 11.0};
    std::vector<std::complex<double>> result = DFT(input_signal);

    // Print the DFT result
    for (int k = 0; k < result.size(); k++) {
        std::cout << "X[" << k << "] = " << result[k] << std::endl;
    }

    return 0;
}*/
