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

#include <cstdint>
#include <string>
#include <vector>

namespace gpmp {

class Comb {
  public:
    int64_t permutation(int n, int r);

    int64_t combination(int n, int r);

    int64_t binom_coeff(int n, int r);

    int64_t factorial(int n);

    std::vector<std::vector<int>> partitions(int n);

    std::vector<int64_t> bell_num(int n);

    int64_t stirling_num(int n, int k);

    std::vector<int> gray_code(int n);

    int64_t subfactorial(int n);

    int64_t subsequences(int n, int k);

    std::vector<std::vector<int>> partition_distinct(int n);

    std::vector<std::vector<int>> compositions(int n);

    int64_t dyck_words(int n);

    std::vector<std::string> gen_dyck_words_until(int n);

    int64_t necklaces(int n, int k);

    int phi(int n);

    std::vector<std::vector<int>> generateNecklaces(int n, int k);

    int64_t lyndonWords(int n);

    std::vector<std::string> generateLyndonWords(int n);

    void generatePartitions(int n,
                            int max,
                            std::vector<int> &partition,
                            std::vector<std::vector<int>> &result);

    void gen_partition_distinct(int n,
                                int max,
                                std::vector<int> &partition,
                                std::vector<std::vector<int>> &result);

    void gen_compositions(int n,
                          int max,
                          std::vector<int> &composition,
                          std::vector<std::vector<int>> &result);

    void gen_dyck_words(std::string prefix,
                        int open,
                        int close,
                        std::vector<std::string> &dyck_words);

    void gen_necklaces(std::vector<int> &necklace,
                       int index,
                       int n,
                       int k,
                       std::vector<std::vector<int>> &necklaces);

    void gen_lyndon_words(std::string prefix,
                          int n,
                          int max,
                          std::vector<std::string> &lyndonWords);

    std::vector<int> divisors(int n);

    template <typename T>
    std::vector<std::vector<T>> permutations(const std::vector<T> &vec) {
        std::vector<std::vector<T>> result;
        std::vector<T> temp = vec;
        do {
            result.push_back(temp);
        } while (std::next_permutation(temp.begin(), temp.end()));
        return result;
    }

    template <typename T>
    std::vector<std::vector<T>> combinations(const std::vector<T> &vec, int r) {
        std::vector<std::vector<T>> result;
        std::vector<bool> bitmask(vec.size(), false);
        std::fill(bitmask.begin(), bitmask.begin() + r, true);
        do {
            std::vector<T> combination;
            for (int i = 0; i < vec.size(); ++i) {
                if (bitmask[i]) {
                    combination.push_back(vec[i]);
                }
            }
            result.push_back(combination);
        } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
        return result;
    }
};

} // namespace gpmp

#endif
