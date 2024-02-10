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

#include "../../include/linalg/sigproc.hpp"
#include <algorithm>
#include <complex>
#include <iostream>
#include <map>
#include <stdexcept>
#include <utility>
#include <vector>

gpmp::linalg::SigProc::SigProc(const std::vector<double> &signal)
    : signal_(signal) {
}

double gpmp::linalg::SigProc::mean() const {
    double sum = 0.0;
    for (const auto &value : signal_) {
        sum += value;
    }
    return sum / static_cast<double>(signal_.size());
}

double gpmp::linalg::SigProc::stdev() const {
    double mn = mean();
    double sumSquaredDiff = 0.0;

    for (const auto &value : signal_) {
        double diff = value - mn;
        sumSquaredDiff += diff * diff;
    }

    return std::sqrt(sumSquaredDiff / static_cast<double>(signal_.size()));
}

void gpmp::linalg::SigProc::lpf(double alpha) {
    if (alpha <= 0.0 || alpha >= 1.0) {
        throw std::invalid_argument(
            "Error: Alpha must be in the range (0, 1).");
    }

    for (size_t i = 1; i < signal_.size(); ++i) {
        signal_[i] = alpha * signal_[i] + (1 - alpha) * signal_[i - 1];
    }
}

void gpmp::linalg::SigProc::normalize() {
    double mn = mean();
    double stdDev = stdev();

    for (auto &value : signal_) {
        value = (value - mn) / stdDev;
    }
}

std::vector<double> gpmp::linalg::SigProc::get_sig() const {
    return signal_;
}

std::map<int, double>
gpmp::linalg::SigProc::z_tform(const std::map<int, double> &signal) {
    std::map<int, double> result;

    for (const auto &entry : signal) {
        int index = entry.first;

        // exponent, negate this for meeting formula requirement
        int exp = index * (-1);

        // coeffecient
        double coeff = entry.second;

        // populate result map
        result.insert({exp, coeff});
    }

    return result;
}

std::vector<std::pair<int, double>> gpmp::linalg::SigProc::z_tform(
    const std::vector<std::pair<int, double>> &signal) {
    std::vector<std::pair<int, double>> result;

    for (const auto &entry : signal) {
        int index = entry.first;

        // exponent, negate this for meeting formula requirement
        int exp = index * (-1);

        // coefficient
        double coeff = entry.second;

        // populate result vector
        result.push_back({exp, coeff});
    }

    return result;
}

std::complex<double>
gpmp::linalg::SigProc::z_adv_tform(const std::complex<double> &z,
                                   int delay) const {
    std::complex<double> result = 0.0;
    for (size_t n = 0; n < signal_.size(); ++n) {
        result += signal_[n] * std::pow(z, -static_cast<double>(n - delay));
    }
    return result;
}

std::complex<double> gpmp::linalg::SigProc::z_matched_tform(
    const std::complex<double> &z,
    const std::vector<double> &referenceSignal) const {
    if (signal_.size() != referenceSignal.size()) {
        throw std::invalid_argument(
            "Error: Signal and reference signal must have the same size.");
    }

    std::complex<double> result = 0.0;
    for (size_t n = 0; n < signal_.size(); ++n) {
        result += signal_[n] * referenceSignal[n] *
                  std::pow(z, -static_cast<double>(n));
    }
    return result;
}

std::vector<double> gpmp::linalg::SigProc::bilinear_tform(double Ts) const {
    size_t N = signal_.size();
    std::vector<double> result(N);

    for (size_t n = 0; n < N; ++n) {
        double t = static_cast<double>(n) * Ts;
        result[n] = signal_[n] / (1.0 + t);
    }

    return result;
}

std::vector<double> gpmp::linalg::SigProc::bilinear_adv_tform(double Ts,
                                                              int delay) const {
    size_t N = signal_.size();
    std::vector<double> result(N);

    for (size_t n = 0; n < N; ++n) {
        double t = static_cast<double>(n - delay) * Ts;
        result[n] = signal_[n] / (1.0 + t);
    }

    return result;
}

std::vector<double> gpmp::linalg::SigProc::bilinear_matched_tform(
    double Ts,
    const std::vector<double> &referenceSignal) const {
    if (signal_.size() != referenceSignal.size()) {
        throw std::invalid_argument(
            "Error: Signal and reference signal must have the same size.");
    }

    size_t N = signal_.size();
    std::vector<double> result(N);

    for (size_t n = 0; n < N; ++n) {
        double t = static_cast<double>(n) * Ts;
        result[n] = signal_[n] * referenceSignal[n] / (1.0 + t);
    }

    return result;
}

