#include "../../include/ml/bayes_clf.hpp"
#include <iostream>
#include <string>
#include <vector>

int main() {
    // Example for BayesBernoulli class
    std::vector<std::vector<size_t>> bernoulli_train_data = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 1, 1},
        {0, 0, 1},
    };

    std::vector<std::string> bernoulli_labels = {"spam", "ham", "spam", "ham"};

    gpmp::ml::BayesBernoulli bernoulliClassifier(1.0);
    bernoulliClassifier.train(bernoulli_train_data, bernoulli_labels);

    std::vector<size_t> bernoulliNewData = {1, 0, 0};
    std::string bernoulliPrediction =
        bernoulliClassifier.predict(bernoulliNewData);

    std::cout << "Predicted Class (BayesBernoulli): " << bernoulliPrediction
              << "\n";

    // Print learned probabilities for BayesBernoulli
    bernoulliClassifier.display();

    // Example for BayesClf class
    std::vector<std::vector<double>> clf_train_data = {
        {1.0, 2.0, 3.0},
        {2.0, 3.0, 4.0},
        {3.0, 4.0, 5.0},
        {4.0, 5.0, 6.0},
    };

    std::vector<std::string> clf_labels = {"classA",
                                           "classB",
                                           "classA",
                                           "classB"};

    gpmp::ml::BayesClf clfClassifier(
        1.0,
        true,
        {0.4, 0.6}); // Example with predefined class priors
    clfClassifier.train(clf_train_data, clf_labels);

    std::vector<double> clfNewData = {2.0, 3.0, 4.0};
    std::string clfPrediction = clfClassifier.predict(clfNewData);

    std::cout << "Predicted Class (BayesClf): " << clfPrediction << "\n";

    // Print learned probabilities for BayesClf
    clfClassifier.display();

    return 0;
}
