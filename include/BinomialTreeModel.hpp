#pragma once
#include "Option.hpp"

class BinomialTreeModel : public Option {
    int steps;
public:
    BinomialTreeModel(double S, double K, double r, double sigma, double T, double delta, OptionType type, int steps);

    double calculatePrice() const override; // overides the function from the options object

    // Methods to calculate the Greeks
    double calculateDelta() const override;
    double calculateGamma() const override;
    double calculateTheta() const override;
    double calculateVega()  const override;
    double calculateRho()   const override;
    double calculatePsi()   const override;


    void printOptionSummary() const;

private:
    // Other Helpful Methods 
    double logCombination(int n, int k) const;
};