std::vector<double>
gpmp::linalg::SigProc::compute_constant_q_transform(double Q, double Ts) const {
    size_t N = signal_.size();
    std::vector<double> result(N);

    for (size_t n = 0; n < N; ++n) {
        double t = static_cast<double>(n) * Ts;
        result[n] = signal_[n] * std::exp(-2.0 * M_PI * Q * t);
    }

    return result;
}

std::vector<double>
gpmp::linalg::SigProc::compute_inverse_constant_q_transform(double Q,
                                                            double Ts) const {
    size_t N = signal_.size();
    std::vector<double> result(N);

    for (size_t n = 0; n < N; ++n) {
        double t = static_cast<double>(n) * Ts;
        result[n] = signal_[n] * std::exp(2.0 * M_PI * Q * t);
    }

    return result;
}

std::vector<double> gpmp::linalg::SigProc::compute_dct(size_t M) const {
    size_t N = signal_.size();
    std::vector<double> result(M, 0.0);

    for (size_t m = 0; m < M; ++m) {
        double sum = 0.0;
        double coef = (m == 0) ? 1.0 / std::sqrt(2.0) : 1.0;

        for (size_t n = 0; n < N; ++n) {
            double theta = (M_PI * m * (2.0 * n + 1)) / (2.0 * N);
            sum += signal_[n] * std::cos(theta);
        }

        result[m] = coef * sum;
    }

    return result;
}

std::vector<double> gpmp::linalg::SigProc::compute_inverse_dct(size_t M) const {
    size_t N = signal_.size();
    std::vector<double> result(N, 0.0);

    for (size_t n = 0; n < N; ++n) {
        double sum = 0.0;

        for (size_t m = 0; m < M; ++m) {
            double coef = (m == 0) ? 1.0 / std::sqrt(2.0) : 1.0;
            double theta = (M_PI * m * (2.0 * n + 1)) / (2.0 * N);
            sum += coef * signal_[m] * std::cos(theta);
        }

        result[n] = sum;
    }

    return result;
}

std::vector<std::complex<double>> gpmp::linalg::SigProc::compute_dft() const {
    size_t N = signal_.size();
    std::vector<std::complex<double>> result(N, 0.0);

    for (size_t k = 0; k < N; ++k) {
        for (size_t n = 0; n < N; ++n) {
            double theta = -2.0 * M_PI * k * n / N;
            result[k] += signal_[n] * std::polar(1.0, theta);
        }
    }

    return result;
}

std::vector<double> gpmp::linalg::SigProc::compute_inverse_dft() const {
    size_t N = signal_.size();
    std::vector<double> result(N, 0.0);

    for (size_t n = 0; n < N; ++n) {
        for (size_t k = 0; k < N; ++k) {
            double theta = 2.0 * M_PI * k * n / N;
            result[n] += std::real(signal_[k] * std::polar(1.0, theta));
        }

        result[n] /= N;
    }

    return result;
}

std::vector<double> gpmp::linalg::SigProc::compute_magnitude_spectrum() const {
    auto dft_result = compute_dft();
    std::vector<double> magnitude_spectrum(dft_result.size(), 0.0);

    for (size_t k = 0; k < dft_result.size(); ++k) {
        magnitude_spectrum[k] = std::abs(dft_result[k]);
    }

    return magnitude_spectrum;
}

std::vector<double> gpmp::linalg::SigProc::compute_phase_spectrum() const {
    auto dft_result = compute_dft();
    std::vector<double> phase_spectrum(dft_result.size(), 0.0);

    for (size_t k = 0; k < dft_result.size(); ++k) {
        phase_spectrum[k] = std::arg(dft_result[k]);
    }

    return phase_spectrum;
}

std::vector<std::complex<double>>
gpmp::linalg::SigProc::compute_dtft(const std::vector<double> &omega) const {
    size_t N = signal_.size();
    std::vector<std::complex<double>> result(omega.size(), 0.0);

    for (size_t w = 0; w < omega.size(); ++w) {
        for (size_t n = 0; n < N; ++n) {
            double theta = -omega[w] * n;
            result[w] += signal_[n] * std::polar(1.0, theta);
        }
    }

    return result;
}

