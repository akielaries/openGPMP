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
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <numeric>
#include <openGPMP/disct/comb.hpp>
#include <string>
#include <vector>

// Function to calculate permutations (n P r)
int64_t gpmp::Comb::permutation(int n, int r) {
    if (n < r)
        return 0; // Invalid input
    int64_t result = 1;
    for (int i = 0; i < r; ++i) {
        result *= (n - i);
    }
    return result;
}

// Function to calculate combinations (n C r)
int64_t gpmp::Comb::combination(int n, int r) {
    if (n < r)
        return 0;           // Invalid input
    r = std::min(r, n - r); // Optimization to reduce calculations
    int64_t result = 1;
    for (int i = 0; i < r; ++i) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

// Function to calculate binomial coefficient (n choose r)
int64_t gpmp::Comb::binom_coeff(int n, int r) {
    if (n < r)
        return 0;           // Invalid input
    r = std::min(r, n - r); // Optimization to reduce calculations
    std::vector<int64_t> dp(r + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = std::min(i, r); j > 0; --j) {
            dp[j] = dp[j] + dp[j - 1];
        }
    }
    return dp[r];
}

// Function to calculate factorial (n!)
int64_t gpmp::Comb::factorial(int n) {
    if (n < 0)
        return 0; // Invalid input
    int64_t result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Function to generate all partitions of an integer n
std::vector<std::vector<int>> gpmp::Comb::partitions(int n) {
    std::vector<std::vector<int>> result;
    std::vector<int> partition;
    generatePartitions(n, n, partition, result);
    return result;
}

// Function to generate Bell numbers up to n
std::vector<int64_t> gpmp::Comb::bell_num(int n) {
    std::vector<int64_t> bell(n + 1, 0);
    bell[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            bell[i] += binom_coeff(i - 1, j) * bell[j];
        }
    }
    return bell;
}

// Function to calculate Stirling numbers of the second kind (S(n, k))
int64_t gpmp::Comb::stirling_num(int n, int k) {
    if (n < k)
        return 0;
    if (n == 0 && k == 0)
        return 1;
    if (k == 0 || k == n)
        return 1;
    return k * stirling_num(n - 1, k) + stirling_num(n - 1, k - 1);
}

// Function to generate Gray codes of length n
std::vector<int> gpmp::Comb::gray_code(int n) {
    std::vector<int> gray;
    for (int i = 0; i < (1 << n); ++i) {
        gray.push_back(i ^ (i >> 1));
    }
    return gray;
}

// Function to calculate the number of derangements (subfactorial)
int64_t gpmp::Comb::subfactorial(int n) {
    if (n == 0)
        return 1;
    if (n == 1)
        return 0;
    return (n - 1) * (subfactorial(n - 1) + subfactorial(n - 2));
}

// Function to calculate the number of increasing subsequences of length k in a
// permutation of length n
int64_t gpmp::Comb::subsequences(int n, int k) {
    if (k > n)
        return 0;
    std::vector<int64_t> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = i - 1; j >= 0; --j) {
            dp[i] += dp[j];
        }
    }
    int64_t result = 0;
    for (int i = n - k; i <= n; ++i) {
        result += dp[i];
    }
    return result;
}

// Function to generate all partitions of an integer n using distinct parts
std::vector<std::vector<int>> gpmp::Comb::partition_distinct(int n) {
    std::vector<std::vector<int>> result;
    std::vector<int> partition;
    gen_partition_distinct(n, n, partition, result);
    return result;
}

// Function to generate all compositions of an integer n (ordered partitions)
std::vector<std::vector<int>> gpmp::Comb::compositions(int n) {
    std::vector<std::vector<int>> result;
    std::vector<int> composition;
    gen_compositions(n, n, composition, result);
    return result;
}

// Function to calculate the number of Dyck words of length 2n
int64_t gpmp::Comb::dyck_words(int n) {
    return binom_coeff(2 * n, n) / (n + 1);
}

// Function to generate all Dyck words of length 2n
std::vector<std::string> gpmp::Comb::gen_dyck_words_until(int n) {
    std::vector<std::string> dyck_words;
    gen_dyck_words("", n, n, dyck_words);
    return dyck_words;
}

// Function to calculate the number of necklaces with n beads of k different
// colors
int64_t gpmp::Comb::necklaces(int n, int k) {
    if (n == 0)
        return 0;
    int64_t result = 0;
    for (int d : divisors(n)) {
        result += phi(n / d) * pow(k, d);
    }
    return result / n;
}

