/**
 * @file
 *
 * Definitions for the Naive Bayes Classifier
 */
#ifndef BAYES_CLF_HPP
#define BAYES_CLF_HPP
#include <vector>
#include <stdio.h>


namespace mtpk {

/**
 * @brief Summary data structure responsible for returning results
 */
typedef struct summary {
    std::vector<std::vector<long double>> mean_stdev;
    long double class_prob;
} summary;

/**
 * @brief Bayes Classifier Class based on assumptions of independence
 */
class BayesClf {
    private:
        std::vector<class_summary> Summary;
        std::vector<long double> unique_label;

    public:
        void fit(std::vector<std::vector<long double>> dataset);
        int64_t predict(const std::vector<long double>& test_data);
};
summary compute_class_summ(std::vector<std::vector<long double>> dataset, 
                            long double class_label);

long double prob_by_summ(const std::vector<long double> &test_data, 
                const class_summary &summary );

} // namespace

#endif

