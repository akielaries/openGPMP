#include "matrix.hpp"

int main() {
    auto M = mtpk::mtx<float>::randn(2, 2); // init randn matrix

    M.print_shape();

}

