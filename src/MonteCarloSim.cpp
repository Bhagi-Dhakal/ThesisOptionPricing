#include "MonteCarloSim.hpp"
#include <iostream>
#include <cmath>
#include <vector> 
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
    return 0.0;
}

double MonteCarloSim::calculateGamma() const {
    return 1.0;
}

double MonteCarloSim::calculateTheta() const {
    return 0.0;
}

double MonteCarloSim::calculateVega() const {
    return 0.0;
}

double MonteCarloSim::calculateRho() const {
    return 0.0;
}

double MonteCarloSim::calculatePsi() const {
    return 0.0;
}