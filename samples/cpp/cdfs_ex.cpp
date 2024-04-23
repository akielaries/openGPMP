#include <iostream>
#include <openGPMP/stats/cdfs.hpp>

int main() {
    double p = 0.7;
    double result_bernoulli = gpmp::stats::CDF::bernoulli(0, p);
    double result_beta = gpmp::stats::CDF::beta(0.5, 2.0, 2.0);
    double result_binomial = gpmp::stats::CDF::binomial(2, 5, p);
    double result_cauchy = gpmp::stats::CDF::cauchy(1.0, 0.0, 1.0);
    double result_chi_squared = gpmp::stats::CDF::chi_squared(3.0, 2.0);
    double result_exponential = gpmp::stats::CDF::exponential(2.0, 0.5);
    double result_f = gpmp::stats::CDF::f(2.0, 2.0, 3.0);
    double result_gamma = gpmp::stats::CDF::gamma(2.0, 2.0, 1.0);
    double result_inverse_gamma =
        gpmp::stats::CDF::inverse_gamma(0.5, 2.0, 1.0);
    double result_inverse_gaussian =
        gpmp::stats::CDF::inverse_gaussian(0.5, 1.0, 2.0);
    double result_laplace = gpmp::stats::CDF::laplace(1.0, 0.0, 1.0);
    double result_logistic = gpmp::stats::CDF::logistic(1.0, 0.0, 1.0);
    double result_log_normal = gpmp::stats::CDF::log_normal(1.0, 0.0, 1.0);
    double result_normal = gpmp::stats::CDF::gaussian(1.0, 0.0, 1.0);
    double result_poisson = gpmp::stats::CDF::poisson(3, 2.0);
    double result_rademacher = gpmp::stats::CDF::rademacher(0.5);
    double result_student_t = gpmp::stats::CDF::student_t(1.0, 2.0);
    double result_uniform = gpmp::stats::CDF::uniform(0.5, 0.0, 1.0);
    double result_weibull = gpmp::stats::CDF::weibull(1.0, 2.0, 1.0);

    return 0;
}
