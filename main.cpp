#include<iostream>
#include "BlackScholes.hpp"


int main() {
    double r = .0386;
    double delta = 0.0;
    double sigma = .1675;
    double S = 660.0;
    double K = 600.0;
    double T = 1.0;
    double t = 0;

    BlackScholes bs(S, K, r, sigma, T, delta, OptionType::Put, t);
    double price = bs.price();

    std::cout << "Black-Scholes Price: " << price << std::endl;
    return 0;
}










