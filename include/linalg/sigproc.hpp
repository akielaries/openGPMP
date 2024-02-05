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

#ifndef SIGPROC_HPP
#define SIGPROC_HPP

#include <cmath>
#include <complex>
#include <vector>

namespace gpmp {

namespace linalg {

class SigProc {
  public:
    /**
     * @brief Constructor
     * Initializes the SigProc object with a signal
     * @param signal The input signal
     */
    explicit SigProc(const std::vector<double> &signal);

    /**
     * @brief Compute the mean value of the signal
     * @return The mean value
     */
    double mean() const;

    /**
     * @brief Compute the standard deviation of the signal
     * @return The standard deviation
     */
    double stdev() const;

    /**
     * @brief Apply a simple low-pass filter to the signal
     * @param alpha Filter coefficient (0 < alpha < 1)
     */
    void lpf(double alpha);

    /**
     * @brief Normalize the signal to have zero mean and unit variance
     */
    void normalize();

    /**
     * @brief Get the processed signal
     * @return The processed signal
     */
    std::vector<double> get_sig() const;
    /**
     * @brief Compute the Z-transform of the signal
     * @param z Complex number representing the Z-transform variable
     * @return The Z-transform of the signal
     */
    std::complex<double> z_tform(const std::complex<double> &z) const;

    /**
     * @brief Compute the Advanced Z-transform of the signal
     * @param z Complex number representing the Z-transform variable
     * @param delay Delay parameter for the Advanced Z-transform
     * @return The Advanced Z-transform of the signal
     */
    std::complex<double> z_adv_tform(const std::complex<double> &z,
                                     int delay) const;

    /**
     * @brief Compute the Matched Z-transform of the signal
     * @param z Complex number representing the Z-transform variable
     * @param referenceSignal Reference signal for the Matched Z-transform
     * @return The Matched Z-transform of the signal
     */
    std::complex<double>
    z_matched_tform(const std::complex<double> &z,
                    const std::vector<double> &referenceSignal) const;

    /**
     * @brief Compute the Bilinear Transform of the signal
     * @param Ts Sampling period
     * @return The Bilinear Transform of the signal
     */
    std::vector<double> bilinear_tform(double Ts) const;

    /**
     * @brief Compute the Advanced Bilinear Transform of the signal
     * @param Ts Sampling period
     * @param delay Delay parameter for the Advanced Bilinear Transform
     * @return The Advanced Bilinear Transform of the signal
     */
    std::vector<double> bilinear_adv_tform(double Ts, int delay) const;

    /**
     * @brief Compute the Matched Bilinear Transform of the signal
     * @param Ts Sampling period
     * @param referenceSignal Reference signal for the Matched Bilinear
     * Transform
     * @return The Matched Bilinear Transform of the signal
     */
    std::vector<double>
    bilinear_matched_tform(double Ts,
                           const std::vector<double> &referenceSignal) const;

    /**
     * @brief Compute the constant-Q transform of the signal
     * @param Q Quality factor
     * @param Ts Sampling period
     * @return The constant-Q transform of the signal
     */
    std::vector<double> compute_constant_q_transform(double Q, double Ts) const;

    /**
     * @brief Compute the inverse constant-Q transform of the signal
     * @param Q Quality factor
     * @param Ts Sampling period
     * @return The inverse constant-Q transform of the signal
     */
    std::vector<double> compute_inverse_constant_q_transform(double Q,
                                                             double Ts) const;

    /**
     * @brief Compute the Discrete Cosine Transform (DCT) of the signal
     * @param M Number of coefficients (non-negative integer)
     * @return The DCT of the signal
     */
    std::vector<double> compute_dct(size_t M) const;

    /**
     * @brief Compute the Inverse Discrete Cosine Transform (IDCT) of the signal
     * @param M Number of coefficients (non-negative integer)
     * @return The IDCT of the signal
     */
    std::vector<double> compute_inverse_dct(size_t M) const;

    /**
     * @brief Compute the Discrete Fourier Transform (DFT) of the signal
     * @return The DFT of the signal
     */
    std::vector<std::complex<double>> compute_dft() const;