// Function to calculate Euler's totient function (phi)
int gpmp::Comb::phi(int n) {
    int result = n;
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0) {
                n /= p;
            }
            result -= result / p;
        }
    }
    if (n > 1) {
        result -= result / n;
    }
    return result;
}

// Function to generate all necklaces with n beads of k different colors
std::vector<std::vector<int>> gpmp::Comb::generateNecklaces(int n, int k) {
    std::vector<std::vector<int>> necklaces;
    std::vector<int> necklace(n, 0);
    gen_necklaces(necklace, 0, n, k, necklaces);
    return necklaces;
}

// Function to calculate the number of Lyndon words of length n
int64_t gpmp::Comb::lyndonWords(int n) {
    int64_t result = 0;
    for (int d : divisors(n)) {
        result += phi(n / d);
    }
    return result;
}

// Function to generate all Lyndon words of length n
std::vector<std::string> gpmp::Comb::generateLyndonWords(int n) {
    std::vector<std::string> lyndonWords;
    gen_lyndon_words("", n, n, lyndonWords);
    return lyndonWords;
}

// Helper function for generating partitions recursively
void gpmp::Comb::generatePartitions(int n,
                                    int max,
                                    std::vector<int> &partition,
                                    std::vector<std::vector<int>> &result) {
    if (n == 0) {
        result.push_back(partition);
        return;
    }

    for (int i = std::min(n, max); i >= 1; --i) {
        partition.push_back(i);
        generatePartitions(n - i, i, partition, result);
        partition.pop_back();
    }
}

// Helper function for generating partitions with distinct parts recursively
void gpmp::Comb::gen_partition_distinct(int n,
                                        int max,
                                        std::vector<int> &partition,
                                        std::vector<std::vector<int>> &result) {
    if (n == 0) {
        result.push_back(partition);
        return;
    }

    for (int i = std::min(n, max); i >= 1; --i) {
        if (std::find(partition.begin(), partition.end(), i) ==
            partition.end()) {
            partition.push_back(i);
            gen_partition_distinct(n - i, i, partition, result);
            partition.pop_back();
        }
    }
}

// Helper function for generating compositions recursively
void gpmp::Comb::gen_compositions(int n,
                                  int max,
                                  std::vector<int> &composition,
                                  std::vector<std::vector<int>> &result) {
    if (n == 0) {
        result.push_back(composition);
        return;
    }

    for (int i = std::min(n, max); i >= 1; --i) {
        composition.push_back(i);
        gen_compositions(n - i, i, composition, result);
        composition.pop_back();
    }
}

// Helper function for generating all Dyck words recursively
void gpmp::Comb::gen_dyck_words(std::string prefix,
                                int open,
                                int close,
                                std::vector<std::string> &dyck_words) {
    if (open == 0 && close == 0) {
        dyck_words.push_back(prefix);
        return;
    }
    if (open > 0) {
        gen_dyck_words(prefix + "(", open - 1, close, dyck_words);
    }
    if (close > open) {
        gen_dyck_words(prefix + ")", open, close - 1, dyck_words);
    }
}

// Helper function for generating all necklaces recursively
void gpmp::Comb::gen_necklaces(std::vector<int> &necklace,
                               int index,
                               int n,
                               int k,
                               std::vector<std::vector<int>> &necklaces) {
    if (index == n) {
        necklaces.push_back(necklace);
        return;
    }

    for (int color = 1; color <= k; ++color) {
        necklace[index] = color;
        gen_necklaces(necklace, index + 1, n, k, necklaces);
    }
}

// Helper function for generating all Lyndon words recursively
void gpmp::Comb::gen_lyndon_words(std::string prefix,
                                  int n,
                                  int max,
                                  std::vector<std::string> &lyndonWords) {
    if (static_cast<int>(prefix.size()) == n) {
        lyndonWords.push_back(prefix);
        return;
    }

    for (char c = (prefix.empty() ? 'a' : prefix.back() + 1); c <= 'z' && static_cast<int>(prefix.size()) < n; ++c) {
        if (n % (static_cast<int>(prefix.size()) + 1) == 0) {
            gen_lyndon_words(prefix + c, n, prefix.size() + 1, lyndonWords);
        } else {
            gen_lyndon_words(prefix + c, n, max, lyndonWords);
        }
    }

}

// Function to compute all divisors of a positive integer
std::vector<int> gpmp::Comb::divisors(int n) {
    std::vector<int> divs;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i != n / i) {
                divs.push_back(n / i);
            }
        }
    }
    return divs;
}
