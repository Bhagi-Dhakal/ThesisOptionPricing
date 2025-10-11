#pragma once
#include "Option.hpp"

class BlackScholes : public Option {
public:
    BlackScholes(double S, double K, double r, double sigma, double T, double delta, OptionType type, double t);

    double calculatePrice() const override; // overides the function from the options object

private:
    // Method to calculate D1, D1
    double calculateD1() const;
    double calculateD2() const;

    // Methods to calculate the Greeks
    double calculateDelta() const override;
    double calculateGamma() const override;
    double calculateTheta() const override;
    double calculateVega()  const override;
    double calculateRho()   const override;
    double calculatePsi()   const override;
};