    /**
     * @brief Compute the Inverse Discrete Fourier Transform (IDFT) of the
     * signal
     * @return The IDFT of the signal
     */
    std::vector<double> compute_inverse_dft() const;

    /**
     * @brief Compute the magnitude spectrum of the signal
     * @return The magnitude spectrum
     */
    std::vector<double> compute_magnitude_spectrum() const;

    /**
     * @brief Compute the phase spectrum of the signal
     * @return The phase spectrum
     */
    std::vector<double> compute_phase_spectrum() const;

    /**
     * @brief Compute the Discrete-time Fourier Transform (DTFT) of the signal
     * @param omega Frequency values at which to compute the DTFT
     * @return The DTFT of the signal at the specified frequencies
     */
    std::vector<std::complex<double>>
    compute_dtft(const std::vector<double> &omega) const;

    /**
     * @brief Compute the Inverse Discrete-time Fourier Transform (IDTFT) of the
     * signal
     * @param omega Frequency values at which to compute the IDTFT
     * @return The IDTFT of the signal at the specified frequencies
     */
    std::vector<double>
    compute_inverse_dtft(const std::vector<double> &omega) const;

    /**
     * @brief Compute the magnitude spectrum of the DTFT of the signal
     * @param omega Frequency values at which to compute the DTFT
     * @return The magnitude spectrum of the DTFT
     */
    std::vector<double>
    compute_dtft_magnitude_spectrum(const std::vector<double> &omega) const;

    /**
     * @brief Compute the phase spectrum of the DTFT of the signal
     * @param omega Frequency values at which to compute the DTFT
     * @return The phase spectrum of the DTFT
     */
    std::vector<double>
    compute_dtft_phase_spectrum(const std::vector<double> &omega) const;

    /**
     * @brief Design a discrete-time system using the impulse invariance method
     * @param analog_system_coefficients Coefficients of the analog system
     * @param sampling_rate Sampling rate of the discrete-time system
     * @return Coefficients of the discrete-time system
     */
    std::vector<double> design_discrete_system(
        const std::vector<double> &analog_system_coefficients,
        double sampling_rate);

    /**
     * @brief Apply the impulse invariance method to transform an analog signal
     * to discrete time
     * @param analog_signal Analog signal to be transformed
     * @param analog_sampling_rate Sampling rate of the analog signal
     * @param discrete_sampling_rate Sampling rate of the discrete-time system
     * @return Discrete-time signal after transformation
     */
    std::vector<double>
    impulse_invariance_transform(const std::vector<double> &analog_signal,
                                 double analog_sampling_rate,
                                 double discrete_sampling_rate);

    /**
     * @brief Perform the Zak transform on a given time domain signal
     *
     * @param time_domain_signal The input time domain signal
     * @param frequency The frequency of the Zak transform
     * @param period The period of the Zak transform
     * @return The Zak domain signal
     */
    std::vector<double>
    zak_transform(const std::vector<double> &time_domain_signal,
                  double frequency,
                  double period);

    /**
     * @brief Perform the inverse Zak transform on a given Zak domain signal
     *
     * @param zak_domain_signal The input Zak domain signal
     * @param frequency The frequency of the Zak transform
     * @param period The period of the Zak transform
     * @return The reconstructed time domain signal
     */
    std::vector<double>
    inverse_zak_transform(const std::vector<double> &zak_domain_signal,
                          double frequency,
                          double period);

    /**
     * @brief Perform Zak transform modulation on a given time domain signal
     *
     * @param time_domain_signal The input time domain signal
     * @param frequency The frequency of the Zak transform
     * @param period The period of the Zak transform
     * @param modulation_index The modulation index for Zak transform
     * modulation
     * @return The modulated Zak domain signal
     */
    std::vector<double>
    zak_transform_modulation(const std::vector<double> &time_domain_signal,
                             double frequency,
                             double period,
                             double modulation_index);

    /**
     * @brief Perform the inverse Zak transform modulation on a given modulated
     * Zak domain signal
     *
     * @param zak_domain_signal The input modulated Zak domain signal
     * @param frequency The frequency of the Zak transform
     * @param period The period of the Zak transform
     * @param modulation_index The modulation index for Zak transform
     * modulation
     * @return The reconstructed time domain signal after modulation
     */
    std::vector<double> inverse_zak_transform_modulation(
        const std::vector<double> &zak_domain_signal,
        double frequency,
        double period,
        double modulation_index);

