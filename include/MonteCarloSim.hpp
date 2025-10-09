#pragma once
#include "Option.hpp"

class MonteCarloSim : public Option {
    int simulationNum;
public:
    MonteCarloSim(double S, double K, double r, double sigma, double T, double delta, OptionType type, int simulationNum);

    double price() const override; // overides the function from the options object

};

