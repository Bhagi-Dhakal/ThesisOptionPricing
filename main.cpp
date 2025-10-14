#include<iostream>
#include "BlackScholes.hpp"
#include "BinomialTreeModel.hpp"
#include "MonteCarloSim.hpp"


int main() {
    double r = .0386;
    double delta = 0.021;
    double sigma = .1675;
    double S = 660.0;
    double K = 600.0;
    double T = 1.0;
    double t = 0;

    std::cout << std::endl;
    BlackScholes bs(S, K, r, sigma, T, delta, OptionType::Put, t);

    BinomialTreeModel bt(S, K, r, sigma, T, delta, OptionType::Put, 10000);

    //MonteCarloSim mc(S, K, r, sigma, T, delta, OptionType::Put, 10000);

    bs.printOptionSummary();
    bt.printOptionSummary();

    return 0;
}










