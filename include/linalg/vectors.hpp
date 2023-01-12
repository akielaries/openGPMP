/**
 * @ file
 *
 * Definitions for Matrix, Scalar, Vector, and other Linear Alebra
 * related operations
 */

#ifndef VECTORS_HPP 
#define VECTORS_HPP

#include <vector>
#include <cmath>


namespace mtpk {

/**
 * @class Vectors
 * @brief Operations related to Vectors and Scalars
 */
class Vectors {
    std::vector<int64_t> x;
    std::vector<int64_t> y;


    public:
        /*
         * vectors of the same dimension size are just scalars as they only 
         * contain magnitude. vectors contain both magnitude + direction
         */
        // function to add two 1D vectors
        // template <typename T>
        //float scalar_add();
        // function to subtract two 1D vectors
        //float scalar_sub();
        // function to multiply two 1D vectors
        //float scalar_mult();
        int64_t add(int64_t a, int64_t b);
};

} // namespace

#endif

