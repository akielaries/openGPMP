/**
 * @file
 *
 * @brief openMTPK LINEAR ALGEBRA MODULE 
 * 
 * @details This file serves as the core header for the Linear Algebra
 * module. This header includes the following :
 *  - Matrix
 *  - Vectors
 *  - Scalars
 *  - Linear Functions & Equations
 *      * Taylor Approximation
 *      * Naive Regression
 *      * Systems
 *  - Linear Dynamical Systems
 *      * Population Dynamics
 *      * Epidemic Dynamics
 *      * Motion
 *      * Supply Chain Dynamics
 *  - Norm & Distance
 *      * STD Dev
 *      * Angle
 *      * Complexity
 *  - Clustering
 *  - Linear Independence 
 *      * Orthonormal Vectors
 *      * Gram-Schmidt Algorithm
 *  
 *  - Least Squares
 *      * Data Fitting
 *      * Classification
 *      * Multi-Objective
 *      * Contrained
 *      * Nonlinear
 *
 *  @note Some topics in Linear Algebra overlap and/or heavily influence 
 *  algorithms seen in Machine Learning
 */
#ifndef LINALG_HPP
#define LINALG_HPP

/**
 * @brief \b Matrix \b Operations
 * @details Encompasses Matrix and Scalar operations
 */
#define MATRIX
#include "linalg/matrix.hpp"
/*****************************************************************************/

/**
 * @brief \b Vector \b Operations
 * @details Encompasses Vector and Scalar operations
 */
#define MATRIX
#include "linalg/vectors.hpp"
/*****************************************************************************/

#endif
