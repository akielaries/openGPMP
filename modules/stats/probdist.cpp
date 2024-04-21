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
#include <limits>
#include <math.h>
#include <numeric>
#include <openGPMP/stats/describe.hpp>
#include <openGPMP/stats/probdist.hpp>
#include <random>
#include <vector>

float my_logf(float);

/* compute inverse error functions with maximum error of 2.35793 ulp */
float erfinv(float a) {
    float p, r, t;
    t = fmaf(a, 0.0f - a, 1.0f);
    t = my_logf(t);
    if (fabsf(t) > 6.125f) {             // maximum ulp error = 2.35793
        p = 3.03697567e-10f;             //  0x1.4deb44p-32
        p = fmaf(p, t, 2.93243101e-8f);  //  0x1.f7c9aep-26
        p = fmaf(p, t, 1.22150334e-6f);  //  0x1.47e512p-20
        p = fmaf(p, t, 2.84108955e-5f);  //  0x1.dca7dep-16
        p = fmaf(p, t, 3.93552968e-4f);  //  0x1.9cab92p-12
        p = fmaf(p, t, 3.02698812e-3f);  //  0x1.8cc0dep-9
        p = fmaf(p, t, 4.83185798e-3f);  //  0x1.3ca920p-8
        p = fmaf(p, t, -2.64646143e-1f); // -0x1.0eff66p-2
        p = fmaf(p, t, 8.40016484e-1f);  //  0x1.ae16a4p-1
    } else {                             // maximum ulp error = 2.35002
        p = 5.43877832e-9f;              //  0x1.75c000p-28
        p = fmaf(p, t, 1.43285448e-7f);  //  0x1.33b402p-23
        p = fmaf(p, t, 1.22774793e-6f);  //  0x1.499232p-20
        p = fmaf(p, t, 1.12963626e-7f);  //  0x1.e52cd2p-24
        p = fmaf(p, t, -5.61530760e-5f); // -0x1.d70bd0p-15
        p = fmaf(p, t, -1.47697632e-4f); // -0x1.35be90p-13
        p = fmaf(p, t, 2.31468678e-3f);  //  0x1.2f6400p-9
        p = fmaf(p, t, 1.15392581e-2f);  //  0x1.7a1e50p-7
        p = fmaf(p, t, -2.32015476e-1f); // -0x1.db2aeep-3
        p = fmaf(p, t, 8.86226892e-1f);  //  0x1.c5bf88p-1
    }
    r = a * p;
    return r;
}

/* compute natural logarithm with a maximum error of 0.85089 ulp */
float my_logf(float a) {
    float i, m, r, s, t;
    int e;

    m = frexpf(a, &e);
    if (m < 0.666666667f) { // 0x1.555556p-1
        m = m + m;
        e = e - 1;
    }
    i = (float)e;
    /* m in [2/3, 4/3] */
    m = m - 1.0f;
    s = m * m;
    /* Compute log1p(m) for m in [-1/3, 1/3] */
    r = -0.130310059f;             // -0x1.0ae000p-3
    t = 0.140869141f;              //  0x1.208000p-3
    r = fmaf(r, s, -0.121484190f); // -0x1.f19968p-4
    t = fmaf(t, s, 0.139814854f);  //  0x1.1e5740p-3
    r = fmaf(r, s, -0.166846052f); // -0x1.55b362p-3
    t = fmaf(t, s, 0.200120345f);  //  0x1.99d8b2p-3
    r = fmaf(r, s, -0.249996200f); // -0x1.fffe02p-3
    r = fmaf(t, m, r);
    r = fmaf(r, m, 0.333331972f);  //  0x1.5554fap-2
    r = fmaf(r, m, -0.500000000f); // -0x1.000000p-1
    r = fmaf(r, s, m);
    r = fmaf(i, 0.693147182f, r);                  //  0x1.62e430p-1 // log(2)
    if (!((a > 0.0f) && (a <= 3.40282346e+38f))) { // 0x1.fffffep+127
        r = a + a;                                 // silence NaNs if necessary
        if (a < 0.0f)
            r = (0.0f / 0.0f); //  NaN
        // if (a == 0.0f)
        if (fabs(a - 0.0f) < std::numeric_limits<double>::epsilon()) {
            r = (-1.0f / 0.0f); // -Inf
        }
    }
    return r;
}