std::vector<double> gpmp::linalg::SigProc::compute_inverse_dtft(
    const std::vector<double> &omega) const {
    size_t N = signal_.size();
    std::vector<double> result(omega.size(), 0.0);

    for (size_t w = 0; w < omega.size(); ++w) {
        for (size_t n = 0; n < N; ++n) {
            double theta = omega[w] * n;
            result[w] += std::real(signal_[n] * std::polar(1.0, theta));
        }
    }

    return result;
}

std::vector<double> gpmp::linalg::SigProc::compute_dtft_magnitude_spectrum(
    const std::vector<double> &omega) const {
    auto dtft_result = compute_dtft(omega);
    std::vector<double> magnitude_spectrum(dtft_result.size(), 0.0);

    for (size_t w = 0; w < dtft_result.size(); ++w) {
        magnitude_spectrum[w] = std::abs(dtft_result[w]);
    }

    return magnitude_spectrum;
}

std::vector<double> gpmp::linalg::SigProc::compute_dtft_phase_spectrum(
    const std::vector<double> &omega) const {
    auto dtft_result = compute_dtft(omega);
    std::vector<double> phase_spectrum(dtft_result.size(), 0.0);

    for (size_t w = 0; w < dtft_result.size(); ++w) {
        phase_spectrum[w] = std::arg(dtft_result[w]);
    }

    return phase_spectrum;
}

std::vector<double> gpmp::linalg::SigProc::design_discrete_system(
    const std::vector<double> &analog_system_coefficients,
    double sampling_rate) {
    // Design a discrete-time system using impulse invariance method
    size_t order = analog_system_coefficients.size() - 1;
    std::vector<double> discrete_system_coefficients(order + 1, 0.0);

    // Impulse invariance transformation
    for (size_t k = 0; k <= order; ++k) {
        double ak = analog_system_coefficients[k];
        for (size_t n = 0; n <= order; ++n) {
            discrete_system_coefficients[n] +=
                ak * std::sin(2 * M_PI * n * sampling_rate / 2.0) / (M_PI * n);
        }
    }

    return discrete_system_coefficients;
}

std::vector<double> gpmp::linalg::SigProc::impulse_invariance_transform(
    const std::vector<double> &analog_signal,
    double analog_sampling_rate,
    double discrete_sampling_rate) {
    size_t M = analog_signal.size();
    std::vector<double> discrete_signal(M, 0.0);

    // Impulse invariance transformation
    for (size_t m = 0; m < M; ++m) {
        double t = m / analog_sampling_rate;
        double sum = 0.0;

        for (size_t n = 0; n < M; ++n) {
            sum += analog_signal[n] *
                   std::sin(M_PI * discrete_sampling_rate *
                            (t - n / discrete_sampling_rate)) /
                   (M_PI * (t - n / discrete_sampling_rate));
        }

        discrete_signal[m] = sum;
    }

    return discrete_signal;
}

std::vector<double> gpmp::linalg::SigProc::zak_transform(
    const std::vector<double> &time_domain_signal,
    double frequency,
    double period) {
    size_t N = time_domain_signal.size();
    std::vector<double> zak_domain_signal(N, 0.0);

    for (size_t n = 0; n < N; ++n) {
        zak_domain_signal[n] += time_domain_signal[n] *
                                std::exp(-2 * M_PI * frequency * n / period);
    }

    return zak_domain_signal;
}

std::vector<double> gpmp::linalg::SigProc::inverse_zak_transform(
    const std::vector<double> &zak_domain_signal,
    double frequency,
    double period) {
    size_t N = zak_domain_signal.size();
    std::vector<double> time_domain_signal(N, 0.0);

    for (size_t n = 0; n < N; ++n) {
        time_domain_signal[n] +=
            zak_domain_signal[n] * std::exp(2 * M_PI * frequency * n / period);
    }

    return time_domain_signal;
}

std::vector<double> gpmp::linalg::SigProc::zak_transform_modulation(
    const std::vector<double> &time_domain_signal,
    double frequency,
    double period,
    double modulation_index) {
    size_t N = time_domain_signal.size();
    std::vector<double> zak_domain_signal(N, 0.0);

    for (size_t n = 0; n < N; ++n) {
        zak_domain_signal[n] +=
            time_domain_signal[n] *
            std::exp(-2 * M_PI * frequency * n / period +
                     modulation_index *
                         std::sin(2 * M_PI * frequency * n / period));
    }

    return zak_domain_signal;
}

