/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openGPMP/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/
#include <algorithm>
#include <cmath>
#include <openGPMP/stats/describe.hpp>
#include <vector>

double gpmp::stats::Describe::u_stat(const std::vector<double> &sample1,
                                     const std::vector<double> &sample2) {
    double U = 0;
    for (double x1 : sample1) {
        for (double x2 : sample2) {
            if (x1 < x2) {
                U++;
            }
        }
    }
    return U;
}

// Arithmetic Mean
double gpmp::stats::Describe::mean_arith(const std::vector<double> &data) {
    double sum = 0.0;
    for (const auto &value : data) {
        sum += value;
    }
    return sum / static_cast<double>(data.size());
}

// Geometric Mean
double gpmp::stats::Describe::mean_geo(const std::vector<double> &data) {
    double product = 1.0;
    for (const auto &value : data) {
        product *= value;
    }
    return std::pow(product, 1.0 / static_cast<double>(data.size()));
}

// Cubic Generalized Mean
double gpmp::stats::Describe::mean_cubic(const std::vector<double> &data,
                                         double p) {
    double sum = 0.0;
    for (const auto &value : data) {
        sum += std::pow(value, p);
    }
    return std::pow(sum / static_cast<double>(data.size()), 1.0 / p);
}

// Power Geometric Mean
double gpmp::stats::Describe::mean_geo_pow(const std::vector<double> &data,
                                           double p) {
    double product = 1.0;
    for (const auto &value : data) {
        product *= std::pow(value, p);
    }
    return std::pow(product, 1.0 / static_cast<double>(data.size()));
}

// Harmonic Mean
double gpmp::stats::Describe::mean_harmonic(const std::vector<double> &data) {
    double sum = 0.0;
    for (const auto &value : data) {
        sum += 1.0 / value;
    }
    return static_cast<double>(data.size()) / sum;
}

// Heronian Mean
double gpmp::stats::Describe::mean_heronian(const std::vector<double> &data) {
    double product = 1.0;
    for (const auto &value : data) {
        product *= std::sqrt(value);
    }
    return std::pow(product, 2.0 / static_cast<double>(data.size()));
}

// Heinz Mean
double gpmp::stats::Describe::mean_heinz(const std::vector<double> &data) {
    double sum = 0.0;
    for (const auto &value : data) {
        sum += value * std::log(value);
    }
    return std::exp(sum / static_cast<double>(data.size()));
}

// Lehmer Mean
double gpmp::stats::Describe::mean_lehmer(const std::vector<double> &data,
                                          double p) {
    double sum = 0.0;
    for (const auto &value : data) {
        sum += std::pow(value, p);
    }
    return sum / static_cast<double>(data.size());
}

// Median
double gpmp::stats::Describe::Median(std::vector<double> data) {
    std::sort(data.begin(), data.end());
    size_t size = data.size();
    if (size % 2 == 0) {
        return (data[size / 2 - 1] + data[size / 2]) / 2.0;
    } else {
        return data[size / 2];
    }
}

// Average Absolute Deviation
double gpmp::stats::Describe::avg_abs_dev(const std::vector<double> &data) {
    double mean = mean_arith(data);
    double sum = 0.0;
    for (const auto &value : data) {
        sum += std::abs(value - mean);
    }
    return sum / static_cast<double>(data.size());
}

// Coefficient of Variation
double gpmp::stats::Describe::var_coeff(const std::vector<double> &data) {
    double mean = mean_arith(data);
    double stddev = stdev(data, mean);
    return (stddev / mean) * 100.0; // Multiply by 100 for percentage
}

// Interquartile Range
double gpmp::stats::Describe::iq_range(const std::vector<double> &data) {
    std::vector<double> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());

    size_t size = sortedData.size();
    size_t lowerIndex = size / 4;
    size_t upperIndex = 3 * size / 4;

    return sortedData[upperIndex] - sortedData[lowerIndex];
}

// percentile
double gpmp::stats::Describe::percentile(const std::vector<double> &data,
                                         double percentile) {
    std::vector<double> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());

    size_t size = sortedData.size();
    size_t index = static_cast<size_t>(percentile * (size - 1));
    return sortedData[index];
}

// Range
double gpmp::stats::Describe::range(const std::vector<double> &data) {
    auto result = std::minmax_element(data.begin(), data.end());
    return *result.second - *result.first;
}

// Standard Deviation
double gpmp::stats::Describe::stdev(const std::vector<double> &data,
                                    double mean) {
    double sum = 0.0;
    for (const auto &value : data) {
        sum += std::pow(value - mean, 2.0);
    }
    return std::sqrt(sum / static_cast<double>(data.size()));
}

