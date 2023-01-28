#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <vector>

namespace mtpk {
class Stats {
  public:
    // These functions are for univariate lin reg module- not for
    // users.
    double b0Estimation(const std::vector<double> &x,
                        const std::vector<double> &y);
    double b1Estimation(const std::vector<double> &x,
                        const std::vector<double> &y);
    // Statistical Functions
    double mean(const std::vector<double> &x);
    double median(std::vector<double> x);
    std::vector<double> mode(const std::vector<double> &x);
    double range(const std::vector<double> &x);
    double midrange(const std::vector<double> &x);
    double absAvgDeviation(const std::vector<double> &x);
    double standardDeviation(const std::vector<double> &x);
    double variance(const std::vector<double> &x);
    double covariance(const std::vector<double> &x,
                      const std::vector<double> &y);
    double correlation(const std::vector<double> &x,
                       const std::vector<double> &y);
    double R2(const std::vector<double> &x, const std::vector<double> &y);
    double chebyshevIneq(const double k);
    double weightedMean(const std::vector<double> &x,
                        const std::vector<double> &weights);
    double geometricMean(const std::vector<double> &x);
    double harmonicMean(const std::vector<double> &x);
    double RMS(const std::vector<double> &x);
    double powerMean(const std::vector<double> &x, const double p);
    double lehmerMean(const std::vector<double> &x, const double p);
    double weightedLehmerMean(const std::vector<double> &x,
                              const std::vector<double> &weights,
                              const double p);
    double contraHarmonicMean(const std::vector<double> &x);
    double heronianMean(const double A, const double B);
    double heinzMean(const double A, const double B, const double x);
    double neumanSandorMean(const double a, const double b);
    double stolarskyMean(const double x, const double y, const double p);
    double identricMean(const double x, const double y);
    double logMean(const double x, const double y);

    // hypothesis test
    std::tuple<bool, double> chiSquareTest(std::vector<double> observed, std::vector<double> expected);
};
} // namespace mtpk

#endif