std::vector<double> gpmp::linalg::SigProc::inverse_zak_transform_modulation(
    const std::vector<double> &zak_domain_signal,
    double frequency,
    double period,
    double modulation_index) {
    size_t N = zak_domain_signal.size();
    std::vector<double> time_domain_signal(N, 0.0);

    for (size_t n = 0; n < N; ++n) {
        time_domain_signal[n] +=
            zak_domain_signal[n] *
            std::exp(2 * M_PI * frequency * n / period -
                     modulation_index *
                         std::sin(2 * M_PI * frequency * n / period));
    }

    return time_domain_signal;
}

std::vector<double> gpmp::linalg::SigProc::apply_aliasing_filter(
    const std::vector<double> &input_signal,
    double sampling_rate,
    double aliasing_frequency) {
    // Alias the signal by introducing frequency components beyond Nyquist.
    size_t num_samples = input_signal.size();
    std::vector<double> aliased_signal(num_samples);

    for (size_t i = 0; i < num_samples; ++i) {
        double time = static_cast<double>(i) / sampling_rate;
        aliased_signal[i] = std::sin(2.0 * M_PI * aliasing_frequency * time);
    }

    return aliased_signal;
}

std::vector<double> gpmp::linalg::SigProc::apply_anti_aliasing_filter(
    const std::vector<double> &input_signal,
    double sampling_rate,
    double cutoff_frequency) {
    // Apply a simple low-pass filter as an anti-aliasing measure.
    // Note: This is a basic example; actual anti-aliasing filters may require
    // more sophisticated designs.

    size_t num_samples = input_signal.size();
    std::vector<double> anti_aliased_signal(num_samples);

    // Design a simple first-order low-pass filter.
    double RC = 1.0 / (2.0 * M_PI * cutoff_frequency);
    double alpha = 1.0 / (1.0 + RC * sampling_rate);

    // Apply the low-pass filter.
    anti_aliased_signal[0] = input_signal[0];
    for (size_t i = 1; i < num_samples; ++i) {
        anti_aliased_signal[i] = alpha * input_signal[i] +
                                 (1.0 - alpha) * anti_aliased_signal[i - 1];
    }

    return anti_aliased_signal;
}

std::vector<double>
gpmp::linalg::SigProc::generate_aliased_sinusoid(double sampling_rate,
                                                 double aliasing_frequency,
                                                 double duration) {
    size_t num_samples = static_cast<size_t>(sampling_rate * duration);
    std::vector<double> aliased_sinusoid(num_samples);

    for (size_t i = 0; i < num_samples; ++i) {
        double time = static_cast<double>(i) / sampling_rate;
        aliased_sinusoid[i] = std::sin(2.0 * M_PI * aliasing_frequency * time);
    }

    return aliased_sinusoid;
}

std::vector<double>
gpmp::linalg::SigProc::decimate(const std::vector<double> &signal,
                                size_t factor) {
    if (factor <= 1) {
        std::cerr << "Error: Downsampling factor must be greater than 1."
                  << std::endl;
        return signal;
    }

    size_t original_size = signal.size();
    size_t downsampled_size = original_size / factor;
    std::vector<double> downsampled_signal(downsampled_size);

    for (size_t i = 0; i < downsampled_size; ++i) {
        downsampled_signal[i] = signal[i * factor];
    }

    return downsampled_signal;
}
std::vector<double>
gpmp::linalg::SigProc::average_downsample(const std::vector<double> &signal,
                                          size_t factor) {
    if (factor <= 1) {
        std::cerr << "Error: Downsampling factor must be greater than 1."
                  << std::endl;
        return signal;
    }

    size_t original_size = signal.size();
    size_t downsampled_size = original_size / factor;
    std::vector<double> downsampled_signal(downsampled_size);

    for (size_t i = 0; i < downsampled_size; ++i) {
        size_t start_index = i * factor;
        size_t end_index = start_index + factor;
        double sum = 0.0;

        for (size_t j = start_index; j < end_index; ++j) {
            sum += signal[j];
        }

        downsampled_signal[i] = sum / static_cast<double>(factor);
    }

    return downsampled_signal;
}

