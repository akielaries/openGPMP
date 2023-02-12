/**
 * @ file
 *
 * Definitions for methods involed in creating Tensors
 *
 */

#ifndef TENSORS_HPP
#define TENSORS_HPP

#include <cmath>
#include <vector>

namespace mtpk {

/**
 * @class Vectors
 * @brief Operations related to Vectors and Scalars
 */
class Tensors {
    public:
    std::vector<std::vector<double>>
        tensor_vec_mult(std::vector<std::vector<std::vector<double>>> A,
                        std::vector<double>                           b);

    void printTensor(std::vector<std::vector<std::vector<double>>> A);
    std::vector<std::vector<std::vector<double>>>
        vector_wise_tensor_product(
            std::vector<std::vector<std::vector<double>>> A,
            std::vector<std::vector<double>>              B);
};

} // namespace mtpk

#endif
