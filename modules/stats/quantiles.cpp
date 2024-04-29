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
#include <numeric>
// #include <openGPMP/stats/quantiles.hpp>
#include <random>
#include <stdexcept>
#include <vector>

class Quantile {
  public:
    // Bernoulli distribution quantile function
    static double bernoulli(double p, double q) {
        return (q < p) ? 0.0 : 1.0;
    }

    // Beta distribution quantile function
    static double beta(double alpha, double beta, double q) {
        if (q <= 0.0)
            return 0.0;
        if (q >= 1.0)
            return 1.0;

        double result = 0.0;
        if (q > 0.5)
            result = 1.0 - incompleteBeta(beta, alpha, 1.0 - q);
        else
            result = incompleteBeta(alpha, beta, q);

        return result;
    }

    // Binomial distribution quantile function
    static int binomial(int n, double p, double q) {
        int x = 0;
        double cdf = 0.0;
        while (x <= n) {
            cdf += binomialCoefficient(n, x) * pow(p, x) * pow(1.0 - p, n - x);
            if (cdf >= q)
                return x;
            x++;
        }
        return n;
    }

    // Cauchy distribution quantile function
    static double cauchy(double median, double scale, double q) {
        return median + scale * tan(M_PI * (q - 0.5));
    }

    // Chi-squared distribution quantile function
    static double chiSquared(int df, double q) {
        if (q < 0.0 || q > 1.0 || df < 1)
            return NAN;
        return df * inverseGamma(0.5 * df, q);
    }

    // Exponential distribution quantile function
    static double exponential(double lambda, double q) {
        if (q < 0.0 || q > 1.0 || lambda <= 0.0)
            return NAN;
        return -log(1.0 - q) / lambda;
    }

    // F distribution quantile function
    static double f(int df1, int df2, double q) {
        if (q <= 0.0 || q >= 1.0 || df1 <= 0 || df2 <= 0)
            return NAN;
        return (inverseBeta(0.5 * df2, 0.5 * df1, q) * df2) /
               (inverseBeta(0.5 * df2, 0.5 * df1, 1.0 - q) * df1);
    }

    // Gamma distribution quantile function
    static double gamma(double shape, double scale, double q) {
        if (q < 0.0 || q > 1.0 || shape <= 0.0 || scale <= 0.0)
            return NAN;
        return shape * scale * inverseGamma(shape, q);
    }

    // Inverse-Gamma distribution quantile function
    static double inverseGamma(double shape, double q) {
        if (q < 0.0 || q > 1.0 || shape <= 0.0)
            return NAN;
        return 1.0 / gamma(shape, 1.0 / shape, 1.0 - q);
    }

  private:
    static double incompleteBeta(double a, double b, double x) {
        const int maxIterations = 200;
        const double epsilon = 1.0e-15;

        double bt = (x == 0.0 || x == 1.0)
                        ? 0.0
                        : exp(gammaLn(a + b) - gammaLn(a) - gammaLn(b) +
                              a * log(x) + b * log(1.0 - x));

        if (x < (a + 1.0) / (a + b + 2.0))
            return bt * betaContinuedFraction(a, b, x) / a;
        else
            return 1.0 - bt * betaContinuedFraction(b, a, 1.0 - x) / b;
    }

    static double gammaLn(double xx) {
        double x, y, tmp, ser;
        static const double cof[6] = {76.18009172947146,
                                      -86.50532032941677,
                                      24.01409824083091,
                                      -1.231739572450155,
                                      0.1208650973866179e-2,
                                      -0.5395239384953e-5};
        int j;

        y = x = xx;
        tmp = x + 5.5;
        tmp -= (x + 0.5) * log(tmp);
        ser = 1.000000000190015;
        for (j = 0; j < 6; j++)
            ser += cof[j] / ++y;
        return -tmp + log(2.5066282746310005 * ser / x);
    }

    static double betaContinuedFraction(double a, double b, double x) {
        const int maxIterations = 200;
        const double epsilon = 1.0e-15;

        double am = 1.0;
        double bm = 1.0;
        double az = 1.0;
        double qab = a + b;
        double qap = a + 1.0;
        double qam = a - 1.0;
        double bz = 1.0 - qab * x / qap;
        double aold = 0.0;
        double em, tem, d, ap, bp, app, bpp;
        int m;

        for (m = 1; m <= maxIterations; m++) {
            em = m;
            tem = em + em;
            d = em * (b - m) * x / ((qam + tem) * (a + tem));
            ap = az + d * am;
            bp = bz + d * bm;
            d = -(a + em) * (qab + em) * x / ((a + tem) * (qap + tem));
            app = ap + d * az;
            bpp = bp + d * bz;
            aold = az;
            am = ap / bpp;
            bm = bp / bpp;
            az = app / bpp;
            bz = 1.0;

            if (fabs(az - aold) < (epsilon * fabs(az)))
                return az;
        }
        return az;
    }

    static double inverseBeta(double a, double b, double q) {
        return 1.0 - incompleteBeta(b, a, q);
    }

    static int binomialCoefficient(int n, int k) {
        if (k < 0 || k > n)
            return 0;
        if (k == 0 || k == n)
            return 1;

        int result = 1;
        if (k > n - k)
            k = n - k;

        for (int i = 0; i < k; ++i) {
            result *= (n - i);
            result /= (i + 1);
        }

        return result;
    }
};
