#include <cstdint>
#include <iostream>
#include <openGPMP/disct/comb.hpp>
#include <vector>

int main() {
    gpmp::Comb comb_obj;
    int n = 5;
    int r = 3;
    std::cout << "Permutations: " << comb_obj.permutation(n, r) << std::endl;
    std::cout << "Combinations: " << comb_obj.combination(n, r) << std::endl;
    std::cout << "Binomial Coefficient: " << comb_obj.binom_coeff(n, r)
              << std::endl;
    std::cout << "Factorial: " << comb_obj.factorial(n) << std::endl;

    std::vector<int> vec = {1, 2, 3};
    std::vector<std::vector<int>> perms = comb_obj.permutations(vec);
    std::cout << "Permutations of {1, 2, 3}:" << std::endl;
    for (const auto &perm : perms) {
        for (int x : perm) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }

    std::vector<std::vector<int>> combs = comb_obj.combinations(vec, r);
    std::cout << "Combinations of size " << r
              << " from {1, 2, 3}:" << std::endl;
    for (const auto &comb : combs) {
        for (int x : comb) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Partitions of " << n << ":" << std::endl;
    std::vector<std::vector<int>> partitions = comb_obj.partitions(n);
    for (const auto &partition : partitions) {
        for (int x : partition) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Bell numbers up to " << n << ":" << std::endl;
    std::vector<int64_t> bell = comb_obj.bell_num(n);
    for (int i = 0; i <= n; ++i) {
        std::cout << "B(" << i << ") = " << bell[i] << std::endl;
    }

    std::cout << "Stirling numbers of the second kind (S(5, 3)): "
              << comb_obj.stirling_num(5, 3) << std::endl;

    std::cout << "Gray code of length 3:" << std::endl;
    std::vector<int> gray = comb_obj.gray_code(3);
    for (int x : gray) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::cout << "Number of derangements for n=5: " << comb_obj.subfactorial(5)
              << std::endl;

    std::cout << "Number of increasing subsequences of length 2 in a "
                 "permutation of length 5: "
              << comb_obj.subsequences(5, 2) << std::endl;

    std::cout << "Partitions of " << n << " using distinct parts:" << std::endl;
    std::vector<std::vector<int>> partition_distinct =
        comb_obj.partition_distinct(n);
    for (const auto &partition : partition_distinct) {
        for (int x : partition) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Compositions of " << n << ":" << std::endl;
    std::vector<std::vector<int>> compositions = comb_obj.compositions(n);
    for (const auto &composition : compositions) {
        for (int x : composition) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Number of Dyck words of length 10: " << comb_obj.dyck_words(5)
              << std::endl;

    std::cout << "Dyck words of length 2 * 3:" << std::endl;
    std::vector<std::string> dyck_words = comb_obj.gen_dyck_words_until(3);
    for (const auto &word : dyck_words) {
        std::cout << word << std::endl;
    }

    std::cout << "Number of necklaces with 4 beads of 2 different colors: "
              << comb_obj.necklaces(4, 2) << std::endl;

    std::cout << "Necklaces with 4 beads of 2 different colors:" << std::endl;
    std::vector<std::vector<int>> necklaces = comb_obj.generateNecklaces(4, 2);
    for (const auto &necklace : necklaces) {
        for (int color : necklace) {
            std::cout << color << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Number of Lyndon words of length 3: "
              << comb_obj.lyndonWords(3) << std::endl;

    std::cout << "Lyndon words of length 3:" << std::endl;
    std::vector<std::string> lyndonWords = comb_obj.generateLyndonWords(3);
    for (const auto &word : lyndonWords) {
        std::cout << word << std::endl;
    }

    return 0;
}
