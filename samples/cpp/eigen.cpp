#include <iostream>
#include <openGPMP/linalg/eigen.hpp>
#include <vector>

const double TOLERANCE = 1e-3;

int main () {
    std::vector<std::vector<double>> squareMat = {{2.0, -1.0, 0.0},
                                                  {-1.0, 2.0, -1.0},
                                                  {0.0, -1.0, 2.0}};
    gpmp::linalg::Eigen eigenSquare(squareMat);

    double eigenvalueSquare = eigenSquare.power_iter(1000, TOLERANCE);

    std::cout << "Eigenvalue square: " << eigenvalueSquare << std::endl;

}
