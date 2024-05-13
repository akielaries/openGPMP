#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

int main() {
    // Define the matrix A
    MatrixXd A(3, 3);
    /*A << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;
    */
    A << 2.0, -1.0, 0.0,
        -1.0, 2.0, -1.0,
        0.0, -1.0, 2.0;

    // Initial guess for the eigenvector
    VectorXd v = VectorXd::Random(3);

    // Power iteration method
    int iterations = 1000; // Maximum number of iterations
    double tolerance = 1e-3; // Tolerance for convergence

    for (int i = 0; i < iterations; ++i) {
        VectorXd Av = A * v;
        double lambda = v.dot(Av) / v.dot(v); // Approximation of the dominant eigenvalue
        VectorXd v_new = Av / Av.norm(); // Normalized eigenvector

        if ((v_new - v).norm() < tolerance) {
            cout << "Dominant eigenvalue: " << lambda << endl;
            cout << "Eigenvector: \n" << v_new << endl;
            break; // Convergence achieved
        }

        v = v_new;
    }

    return 0;
}

