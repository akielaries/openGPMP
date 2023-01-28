/**
 * @file
 *
 * @brief Miscellaneous utilities methods related to openMTPK
 *
 */
#ifndef UTILS_HPP
#define UTILS_HPP

namespace mtpk {
// exponentiate

// square root

// cube root

/**
 * @class
 * @brief Finds outliers in models
 */

class OutlierFinder {
  public:
    // Cnstr
    OutlierFinder(int threshold);

    std::vector<std::vector<double>>
        modelSetTest(std::vector<std::vector<double>> inputSet);
    std::vector<double> modelTest(std::vector<double> inputSet);

    // Variables required
    int threshold;
};

} // namespace mtpk

#endif
