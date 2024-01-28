#include "../../include/ml/bayes_clf.hpp"
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::vector<size_t>> train_data = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 1, 1},
        {0, 0, 1},
    };

    std::vector<std::string> labels = {"spam", "ham", "spam", "ham"};

    gpmp::ml::BayesBernoulli classifier(1.0);
    classifier.train(train_data, labels);

    std::vector<size_t> newData = {1, 0, 0};
    std::string prediction = classifier.predict(newData);

    std::cout << "Predicted Class: " << prediction << "\n";

    // Print learned probabilities
    classifier.display();

    return 0;
}