std::vector<double>
gpmp::linalg::SigProc::max_pool_downsample(const std::vector<double> &signal,
                                           size_t factor) {
    if (factor <= 1) {
        std::cerr << "Error: Downsampling factor must be greater than 1."
                  << std::endl;
        return signal;
    }

    size_t original_size = signal.size();
    size_t downsampled_size = original_size / factor;
    std::vector<double> downsampled_signal(downsampled_size);

    for (size_t i = 0; i < downsampled_size; ++i) {
        size_t start_index = i * factor;
        size_t end_index = start_index + factor;
        downsampled_signal[i] = *std::max_element(signal.begin() + start_index,
                                                  signal.begin() + end_index);
    }

    return downsampled_signal;
}
std::vector<double>
gpmp::linalg::SigProc::strided_downsample(const std::vector<double> &signal,
                                          size_t factor) {
    if (factor <= 1) {
        std::cerr << "Error: Downsampling factor must be greater than 1."
                  << std::endl;
        return signal;
    }

    size_t original_size = signal.size();
    size_t downsampled_size = original_size / factor;
    std::vector<double> downsampled_signal(downsampled_size);

    for (size_t i = 0; i < downsampled_size; ++i) {
        downsampled_signal[i] = signal[i * factor];
    }

    return downsampled_signal;
}
std::vector<double> gpmp::linalg::SigProc::linear_interpolation_downsample(
    const std::vector<double> &signal,
    size_t factor) {
    if (factor <= 1) {
        std::cerr << "Error: Downsampling factor must be greater than 1."
                  << std::endl;
        return signal;
    }

    size_t original_size = signal.size();
    size_t downsampled_size = original_size / factor;
    std::vector<double> downsampled_signal(downsampled_size);

    for (size_t i = 0; i < downsampled_size; ++i) {
        size_t lower_index = i * factor;
        size_t upper_index = std::min(lower_index + factor, original_size);

        for (size_t j = lower_index; j < upper_index; ++j) {
            downsampled_signal[i] += signal[j];
        }

        downsampled_signal[i] /= static_cast<double>(upper_index - lower_index);
    }

    return downsampled_signal;
}
std::vector<double>
gpmp::linalg::SigProc::median_downsample(const std::vector<double> &signal,
                                         size_t factor) {
    if (factor <= 1) {
        std::cerr << "Error: Downsampling factor must be greater than 1."
                  << std::endl;
        return signal;
    }

    size_t original_size = signal.size();
    size_t downsampled_size = original_size / factor;
    std::vector<double> downsampled_signal(downsampled_size);

    for (size_t i = 0; i < downsampled_size; ++i) {
        size_t start_index = i * factor;
        size_t end_index = start_index + factor;

        std::vector<double> block(signal.begin() + start_index,
                                  signal.begin() + end_index);
        std::sort(block.begin(), block.end());
        downsampled_signal[i] = block[block.size() / 2]; // Median value
    }

    return downsampled_signal;
}

std::vector<double> gpmp::linalg::SigProc::nearest_neighbor_upsample(
    const std::vector<double> &signal,
    size_t factor) {
    if (factor <= 1) {
        std::cerr << "Error: Upsampling factor must be greater than 1."
                  << std::endl;
        return signal;
    }

    size_t original_size = signal.size();
    size_t upsampled_size = original_size * factor;
    std::vector<double> upsampled_signal(upsampled_size);

    for (size_t i = 0; i < original_size; ++i) {
        upsampled_signal[i * factor] = signal[i];
    }

    return upsampled_signal;
}
std::vector<double> gpmp::linalg::SigProc::linear_interpolation_upsample(
    const std::vector<double> &signal,
    size_t factor) {
    if (factor <= 1) {
        std::cerr << "Error: Upsampling factor must be greater than 1."
                  << std::endl;
        return signal;
    }

    size_t original_size = signal.size();
    size_t upsampled_size = original_size * factor;
    std::vector<double> upsampled_signal(upsampled_size);

    for (size_t i = 0; i < original_size - 1; ++i) {
        upsampled_signal[i * factor] = signal[i];
        for (size_t j = 1; j < factor; ++j) {
            upsampled_signal[i * factor + j] =
                signal[i] + j * (signal[i + 1] - signal[i]) / factor;
        }
    }

    upsampled_signal[upsampled_size - 1] = signal[original_size - 1];

    return upsampled_signal;
}

std::vector<double> gpmp::linalg::SigProc::zero_order_hold_upsample(
    const std::vector<double> &signal,
    size_t factor) {
    if (factor <= 1) {
        std::cerr << "Error: Upsampling factor must be greater than 1."
                  << std::endl;
        return signal;
    }

    size_t original_size = signal.size();
    size_t upsampled_size = original_size * factor;
    std::vector<double> upsampled_signal(upsampled_size);

    for (size_t i = 0; i < original_size - 1; ++i) {
        upsampled_signal[i * factor] = signal[i];
        for (size_t j = 1; j < factor; ++j) {
            upsampled_signal[i * factor + j] = signal[i];
        }
    }

    upsampled_signal[upsampled_size - 1] = signal[original_size - 1];

    return upsampled_signal;
}