double gpmp::stats::ProbDist::quantile_dist(double probability) {
    if (probability <= 0.0 || probability >= 1.0) {
        return 0.0; // Invalid input, return 0
    }

    // Using erfinv for older C++ standards
    double z = std::sqrt(2.0) * erfinv(2.0 * probability - 1.0);

    return z;
}

double gpmp::stats::ProbDist::normal_PDF(double x, double mean, double stddev) {
    // Implement the probability density function (PDF) for the normal
    // distribution You can use standard libraries or existing implementations
    // for this calculation Example using C++ standard library:
    double exponent = -0.5 * std::pow((x - mean) / stddev, 2.0);
    return (1.0 / (stddev * std::sqrt(2.0 * M_PI))) * std::exp(exponent);
}

double gpmp::stats::ProbDist::normal_CDF(double x, double mean, double stddev) {
    // Implement the cumulative distribution function (CDF) for the normal
    // distribution You can use standard libraries or existing implementations
    // for this calculation Example using C++ standard library:
    return 0.5 * (1.0 + std::erf((x - mean) / (stddev * std::sqrt(2.0))));
}

double gpmp::stats::ProbDist::uniform_CDF(size_t k, size_t n) {
    if (k == 0 || k > n) {
        return 0.0; // Invalid input, return 0
    }

    return static_cast<double>(k) / (n + 1);
}

double gpmp::stats::ProbDist::exp_PDF(double x, size_t k, double lambda) {
    // Check if k is valid (k must be 1 for exponential distribution)
    if (k != 1) {
        // Return 0 if k is not 1, as exponential distribution is only defined
        // for k = 1
        return 0.0;
    }

    // Check if lambda is non-positive
    if (lambda <= 0) {
        // Return 0 if lambda is non-positive
        return 0.0;
    }

    // Calculate the exponential PDF
    return (k / lambda) * exp(-k * x);
}

double gpmp::stats::ProbDist::emp_CDF(const std::vector<double> &data,
                                      double x) {
    size_t count = 0;
    for (const auto &value : data) {
        if (value <= x) {
            count++;
        }
    }

    return static_cast<double>(count) / data.size();
}

double gpmp::stats::ProbDist::emp_PMF(const std::vector<double> &data,
                                      double x) {
    size_t count = std::count(data.begin(), data.end(), x);
    return static_cast<double>(count) / data.size();
}

double gpmp::stats::ProbDist::inverse_emp_CDF(const std::vector<double> &data,
                                              double p) {
    if (data.empty() || p < 0.0 || p > 1.0) {
        return 0.0; // Invalid input, return 0
    }

    std::vector<double> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());

    size_t index = static_cast<size_t>(p * (data.size() - 1));
    return sortedData[index];
}

