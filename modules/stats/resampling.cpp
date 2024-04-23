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
 * LICENSE file.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/
#include <algorithm>
#include <openGPMP/stats/resampling.hpp>
#include <random>
#include <stdexcept>
#include <vector>

// Resample with replacement
std::vector<int>
gpmp::stats::Resampling::bootstrap(const std::vector<int> &data,
                                   int numSamples) {
    std::vector<int> resampledData;
    resampledData.reserve(numSamples);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, data.size() - 1);

    for (int i = 0; i < numSamples; ++i) {
        int index = dist(rng);
        resampledData.push_back(data[index]);
    }

    return resampledData;
}

// Resample without replacement
std::vector<int>
gpmp::stats::Resampling::subsample(const std::vector<int> &data,
                                   int numSamples) {
    if (numSamples > static_cast<int>(data.size())) {
        throw std::invalid_argument(
            "Number of samples cannot exceed data size");
    }

    std::vector<int> resampledData = data;
    std::shuffle(resampledData.begin(),
                 resampledData.end(),
                 std::mt19937(std::random_device()()));

    resampledData.resize(numSamples);

    return resampledData;
}

// Jackknife resampling
std::vector<std::vector<int>>
gpmp::stats::Resampling::jackknife(const std::vector<int> &data) {
    int n = data.size();
    std::vector<std::vector<int>> resampledDatasets;
    resampledDatasets.reserve(n);

    for (int i = 0; i < n; ++i) {
        std::vector<int> resampledData = data;
        resampledData.erase(resampledData.begin() + i);
        resampledDatasets.push_back(resampledData);
    }

    return resampledDatasets;
}

// Permutation test
std::vector<std::vector<int>>
gpmp::stats::Resampling::permutation_test(const std::vector<int> &data,
                                          int numPermutations) {
    std::vector<std::vector<int>> permutedDatasets;
    permutedDatasets.reserve(numPermutations);

    std::mt19937 rng(std::random_device{}());

    for (int i = 0; i < numPermutations; ++i) {
        std::vector<int> permutedData = data;
        std::shuffle(permutedData.begin(), permutedData.end(), rng);
        permutedDatasets.push_back(permutedData);
    }

    return permutedDatasets;
}

// Bootstrap-t method
std::vector<double>
gpmp::stats::Resampling::bootstrap_t(const std::vector<double> &data,
                                     int numSamples) {
    std::vector<double> resampledMeans;
    resampledMeans.reserve(numSamples);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, data.size() - 1);

    for (int i = 0; i < numSamples; ++i) {
        std::vector<double> resampledData;
        resampledData.reserve(data.size());
        for (int j = 0; j < static_cast<int>(data.size()); ++j) {
            int index = dist(rng);
            resampledData.push_back(data[index]);
        }
        double mean =
            std::accumulate(resampledData.begin(), resampledData.end(), 0.0) /
            resampledData.size();
        resampledMeans.push_back(mean);
    }

    return resampledMeans;
}

// Bootstrapped confidence interval
std::pair<double, double>
gpmp::stats::Resampling::bootstrap_ci(const std::vector<double> &data,
                                      double alpha,
                                      int numSamples) {
    std::vector<double> resampledMeans = bootstrap_t(data, numSamples);
    std::sort(resampledMeans.begin(), resampledMeans.end());
    int lowerIndex = static_cast<int>((alpha / 2) * numSamples);
    int upperIndex = static_cast<int>((1 - alpha / 2) * numSamples) - 1;
    return std::make_pair(resampledMeans[lowerIndex],
                          resampledMeans[upperIndex]);
}

// Smoothed bootstrap
std::vector<double>
gpmp::stats::Resampling::smoothed_bootstrap(const std::vector<double> &data,
                                            int numSamples) {
    std::vector<double> resampledData;
    resampledData.reserve(numSamples);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, data.size() - 1);

    for (int i = 0; i < numSamples; ++i) {
        double sum = 0.0;
        for (int j = 0; j < static_cast<int>(data.size()); ++j) {
            int index = dist(rng);
            sum += data[index];
        }
        resampledData.push_back(sum / data.size());
    }

    return resampledData;
}

// Circular block bootstrap
std::vector<double> gpmp::stats::Resampling::circular_block_bootstrap(
    const std::vector<double> &data,
    int blockSize,
    int numSamples) {

    if (blockSize <= 0 || blockSize > static_cast<int>(data.size())) {
        throw std::invalid_argument("Invalid block size");
    }

    std::vector<double> resampledData;
    resampledData.reserve(numSamples);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, data.size() - 1);

    for (int i = 0; i < numSamples; ++i) {
        std::vector<double> blockMeans;
        blockMeans.reserve(data.size() / blockSize);
        for (int j = 0; j < static_cast<int>(data.size()) / blockSize; ++j) {
            double sum = 0.0;
            for (int k = 0; k < blockSize; ++k) {
                int index = dist(rng);
                sum += data[index];
            }
            blockMeans.push_back(sum / blockSize);
        }
        std::shuffle(blockMeans.begin(), blockMeans.end(), rng);
        resampledData.insert(resampledData.end(),
                             blockMeans.begin(),
                             blockMeans.end());
    }

    return resampledData;
}

// Time series bootstrap
std::vector<double>
gpmp::stats::Resampling::time_series_bootstrap(const std::vector<double> &data,
                                               int numSamples) {
    std::vector<double> resampledData;
    resampledData.reserve(numSamples);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, data.size() - 1);

    for (int i = 0; i < numSamples; ++i) {
        std::vector<double> resampledSequence;
        resampledSequence.reserve(data.size());
        int startIndex = dist(rng);
        for (int j = 0; j < static_cast<int>(data.size()); ++j) {
            int index = (startIndex + j) % data.size();
            resampledSequence.push_back(data[index]);
        }
        resampledData.insert(resampledData.end(),
                             resampledSequence.begin(),
                             resampledSequence.end());
    }

    return resampledData;
}

std::vector<double>
gpmp::stats::Resampling::weighted_bootstrap(const std::vector<double> &data,
                                            const std::vector<double> &weights,
                                            int size) {
    std::vector<double> resampledData;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> dis(weights.begin(), weights.end());
    for (int i = 0; i < size; ++i) {
        resampledData.push_back(data[dis(gen)]);
    }
    return resampledData;
}

double
gpmp::stats::Resampling::permutation_p_value(const std::vector<double> &data1,
                                             const std::vector<double> &data2,
                                             double observedStatistic) {
    int count = 0;
    std::vector<double> combinedData = data1;
    combinedData.insert(combinedData.end(), data2.begin(), data2.end());
    std::shuffle(combinedData.begin(),
                 combinedData.end(),
                 std::mt19937(std::random_device()()));
    std::vector<double> permutedData1(data1.begin(), data1.end());
    std::vector<double> permutedData2(data2.begin(), data2.end());
    for (int i = 0; i < 1000; ++i) {
        std::shuffle(combinedData.begin(),
                     combinedData.end(),
                     std::mt19937(std::random_device()()));
        auto permutedStatistic =
            (std::accumulate(combinedData.begin(),
                             combinedData.begin() + data1.size(),
                             0.0)) /
            data1.size();
        if (permutedStatistic >= observedStatistic) {
            count++;
        }
    }
    return count / 1000.0;
}
