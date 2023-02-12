#include <cassert>
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

template <typename LHS, typename RHS>
auto vsum(LHS &lhs, RHS const &rhs) {
    assert(lhs.size() == rhs.size());
    auto lhs_iter = lhs.begin();
    auto rhs_iter = rhs.cbegin();
    while (lhs_iter != lhs.end() && rhs_iter != rhs.cend()) {
        *lhs_iter += *rhs_iter;
        ++lhs_iter;
        ++rhs_iter;
    }
    return lhs_iter;
}

template <std::size_t DIM, typename T>
void project(std::vector<T> &vec) {
    vec.resize(DIM, T(0));
}

int main() {
    std::vector<double> lhs = {1.0, 2.2, 1};
    std::vector<int> rhs    = {1, 3, 2};

    auto sum = vsum(lhs, rhs);

    cout << typeid(sum).name() << endl;

    constexpr int k_physical_dim = 3;
    std::vector<double> data_vec{3.4, 5.6};
    project<k_physical_dim>(data_vec);

    return 0;
}
