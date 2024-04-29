#include <iostream>
#include <openGPMP/stats/pdfs.hpp>

int main() {
    // Testing the PDF class methods
    std::cout << "Bernoulli CDF at x=1, p=0.5: "
              << gpmp::stats::PDF::bernoulli(1, 0.5) << std::endl;
    std::cout << "Beta PDF at x=0.5, alpha=2, beta=2: "
              << gpmp::stats::PDF::beta(0.5, 2, 2) << std::endl;
    std::cout << "Binomial PDF at k=2, n=5, p=0.5: "
              << gpmp::stats::PDF::binomial(2, 5, 0.5) << std::endl;
    std::cout << "Cauchy PDF at x=0, x0=0, gamma=1: "
              << gpmp::stats::PDF::cauchy(0, 0, 1) << std::endl;
    std::cout << "Chi-squared PDF at x=2, k=3: "
              << gpmp::stats::PDF::chi_squared(2, 3) << std::endl;
    std::cout << "Exponential PDF at x=1, lambda=0.5: "
              << gpmp::stats::PDF::exponential(1, 0.5) << std::endl;
    std::cout << "F Distribution PDF at x=1, df1=2, df2=3: "
              << gpmp::stats::PDF::f_dist(1, 2, 3) << std::endl;
    std::cout << "Gamma PDF at x=2, alpha=2, beta=0.5: "
              << gpmp::stats::PDF::gamma(2, 2, 0.5) << std::endl;
    std::cout << "Inverse-Gamma PDF at x=1, alpha=2, beta=0.5: "
              << gpmp::stats::PDF::inverse_gamma(1, 2, 0.5) << std::endl;
    std::cout << "Inverse-Gaussian PDF at x=1, mu=2, lambda=0.5: "
              << gpmp::stats::PDF::inverse_gaussian(1, 2, 0.5) << std::endl;
    std::cout << "Laplace PDF at x=1, mu=0, b=1: "
              << gpmp::stats::PDF::laplace(1, 0, 1) << std::endl;
    std::cout << "Logistic PDF at x=1, mu=0, s=1: "
              << gpmp::stats::PDF::logistic(1, 0, 1) << std::endl;
    std::cout << "Log-Normal PDF at x=2, mu=1, sigma=0.5: "
              << gpmp::stats::PDF::log_normal(2, 1, 0.5) << std::endl;
    std::cout << "Gaussian PDF at x=1, mu=0, sigma=1: "
              << gpmp::stats::PDF::gaussian(1, 0, 1) << std::endl;
    std::cout << "Poisson PDF at k=2, lambda=1: "
              << gpmp::stats::PDF::poisson(2, 1) << std::endl;
    std::cout << "Rademacher PDF at k=1: " << gpmp::stats::PDF::rademacher(1)
              << std::endl;
    std::cout << "Student's t PDF at x=1, df=2: "
              << gpmp::stats::PDF::student_t(1, 2) << std::endl;
    std::cout << "Uniform PDF at x=1, a=0, b=2: "
              << gpmp::stats::PDF::uniform(1, 0, 2) << std::endl;
    std::cout << "Weibull PDF at x=2, k=2, lambda=1: "
              << gpmp::stats::PDF::weibull(2, 2, 1) << std::endl;

    return 0;
}
