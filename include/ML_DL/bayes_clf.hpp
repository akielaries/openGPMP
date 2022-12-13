/*
 * Naive Bayes Classifier
 */
#ifndef BAYES_CLF_HPP
#define BAYES_CLF_HPP
#include <vector>
#include <stdio.h>

typedef struct class_summ {
    std::vector<std::vector<float>> mean_stdev;
    float class_prob;
} class_sum;

class bayes_clf {
    private:
        std::vector<class_summ> Summary;
        std::vector<float> unique_label;

    public:
        void fit(std::vector<std::vector<float>> dataset);
        int predict(const  std::vector<float>& test_data);
};
class_summ compute_class_summ(std::vector<std::vector<float>> dataset, 
                            float class_label);

float prob_by_summ(const std::vector<float> &test_data, 
                const class_summary &summary );

#endif

