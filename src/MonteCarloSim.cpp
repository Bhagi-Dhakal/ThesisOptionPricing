#include "MonteCarloSim.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <random>




MonteCarloSim::MonteCarloSim
(double S, double K, double r, double sigma, double T, double delta, OptionType type, int simulationNum)
    : Option(S, K, r, sigma, T, delta, type, 0.0), simulationNum(simulationNum)
{
}

double MonteCarloSim::calculatePrice() const {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    double presentValue = exp(-r * T);
    double stock = S * exp(r - delta - (pow(sigma, 2) / 2));
    double std = sigma * sqrt(T);

    double sum = 0.0;
    for (int i = 0; i <= simulationNum; ++i) {
        double stockPrice = stock * exp(std * distribution(generator));

        double payoff = (type == OptionType::Call)
            ? std::max(stockPrice - K, 0.0)
            : std::max(K - stockPrice, 0.0);

        sum += payoff;
    }
    return presentValue * (sum / simulationNum);
}

double MonteCarloSim::calculateDelta() const {
    double dS = S * 0.005; // 0.5% of current Stock Price
    double upPrice = MonteCarloSim(S + dS, K, r, sigma, T, delta, type, simulationNum).calculatePrice();
    double downPrice = MonteCarloSim(S - dS, K, r, sigma, T, delta, type, simulationNum).calculatePrice();
    double optionDelta = (upPrice - downPrice) / (2 * dS);
    return optionDelta;
}

double MonteCarloSim::calculateGamma() const {
    double dS = S * 0.005; // 0.5% of current Stock Price
    double upPrice = MonteCarloSim(S + dS, K, r, sigma, T, delta, type, simulationNum).calculatePrice();
    double currentPrice = calculatePrice();
    double downPrice = MonteCarloSim(S - dS, K, r, sigma, T, delta, type, simulationNum).calculatePrice();
    double optionGamma = (upPrice - 2 * currentPrice + downPrice) / (dS * dS);
    return optionGamma;
}

double MonteCarloSim::calculateTheta() const {
    double dT = 1.0 / 365.0; // Change by 1 day
    double upPrice = MonteCarloSim(S, K, r, sigma, T + dT, delta, type, simulationNum).calculatePrice();
    double downPrice = MonteCarloSim(S, K, r, sigma, T - dT, delta, type, simulationNum).calculatePrice();
    double optionTheta = (upPrice - downPrice) / (2 * dT);
    return optionTheta;
}

double MonteCarloSim::calculateVega() const {
    double dSigma = sigma * 0.005; // 0.5%  of current sigma
    double upPrice = MonteCarloSim(S, K, r, sigma + dSigma, T, delta, type, simulationNum).calculatePrice();
    double downPrice = MonteCarloSim(S, K, r, sigma - dSigma, T, delta, type, simulationNum).calculatePrice();
    double optionVega = (upPrice - downPrice) / (2 * dSigma);
    return optionVega;
}

double MonteCarloSim::calculateRho() const {
    double dr = r * 0.005; // 0.5%  of current r
    double upPrice = MonteCarloSim(S, K, r + dr, sigma, T, delta, type, simulationNum).calculatePrice();
    double downPrice = MonteCarloSim(S, K, r - dr, sigma, T, delta, type, simulationNum).calculatePrice();
    double optionRho = (upPrice - downPrice) / (2 * dr);
    return optionRho;
}

double MonteCarloSim::calculatePsi() const {
    double ddelta = delta * 0.005; // 0.5%  of current delta
    double upPrice = MonteCarloSim(S, K, r, sigma, T, delta + ddelta, type, simulationNum).calculatePrice();
    double downPrice = MonteCarloSim(S, K, r, sigma, T, delta - ddelta, type, simulationNum).calculatePrice();
    double optionPsi = (upPrice - downPrice) / (2 * ddelta);
    return optionPsi;
}

void MonteCarloSim::printOptionSummary() const {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "----------------------------------------------\n";
    std::cout << "MONTE CARLO SIM EUROPEAN OPTION SUMMARY\n";
    std::cout << "----------------------------------------------\n";
    std::cout << "Type: " << (type == OptionType::Call ? "Call" : "Put") << "\n";
    std::cout << "Spot Price (S): " << S << "\n";
    std::cout << "Strike Price (K): " << K << "\n";
    std::cout << "Risk-Free Rate (r): " << r << "\n";
    std::cout << "Volatility (sigma): " << sigma << "\n";
    std::cout << "Time to Maturity (T): " << T << "\n";
    std::cout << "Continous Dividend Yield (delta): " << delta << "\n";
    std::cout << "Number of Simulations (n): " << simulationNum << "\n";
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