// variance
double gpmp::stats::Describe::variance(const std::vector<double> &data,
                                       double mean) {
    double sum = 0.0;
    for (const auto &value : data) {
        sum += std::pow(value - mean, 2.0);
    }
    return sum / static_cast<double>(data.size());
}

// central limit theorem
double gpmp::stats::Describe::clt(const std::vector<double> &data,
                                  int numSamples) {
    double mean = mean_arith(data);
    double stddev = stdev(data, mean);
    return stddev / std::sqrt(static_cast<double>(numSamples));
}

// Kurtosis
double gpmp::stats::Describe::kurtosis(const std::vector<double> &data,
                                       double mean) {
    double sum = 0.0;
    for (const auto &value : data) {
        sum += std::pow(value - mean, 4.0);
    }
    double var = variance(data, mean);
    return sum / (data.size() * std::pow(var, 2.0)) - 3.0;
}

// l-moments (first two)
double gpmp::stats::Describe::lmoment1(const std::vector<double> &data,
                                       double mean) {
    double sum = 0.0;
    for (const auto &value : data) {
        sum += std::pow(value - mean, 3.0);
    }
    return sum / data.size();
}

double gpmp::stats::Describe::lmoment2(const std::vector<double> &data,
                                       double mean) {
    double sum = 0.0;
    for (const auto &value : data) {
        sum += std::pow(value - mean, 4.0);
    }
    return sum / data.size();
}

// skewness
double gpmp::stats::Describe::skewness(const std::vector<double> &data,
                                       double mean,
                                       double stddev) {
    double sum = 0.0;
    for (const auto &value : data) {
        sum += std::pow((value - mean) / stddev, 3.0);
    }
    return sum / static_cast<double>(data.size());
}

std::vector<size_t>
gpmp::stats::Describe::rank_data(const std::vector<double> &data) {
    std::vector<size_t> ranks(data.size());

    for (size_t i = 0; i < data.size(); ++i) {
        size_t rank = 1;
        for (size_t j = 0; j < data.size(); ++j) {
            if (j != i && data[j] < data[i]) {
                rank++;
            }
        }
        ranks[i] = rank;
    }

    return ranks;
}

double gpmp::stats::Describe::partial_corr(const std::vector<double> &x,
                                           const std::vector<double> &y,
                                           const std::vector<double> &z) {
    double r_xy = ppmc(x, y);
    double r_xz = ppmc(x, z);
    double r_yz = ppmc(y, z);

    return (r_xy - (r_xz * r_yz)) /
           std::sqrt((1.0 - std::pow(r_xz, 2.0)) * (1.0 - std::pow(r_yz, 2.0)));
}

// Pearson Product-Moment Correlation
double gpmp::stats::Describe::ppmc(const std::vector<double> &x,
                                   const std::vector<double> &y) {
    double mean_x = mean_arith(x);
    double mean_y = mean_arith(y);

    double numerator = 0.0;
    double denominator_x = 0.0;
    double denominator_y = 0.0;

    for (size_t i = 0; i < x.size(); ++i) {
        numerator += (x[i] - mean_x) * (y[i] - mean_y);
        denominator_x += std::pow(x[i] - mean_x, 2.0);
        denominator_y += std::pow(y[i] - mean_y, 2.0);
    }

    return numerator / std::sqrt(denominator_x * denominator_y);
}

// Kendall's Tau Rank Correlation
double gpmp::stats::Describe::kendalls_tau(const std::vector<double> &x,
                                           const std::vector<double> &y) {
    size_t concordant = 0;
    size_t discordant = 0;

    for (size_t i = 0; i < x.size() - 1; ++i) {
        for (size_t j = i + 1; j < x.size(); ++j) {
            if ((x[i] < x[j] && y[i] < y[j]) || (x[i] > x[j] && y[i] > y[j])) {
                concordant++;
            } else if ((x[i] < x[j] && y[i] > y[j]) ||
                       (x[i] > x[j] && y[i] < y[j])) {
                discordant++;
            }
        }
    }

    return static_cast<double>(concordant - discordant) /
           std::sqrt(static_cast<double>((concordant + discordant) *
                                         (x.size() * (x.size() - 1)) / 2));
}

// Spearman's Rank Correlation
double gpmp::stats::Describe::spearmans_rho(const std::vector<double> &x,
                                            const std::vector<double> &y) {
    std::vector<size_t> ranks_x = rank_data(x);
    std::vector<size_t> ranks_y = rank_data(y);

    double d_squared = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        d_squared += std::pow(ranks_x[i] - ranks_y[i], 2.0);
    }

    return 1.0 -
           (6.0 * d_squared) / (x.size() * (std::pow(x.size(), 2.0) - 1.0));
}