    /**
     * @brief Apply an aliasing filter to a given signal
     *
     * @param input_signal The input signal
     * @param sampling_rate The sampling rate of the signal
     * @param aliasing_frequency The aliasing frequency to introduce
     * @return The signal after aliasing
     */
    std::vector<double>
    apply_aliasing_filter(const std::vector<double> &input_signal,
                          double sampling_rate,
                          double aliasing_frequency);
    /**
     * @brief Apply an anti-aliasing filter to remove high-frequency components
     * from a signal
     *
     * @param input_signal The input signal with potential high-frequency
     * components
     * @param sampling_rate The sampling rate of the signal
     * @param cutoff_frequency The cutoff frequency of the anti-aliasing filter
     * @return The signal after anti-aliasing
     */
    std::vector<double>
    apply_anti_aliasing_filter(const std::vector<double> &input_signal,
                               double sampling_rate,
                               double cutoff_frequency);

    /**
     * @brief Generate a sinusoidal signal with a frequency beyond the Nyquist
     * limit, leading to aliasing when sampled
     *
     * @param sampling_rate The sampling rate of the signal
     * @param aliasing_frequency The aliasing frequency to introduce
     * @param duration The duration of the signal in seconds
     * @return The aliased sinusoidal signal
     */
    std::vector<double> generate_aliased_sinusoid(double sampling_rate,
                                                  double aliasing_frequency,
                                                  double duration);

    /**
     * Downsample a signal by a given factor using the Decimation method
     *
     * @param signal The input signal
     * @param factor The downsampling factor
     * @return The downsampled signal
     */
    std::vector<double> decimate(const std::vector<double> &signal,
                                 size_t factor);

    /**
     * Downsample a signal by averaging blocks of samples
     *
     * @param signal The input signal
     * @param factor The downsampling factor
     * @return The downsampled signal
     */
    std::vector<double> average_downsample(const std::vector<double> &signal,
                                           size_t factor);

    /**
     * Downsample a signal using the Max-Pooling method
     *
     * @param signal The input signal
     * @param factor The downsampling factor
     * @return The downsampled signal
     */
    std::vector<double> max_pool_downsample(const std::vector<double> &signal,
                                            size_t factor);

    /**
     * Downsample a signal by selecting every Nth sample using the Strided
     * method
     *
     * @param signal The input signal
     * @param factor The downsampling factor
     * @return The downsampled signal
     */
    std::vector<double> strided_downsample(const std::vector<double> &signal,
                                           size_t factor);

    /**
     * Downsample a signal by interpolating between samples using Linear
     * Interpolation
     *
     * @param signal The input signal
     * @param factor The downsampling factor
     * @return The downsampled signal
     */
    std::vector<double>
    linear_interpolation_downsample(const std::vector<double> &signal,
                                    size_t factor);

    /**
     * Downsample a signal by selecting the median value in each block
     *
     * @param signal The input signal
     * @param factor The downsampling factor
     * @return The downsampled signal
     */
    std::vector<double> median_downsample(const std::vector<double> &signal,
                                          size_t factor);
    /**
     * Upsample a signal using the Nearest Neighbor method
     *
     * @param signal The input signal
     * @param factor The upsampling factor
     * @return The upsampled signal
     */
    std::vector<double>
    nearest_neighbor_upsample(const std::vector<double> &signal, size_t factor);

    /**
     * Upsample a signal using Linear Interpolation
     *
     * @param signal The input signal
     * @param factor The upsampling factor
     * @return The upsampled signal
     */
    std::vector<double>
    linear_interpolation_upsample(const std::vector<double> &signal,
                                  size_t factor);

    /**
     * Upsample a signal using Zero-Order Hold
     *
     * @param signal The input signal
     * @param factor The upsampling factor
     * @return The upsampled signal
     */
    std::vector<double>
    zero_order_hold_upsample(const std::vector<double> &signal, size_t factor);

  private:
    std::vector<double> signal_;
};

} // namespace linalg
} // namespace gpmp
#endif
