#include "BlackScholes.hpp"
#include <cmath>
#include<iostream>


// Not Exactly CDF, but approximation of the CDF using Error Function
static double norm_cdf(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}

BlackScholes::BlackScholes(double S, double K, double r, double sigma, double T, double delta, OptionType type, double t = 0.0)
    : Option(S, K, r, sigma, T, delta, type, t)
{
}
double BlackScholes::price() const {
    double d1 = (std::log(S / K) + (r - delta + (sigma * sigma) * 0.5) * (T - t)) / sigma * sqrt(T - t);
    std::cout << "d1: " << d1 << std::endl;
    double d2 = (std::log(S / K) + (r - delta - (sigma * sigma) * 0.5) * (T - t)) / sigma * sqrt(T - t);
    std::cout << "d2: " << d2 << std::endl;

    if (type == OptionType::Call) {
        double callPrice = S * std::exp(-delta * (T - t)) * norm_cdf(d1) - K * std::exp(-r * (T - t)) * norm_cdf(d2);
        return callPrice;
    }
    else if (type == OptionType::Put)
    {
        double putPrice = K * std::exp(-r * (T - t)) * norm_cdf(-d2) - S * std::exp(-delta * (T - t)) * norm_cdf(-d1);
        return putPrice;
    }

    return 0;
}