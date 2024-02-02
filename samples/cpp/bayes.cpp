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

    gpmp::ml::BayesBernoulli bernoulli_clf(1.0);
    bernoulli_clf.train(bernoulli_train_data, bernoulli_labels);

    std::vector<size_t> bernoulli_new_data = {1, 0, 0};
    std::string bernoulli_prediction =
        bernoulli_clf.predict(bernoulli_new_data);

    std::cout << "Predicted Class (BayesBernoulli): " << bernoulli_prediction
              << "\n";

    // print learned probabilities for BayesBernoulli
    bernoulli_clf.display();

    // example for BayesClf class
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
    // example with predefined class priors
    gpmp::ml::BayesClf bayes_clf(1.0, true, {0.4, 0.6});
    bayes_clf.train(clf_train_data, clf_labels);

    std::vector<double> bayes_clf_new_data = {2.0, 3.0, 4.0};
    std::string bayes_clf_prediction = bayes_clf.predict(bayes_clf_new_data);

    std::cout << "Predicted Class (BayesClf): " << bayes_clf_prediction << "\n";

    // print learned probabilities for BayesClf
    bayes_clf.display();

    // example for BayesGauss class
    std::vector<std::vector<double>> gauss_train_data = {
        {1.2, 2.3, 3.5},
        {2.5, 3.8, 4.0},
        {3.0, 4.2, 5.2},
        {4.1, 5.3, 6.7},
    };

    std::vector<std::string> gauss_labels = {"classX",
                                             "classY",
                                             "classX",
                                             "classY"};

    gpmp::ml::BayesGauss gauss_clf;
    gauss_clf.train(gauss_train_data, gauss_labels);

    std::vector<double> gauss_new_data = {2.3, 3.7, 4.5};
    std::string gauss_prediction = gauss_clf.predict(gauss_new_data);

    std::cout << "Predicted Class (BayesGauss): " << gauss_prediction << "\n";

    // print learned probabilities for BayesGauss
    gauss_clf.display();

    // example for BayesMultiNom class
    std::vector<std::vector<size_t>> multinom_train_data = {
        {1, 2, 3},
        {2, 3, 4},
        {3, 4, 5},
        {4, 5, 6},
    };

    std::vector<std::string> multinom_labels = {"classA",
                                                "classB",
                                                "classA",
                                                "classB"};

    gpmp::ml::BayesMultiNom multinom_clf(1.0, true, {0.4, 0.6});
    multinom_clf.train(multinom_train_data, multinom_labels);

    std::vector<size_t> multinom_new_data = {2, 3, 4};
    std::string multinom_prediction = multinom_clf.predict(multinom_new_data);

    std::cout << "Predicted Class (BayesMultiNom): " << multinom_prediction
              << "\n";

    // print learned probabilities for BayesMultiNom
    multinom_clf.display();

    return 0;
}
