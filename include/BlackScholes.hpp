#pragma once
#include "Option.hpp"

class BlackScholes : public Option {
public:
    BlackScholes(double S, double K, double r, double sigma, double T, double delta, OptionType type, double t);

    double price() const override; // overides the function from the options object
};

