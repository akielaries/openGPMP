/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openGPMP/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/

#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <iostream>
#include <vector>

namespace gpmp {

namespace linalg {

/**
 * @class Tensor
 * @brief Represents a 3D tensor with basic operations
 *
 * This class provides basic operations for a 3D tensor, including addition,
 * multiplication, element access, and display functionality
 */
class Tensor {
  public:
    /**
     * @brief Default constructor Creates an empty tensor
     */
    Tensor();

    /**
     * @brief Constructor with specified dimensions
     * @param dimensions A vector containing three dimensions for the tensor
     * @throw std::invalid_argument if dimensions are empty
     *
     * Constructs a tensor with specified dimensions and initializes the data
     */
    explicit Tensor(const std::vector<size_t> &dimensions);

    /**
     * @brief Constructor with initial data
     * @param data 3D vector representing the initial data for the tensor
     * @throw std::invalid_argument if data is empty
     *
     * Constructs a tensor with the given initial data and sets dimensions
     * accordingly
     */
    Tensor(const std::vector<std::vector<std::vector<double>>> &data);

    /**
     * @brief Adds another tensor to the current tensor
     * @param other Tensor to be added
     * @return A new tensor representing the sum
     * @throw std::invalid_argument if dimensions do not match
     */
    Tensor add(const Tensor &other) const;

    /**
     * @brief Multiplies the tensor by a scalar value
     * @param scalar The scalar value
     * @return A new tensor representing the product
     */
    Tensor multiply(double scalar) const;

    /**
     * @brief Multiplies the tensor by another tensor
     * @param other Tensor to be multiplied
     * @return A new tensor representing the product
     * @throw std::invalid_argument if dimensions do not match
     */
    Tensor multiply(const Tensor &other) const;

    /**
     * @brief Gets the value at the specified indices
     * @param indices Vector containing three indices
     * @return The value at the specified indices
     * @throw std::out_of_range if the number of indices is not 3 or if an index
     * is out of bounds
     */
    double get(const std::vector<size_t> &indices) const;

    /**
     * @brief Sets the value at the specified indices
     * @param indices Vector containing three indices
     * @param value The value to set
     * @throw std::out_of_range if the number of indices is not 3 or if an index
     * is out of bounds
     */
    void set(const std::vector<size_t> &indices, double value);

    /**
     * @brief Displays the tensor
     */
    void display() const;

  private:
    ///< 3D vector representing the tensor data
    std::vector<std::vector<std::vector<double>>> data_;
    ///< Array representing the dimensions of the tensor
    size_t dimensions_[3];
};

} // namespace linalg
} // namespace gpmp

#endif
