#include <iostream>
#include <openGPMP/stats/hypothesis.cpp>

int main() {
    // Example usage of the extended HypothesisTest class
    std::vector<double> sample1 = {25, 30, 28, 32, 35};
    std::vector<double> sample2 = {20, 22, 18, 24, 21};
    std::vector<std::vector<double>> samples = {{10, 12, 14},
                                                {15, 17, 19},
                                                {20, 22, 24}};
    std::vector<std::vector<int>> observed = {{10, 20, 30},
                                              {15, 25, 35},
                                              {25, 35, 45}};
    std::vector<std::vector<double>> expected = {{15, 25, 35},
                                                 {20, 30, 40},
                                                 {30, 40, 50}};

    std::cout << "One-sample t-test: "
              << gpmp::stats::HypothesisTest::one_sample_ttest(sample1, 30.0)
              << std::endl;
    std::cout << "Two-sample t-test: "
              << gpmp::stats::HypothesisTest::two_sample_ttest(sample1, sample2)
              << std::endl;
    std::cout << "ANOVA: " << gpmp::stats::HypothesisTest::ANOVA(samples)
              << std::endl;
    std::cout << "Chi-square test: "
              << gpmp::stats::HypothesisTest::chi_square_test(observed,
                                                              expected)
              << std::endl;
    std::cout << "Z-test for proportions: "
              << gpmp::stats::HypothesisTest::proportion_z_test(0.6,
                                                                0.4,
                                                                100,
                                                                100)
              << std::endl;
    std::cout << "Wilcoxon signed-rank test: "
              << gpmp::stats::HypothesisTest::wilcoxon_rank_test(sample1,
                                                                 sample2)
              << std::endl;
    std::cout << "Mann-Whitney U test: "
              << gpmp::stats::HypothesisTest::mann_whitney_test(sample1,
                                                                sample2)
              << std::endl;

    return 0;
}