double gpmp::stats::ProbDist::mle(const std::vector<double> &data) {
    if (data.empty()) {
        return 0.0; // Invalid input, return 0
    }

    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

double gpmp::stats::ProbDist::mom(const std::vector<double> &data) {
    if (data.empty()) {
        return 0.0; // Invalid input, return 0
    }
    gpmp::stats::Describe desc;

    double mean = desc.mean_arith(data);
    double variance = desc.variance(data, mean);

    return mean - variance / 2.0;
}

double gpmp::stats::ProbDist::mle_est(const std::vector<double> &data) {
    // This is a placeholder, you can replace it with a specific M-estimation
    // method
    return mle(data);
}

double gpmp::stats::ProbDist::mumv(const std::vector<double> &data) {
    if (data.empty()) {
        return 0.0; // Invalid input, return 0
    }

    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

double gpmp::stats::ProbDist::median_uniased(const std::vector<double> &data) {
    if (data.empty()) {
        return 0.0; // Invalid input, return 0
    }

    std::vector<double> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());

    size_t size = sortedData.size();
    if (size % 2 == 0) {
        return (sortedData[size / 2 - 1] + sortedData[size / 2]) / 2.0;
    } else {
        return sortedData[size / 2];
    }
}

// Interval Estimation
std::pair<double, double>
gpmp::stats::ProbDist::ConfidenceInterval(const std::vector<double> &data,
                                          double alpha) {
    if (data.empty() || alpha <= 0.0 || alpha >= 1.0) {
        return {0.0, 0.0}; // Invalid input, return an empty interval
    }

    size_t n = data.size();
    gpmp::stats::Describe desc;
    double mean = desc.mean_arith(data);
    double stddev = desc.stdev(data, mean);

    // Assuming a normal distribution for simplicity
    double z = quantile_dist(1 - alpha / 2.0);
    double margin = z * stddev / std::sqrt(static_cast<double>(n));

    return {mean - margin, mean + margin};
}

double gpmp::stats::ProbDist::Pivot(
    const std::vector<double> &data,
    double pivotFunction(const std::vector<double> &)) {
    if (data.empty()) {
        return 0.0; // Invalid input, return 0
    }

    return pivotFunction(data);
}

// Example of a pivot function for Confidence Interval
double gpmp::stats::ProbDist::PivotFunctionForConfidenceInterval(
    const std::vector<double> &data) {
    size_t n = data.size();

    gpmp::stats::Describe desc;
    double mean = desc.mean_arith(data);
    double stddev = desc.stdev(data, mean);

    return mean + 2 * stddev / std::sqrt(static_cast<double>(n));
}

std::pair<double, double>
gpmp::stats::ProbDist::LikelihoodInterval(const std::vector<double> &data,
                                          double alpha) {
    // Example implementation, this needs to be adapted based on the specific
    // likelihood function
    if (data.empty() || alpha <= 0.0 || alpha >= 1.0) {
        return {0.0, 0.0}; // Invalid input, return an empty interval
    }

    // Placeholder, implement likelihood function and find confidence bounds
    double lowerBound = 0.0;
    double upperBound = 1.0;

    return {lowerBound, upperBound};
}

std::pair<double, double>
gpmp::stats::ProbDist::PredictionInterval(const std::vector<double> &data,
                                          double alpha) {
    if (data.empty() || alpha <= 0.0 || alpha >= 1.0) {
        return {0.0, 0.0}; // Invalid input, return an empty interval
    }

    // Placeholder, implement prediction interval calculation
    double lowerBound = 0.0;
    double upperBound = 1.0;

    return {lowerBound, upperBound};
}

std::pair<double, double>
gpmp::stats::ProbDist::ToleranceInterval(const std::vector<double> &data,
                                         double alpha) {
    if (data.empty() || alpha <= 0.0 || alpha >= 1.0) {
        return {0.0, 0.0}; // Invalid input, return an empty interval
    }

    // Placeholder, implement tolerance interval calculation
    double lowerBound = 0.0;
    double upperBound = 1.0;

    return {lowerBound, upperBound};
}

std::pair<double, double>
gpmp::stats::ProbDist::BootstrapResampling(const std::vector<double> &data,
                                           int numSamples) {
    if (data.empty() || numSamples <= 0) {
        return {0.0, 0.0}; // Invalid input, return an empty interval
    }

    std::vector<double> resampledMeans;
    resampledMeans.reserve(numSamples);

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<size_t> distribution(0, data.size() - 1);
    gpmp::stats::Describe desc;

    for (int i = 0; i < numSamples; ++i) {
        std::vector<double> resampledData;
        resampledData.reserve(data.size());
        for (size_t j = 0; j < data.size(); ++j) {
            resampledData.push_back(data[distribution(gen)]);
        }
        resampledMeans.push_back(desc.mean_arith(resampledData));
    }

    std::sort(resampledMeans.begin(), resampledMeans.end());

    double lowerBound = resampledMeans[numSamples / 20];
    double upperBound = resampledMeans[19 * numSamples / 20];

    return {lowerBound, upperBound};
}

std::pair<double, double>
gpmp::stats::ProbDist::JackknifeResampling(const std::vector<double> &data) {
    if (data.empty()) {
        return {0.0, 0.0}; // Invalid input, return an empty interval
    }

    size_t n = data.size();

    std::vector<double> resampledMeans;
    resampledMeans.reserve(n);
    gpmp::stats::Describe desc;

    for (size_t i = 0; i < n; ++i) {
        std::vector<double> resampledData;
        resampledData.reserve(n - 1);
        for (size_t j = 0; j < n; ++j) {
            if (j != i) {
                resampledData.push_back(data[j]);
            }
        }
        resampledMeans.push_back(desc.mean_arith(resampledData));
    }

    std::sort(resampledMeans.begin(), resampledMeans.end());

    double lowerBound = resampledMeans[n / 20];
    double upperBound = resampledMeans[19 * n / 20];

    return {lowerBound, upperBound};
}
