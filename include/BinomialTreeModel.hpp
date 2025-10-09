#pragma once
#include "Option.hpp"

class BinomialTreeModel : public Option {
    int steps;
public:
    BinomialTreeModel(double S, double K, double r, double sigma, double T, double delta, OptionType type, int steps);

    double price() const override; // overides the function from the options object
private:
    double logCombination(int n, int k) const;
};

