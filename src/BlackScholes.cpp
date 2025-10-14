#include "BlackScholes.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <numbers>


static double NormalCDF(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}

static double NormalPDF(double x) {
    // Normal PDF(x) = (1 / sqrt(2*pi)) * (e *(-.5 * x * x))
    return (1 / (sqrt(2 * 3.14159265))) * std::exp(-0.5 * pow(x, 2));
}

BlackScholes::BlackScholes(double S, double K, double r, double sigma, double T, double delta, OptionType type, double t = 0.0)
    : Option(S, K, r, sigma, T, delta, type, t) {
}

double BlackScholes::calculateD1() const {
    double d1 = (std::log(S / K) + (r - delta + pow(sigma, 2) * 0.5) * (T - t)) / (sigma * sqrt(T - t));
    return d1;
}

double BlackScholes::calculateD2() const {
    double d2 = (std::log(S / K) + (r - delta - pow(sigma, 2) * 0.5) * (T - t)) / (sigma * sqrt(T - t));
    return d2;
}

double BlackScholes::calculatePrice() const {

    double d1 = calculateD1();
    double d2 = calculateD2();

    if (type == OptionType::Call) {
        double callPrice = S * std::exp(-delta * (T - t)) * NormalCDF(d1) - K * std::exp(-r * (T - t)) * NormalCDF(d2);
        return callPrice;
    }
    else if (type == OptionType::Put)
    {
        double putPrice = K * std::exp(-r * (T - t)) * NormalCDF(-d2) - S * std::exp(-delta * (T - t)) * NormalCDF(-d1);
        return putPrice;
    }

    return 0;
}

double BlackScholes::calculateDelta() const {

    double optionDelta = (type == OptionType::Call)
        ? exp(-delta * (T - t)) * NormalCDF(calculateD1())
        : -exp(-delta * (T - t)) * NormalCDF(-1 * calculateD1());

    return optionDelta;
}

double BlackScholes::calculateGamma() const {
    // Gamma is same for both Call and Put
    double optionGamma = (exp(-delta * (T - t)) * NormalPDF(calculateD1())) / (sigma * S * sqrt(T - t));
    return optionGamma;
}

double BlackScholes::calculateTheta() const {
    // Little messy, its a long equation so I just brok it down into reusable parts
    double d1 = calculateD1();
    double d2 = calculateD2();

    double a = S * exp(-delta * (T - t));
    double b = (sigma * NormalPDF(d1)) / (2.0 * sqrt(T - t));
    double c = r * K * exp(-r * (T - t));

    double optionTheta = (type == OptionType::Call)
        ? a * (delta * NormalCDF(d1) - b) - (c * NormalCDF(d2))
        : -a * (delta * NormalCDF(-d1) + b) + (c * NormalCDF(-d2));
    return -optionTheta; // Not sure how I keep getting -theta.. so I am just negating
}

double BlackScholes::calculateVega() const {
    // Vega is same for both Call and Put
    double optionVega = S * exp(-delta * (T - t)) * NormalPDF(calculateD1()) * sqrt(T - t);
    return optionVega;
}

double BlackScholes::calculateRho() const {
    double optionRho = (type == OptionType::Call)
        ? K * (T - t) * exp(-r * (T - t)) * NormalCDF(calculateD2())
        : -K * (T - t) * exp(-r * (T - t)) * NormalCDF(-calculateD2());
    return optionRho;
}

double BlackScholes::calculatePsi() const {
    double optionPsi = (type == OptionType::Call)
        ? -(T - t) * S * exp(-delta * (T - t)) * NormalCDF(calculateD1())
        : (T - t) * S * exp(-delta * (T - t)) * NormalCDF(-calculateD1());
    return optionPsi;
}

void BlackScholes::printOptionSummary() const {
    std::cout << std::fixed << std::setprecision(4); // 
    std::cout << "----------------------------------------------\n";
    std::cout << "BLACK SCHOLES EUROPEAN OPTION SUMMARY\n";
    std::cout << "----------------------------------------------\n";
    std::cout << "Type: " << (type == OptionType::Call ? "Call" : "Put") << "\n";
    std::cout << "Spot Price (S): " << S << "\n";
    std::cout << "Strike Price (K): " << K << "\n";
    std::cout << "Risk-Free Rate (r): " << r << "\n";
    std::cout << "Volatility (sigma): " << sigma << "\n";
    std::cout << "Time to Maturity (T): " << T << "\n";
    std::cout << "Continous Dividend Yield (delta): " << delta << "\n";
    std::cout << "Current Time (t): " << t << "\n";
    std::cout << "----------------------------------------------\n";
    std::cout << "OPTION VALUE & GREEKS\n";
    std::cout << "----------------------------------------------\n";
    std::cout << "Value: " << calculatePrice() << "\n";
    std::cout << "Delta: " << calculateDelta() << "\n";
    std::cout << "Gamma: " << calculateGamma() << "\n";
    std::cout << "Theta:  " << calculateTheta() << "\n";
    std::cout << "Vega: " << calculateVega() << "\n";
    std::cout << "Rho:   " << calculateRho() << "\n";
    std::cout << "Psi:   " << calculatePsi() << "\n";
    std::cout << "----------------------------------------\n";
}