#pragma once
#include "Option.hpp"

class MonteCarloSim : public Option {
    int simulationNum;
public:
    MonteCarloSim(double S, double K, double r, double sigma, double T, double delta, OptionType type, int simulationNum);

    double calculatePrice() const override; // overrides the methods from the options object

    // Methods to calculate the Greeks
    double calculateDelta() const override;
    double calculateGamma() const override;
    double calculateTheta() const override;
    double calculateVega()  const override;
    double calculateRho()   const override;
    double calculatePsi()   const override;

    void printOptionSummary() const;
private:

};

