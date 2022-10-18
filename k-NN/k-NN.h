/*
 * header for cross-validation + k-fold cross-validation implementations
 * in C++
 */


#ifndef KFOLDCV_H
#define KFOLDCV_H
#include <vector>
#include <random>

using namespace std;

bool comparison(Company& lhs, Company& rhs); 

double euclideanDistance(Company& lhs, Company& test);

double manhattanDistance(Company& lhs, Company& test);

void fillDistances(vector<Company>& data, Company& test, 
        double(*distanceFunction)(Company&, Company&));

bool KNN(vector<Company>& data, Company& test, int k, 
        double(*distanceFunction)(Company&, Company&));


#endif
