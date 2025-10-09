#include<iostream>
#include "BlackScholes.hpp"
#include "BinomialTreeModel.hpp"

int main() {
    double r = .0386;
    double delta = 0.0;
    double sigma = .1675;
    double S = 660.0;
    double K = 600.0;
    double T = 1.0;
    double t = 0;

    BlackScholes bs(S, K, r, sigma, T, delta, OptionType::Put, t);
    double bsprice = bs.price();
    std::cout << "Black-Scholes Price: " << bsprice << std::endl;

    BinomialTreeModel bt(S, K, r, sigma, T, delta, OptionType::Put, 10000);
    double btprice = bt.price();
    std::cout << "Binomial Tree Price: " << btprice << std::endl;

    return 0;
}










