#pragma once
#include "Option.hpp"

class MonteCarloSim : public Option {
    int simulationNum;
public:
    MonteCarloSim(double S, double K, double r, double sigma, double T, double delta, OptionType type, int simulationNum);

    double calculatePrice() const override; // overides the function from the options object
private:
    // Methods to calculate the Greeks
    // Methods to calculate the Greeks
    double calculateDelta() const override;
    double calculateGamma() const override;
    double calculateTheta() const override;
    double calculateVega()  const override;
    double calculateRho()   const override;
    double calculatePsi()   const override;
};

