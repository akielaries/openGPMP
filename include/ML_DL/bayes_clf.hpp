/*
 * Naive Bayes Classifier
 */
#ifndef BAYES_CLF_HPP
#define BAYES_CLF_HPP
#include <vector>
#include <stdio.h>

typedef struct summary {
    std::vector<std::vector<float>> mean_stdev;
    float class_prob;
} summary;

class bayes_clf {
    private:
        std::vector<class_summary> Summary;
        std::vector<float> unique_label;

    public:
        void fit(std::vector<std::vector<float>> dataset);
        int predict(const  std::vector<float>& test_data);
};
summary compute_class_summ(std::vector<std::vector<float>> dataset, 
                            float class_label);

float prob_by_summ(const std::vector<float> &test_data, 
                const class_summary &summary );

#endif

