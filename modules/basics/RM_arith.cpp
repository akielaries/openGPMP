/* RM-pkg
 * BASIC ARITHMETIC OPERATIONS + - ÷ ×
 * taking a look at different mathematical operations seen in Linear
 * Algebra in C++
 */
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "../../include/RM_arith.hpp"


/*
 * Constructor to provide the default values to all the terms in the object 
 * of class la_ops
 */
//template<typename T>
//arith<T>::arith(){}

template<typename T>
inline T rm_sum(T t) {
    return t;
}

template<typename T, typename... Ts>
inline auto rm_sum(T t, Ts... ts) {
    return t+rm_sum(ts...);
}

