/*
 * header for cross-validation + k-fold cross-validation
 * implementations in C++
 */

#ifndef KFOLDCV_H
#define KFOLDCV_H
#include <random>
#include <vector>

using namespace std;

namespace mtpk {

class NearestNeighbor {
    public:
    bool comparison(Company &lhs, Company &rhs);

    long double euclideanDistance(Company &lhs, Company &test);

    long double manhattanDistance(Company &lhs, Company &test);

    void fillDistances(vector<Company> &data, Company &test,
                       long double (*distanceFunction)(Company &,
                                                       Company &));

    bool KNN(vector<Company> &data, Company &test, int64_t k,
             long double (*distanceFunction)(Company &, Company &));
};

} // namespace mtpk

#endif
