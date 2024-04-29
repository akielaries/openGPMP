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
 * LICENSE file.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/

#ifndef __COMB_HPP__
#define __COMB_HPP__

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

namespace gpmp {

/**
 * @class Comb
 * @brief A class providing various combinatorial functions and algorithms
 */
class Comb {
  public:
    /**
     * @brief Calculate the number of permutations (nPr)
     * @param n The total number of items
     * @param r The number of items to choose
     * @return The number of permutations
     */
    int64_t permutation(int n, int r);

    /**
     * @brief Calculate the number of combinations (nCr)
     * @param n The total number of items
     * @param r The number of items to choose
     * @return The number of combinations
     */
    int64_t combination(int n, int r);

    /**
     * @brief Calculate the binomial coefficient (n choose r)
     * @param n The total number of items
     * @param r The number of items to choose
     * @return The binomial coefficient
     */
    int64_t binom_coeff(int n, int r);

    /**
     * @brief Calculate the factorial of a number
     * @param n The number
     * @return The factorial of n
     */
    int64_t factorial(int n);

    /**
     * @brief Generate all partitions of a positive integer n
     * @param n The integer to partition
     * @return A vector of partitions
     */
    std::vector<std::vector<int>> partitions(int n);

    /**
     * @brief Calculate the Bell numbers
     * @param n The number of Bell numbers to calculate
     * @return A vector of Bell numbers
     */
    std::vector<int64_t> bell_num(int n);

    /**
     * @brief Calculate the Stirling number of the second kind
     * @param n The total number of items
     * @param k The number of non-empty subsets
     * @return The Stirling number
     */
    int64_t stirling_num(int n, int k);

    /**
     * @brief Generate the Gray code sequence of length n
     * @param n The number of bits in the sequence
     * @return A vector representing the Gray code
     */
    std::vector<int> gray_code(int n);

    /**
     * @brief Calculate the subfactorial (!n) or derangement of n
     * @param n The number
     * @return The subfactorial of n
     */
    int64_t subfactorial(int n);

    /**
     * @brief Calculate the number of subsequences of length k from n items
     * @param n The total number of items
     * @param k The length of subsequences
     * @return The number of subsequences
     */
    int64_t subsequences(int n, int k);

    /**
     * @brief Generate all distinct partitions of a positive integer n
     * @param n The integer to partition
     * @return A vector of distinct partitions
     */
    std::vector<std::vector<int>> partition_distinct(int n);

    /**
     * @brief Generate all compositions of a positive integer n
     * @param n The integer to compose
     * @return A vector of compositions
     */
    std::vector<std::vector<int>> compositions(int n);

    /**
     * @brief Calculate the number of Dyck words of length 2n
     * @param n The length parameter
     * @return The number of Dyck words
     */
    int64_t dyck_words(int n);

    /**
     * @brief Generate Dyck words up to length n
     * @param n The maximum length of Dyck words
     * @return A vector of Dyck words
     */
    std::vector<std::string> gen_dyck_words_until(int n);

    /**
     * @brief Calculate the number of necklaces of length n with k colors
     * @param n The length of the necklace
     * @param k The number of colors
     * @return The number of necklaces
     */
    int64_t necklaces(int n, int k);

    /**
     * @brief Calculate Euler's totient function (φ)
     * @param n The integer
     * @return The value of φ(n)
     */
    int phi(int n);

    /**
     * @brief Generate all necklaces of length n with k colors
     * @param n The length of the necklace
     * @param k The number of colors
     * @return A vector of necklaces
     */
    std::vector<std::vector<int>> generateNecklaces(int n, int k);

    /**
     * @brief Calculate the number of Lyndon words of length n
     * @param n The length of the Lyndon word
     * @return The number of Lyndon words
     */
    int64_t lyndonWords(int n);

    /**
     * @brief Generate all Lyndon words of length n
     * @param n The length of the Lyndon words
     * @return A vector of Lyndon words
     */
    std::vector<std::string> generateLyndonWords(int n);

    /**
     * @brief Generate partitions of a positive integer
     * @param n The integer to partition
     * @param max The maximum value in each partition
     * @param partition The current partition being generated
     * @param result The resulting vector of partitions
     */
    void generatePartitions(int n,
                            int max,
                            std::vector<int> &partition,
                            std::vector<std::vector<int>> &result);

    /**
     * @brief Generate distinct partitions of a positive integer
     * @param n The integer to partition
     * @param max The maximum value in each partition
     * @param partition The current partition being generated
     * @param result The resulting vector of partitions
     */
    void gen_partition_distinct(int n,
                                int max,
                                std::vector<int> &partition,
                                std::vector<std::vector<int>> &result);

    /**
     * @brief Generate compositions of a positive integer
     * @param n The integer to compose
     * @param max The maximum value in each composition
     * @param composition The current composition being generated
     * @param result The resulting vector of compositions
     */
    void gen_compositions(int n,
                          int max,
                          std::vector<int> &composition,
                          std::vector<std::vector<int>> &result);

    /**
     * @brief Generate Dyck words
     * @param prefix The current Dyck word prefix
     * @param open The number of open parentheses remaining
     * @param close The number of close parentheses remaining
     * @param dyck_words The resulting vector of Dyck words
     */
    void gen_dyck_words(std::string prefix,
                        int open,
                        int close,
                        std::vector<std::string> &dyck_words);

    /**
     * @brief Generate necklaces
     * @param necklace The current necklace being generated
     * @param index The current index in the necklace
     * @param n The length of the necklace
     * @param k The number of colors
     * @param necklaces The resulting vector of necklaces
     */
    void gen_necklaces(std::vector<int> &necklace,
                       int index,
                       int n,
                       int k,
                       std::vector<std::vector<int>> &necklaces);

    /**
     * @brief Generate Lyndon words
     * @param prefix The current Lyndon word prefix
     * @param n The length of the Lyndon words
     * @param max The maximum value in each Lyndon word
     * @param lyndonWords The resulting vector of Lyndon words
     */
    void gen_lyndon_words(std::string prefix,
                          int n,
                          int max,
                          std::vector<std::string> &lyndonWords);

    /**
     * @brief Calculate the divisors of a positive integer
     * @param n The integer
     * @return A vector of divisors
     */
    std::vector<int> divisors(int n);

    /**
     * @brief Generate all permutations of a vector
     * @tparam T The type of elements in the vector
     * @param vec The vector
     * @return A vector of all permutations
     */
    template <typename T>
    std::vector<std::vector<T>> permutations(const std::vector<T> &vec);

    /**
     * @brief Generate all combinations of a vector
     * @tparam T The type of elements in the vector
     * @param vec The vector
     * @param r The size of combinations
     * @return A vector of all combinations
     */
    template <typename T>
    std::vector<std::vector<T>> combinations(const std::vector<T> &vec, int r);
};

} // namespace gpmp

#endif
