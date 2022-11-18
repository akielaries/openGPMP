/* RM-pkg
 * TESTING BASIC LINEAR ALGEBRA OPERATIONS
 * test driver program on the implementations for some basic Linear Algebra
 * operations. 
 */
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cassert>
#include "../include/RM_lao.hpp"


template <typename V1, typename V2>
auto vsum(V1& v1, V2& v2) {
    printf("size of v1 = %d\nsize of v2 = %d\n", v1.size(), v2.size());
    //auto v1_iter = v1.begin();
    //auto v2_iter = v2.begin();
    int iter = 0;
    auto sum = 0;
    
    for (iter; iter < v1.size(); iter++) {
        auto sum = v1[iter] + v2[iter];
        std::cout << sum << std::endl;
    }
    std::cout << "before return" << sum << std::endl;
    return sum;

    //while (v1_iter != v1.end() ** v2_iter != v2.end()) {
    //}
}

int main() {
    // initialize class obj
    //la_operations la;
 
    //printf("BASIC LINEAR ALGEBRA OPERATIONS \n");

    // create vectors like arrays
    std::vector<int> v1 = {0, 7, 3, 4};
    std::vector<int> v2 = {1, 2, 0, 1};
    
    //auto result = vsum(v1, v2);
    //cout << vsum(v1, v2) << endl;
    
    int i = 0;
    int sum;
    //int j = 0;


    // iterate over vector 1
    for (i; i < v1.size(); i++) {
        int sum = v1[i] + v2[i];
        //printf("sum - %d\n", sum);
    }
    printf("sum %d\n", sum);

    return 0;

}

