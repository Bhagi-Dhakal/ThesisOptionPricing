#include "BinomialTreeModel.hpp"
#include <cmath>
#include <iostream>



BinomialTreeModel::BinomialTreeModel
(double S, double K, double r, double sigma, double T, double delta, OptionType type, int steps)
    : Option(S, K, r, sigma, T, delta, type, 0.0), steps(steps)
{
}

double BinomialTreeModel::logCombination(int n, int k) const {
    return std::lgamma(n + 1) - std::lgamma(k + 1) - std::lgamma(n - k + 1);
}

double BinomialTreeModel::price() const {
    /*
        Binomial Tree Model Formmula:
        C(S,K) = e^(rnt) * sum(k = 0, n: ([combnations(n,k)]  * (p*)^k * (1-p*)^(n-k) * max{u^k * d^(n-k) * S - K, 0})
    */

    double price = 0.0;

    double t = T / steps; // steps = n
    double discount = exp(-r * T);
    //double forwardPrice = S * exp((r - delta) * t);
    double u = exp(sigma * sqrt(t));
    double d = exp(-sigma * sqrt(t));
    double pstar = (exp((r - delta) * t) - d) / (u - d);


    for (int k = 0; k <= steps; ++k) {
        /*
            [combnations(n,k)] = n! / (k! * (n - k)!) blows up really fast,
            (p*)^k blows up really fast, (1-p*)^(n-k) goes to 0 really fast, becomes tiny
            and when we mulltiple all this its pure Chaos.

            Better approch: Take logs of this portions of the equations
            Let A = [combnations(n,k)]  * (p*)^k * (1-p*)^(n-k)
                log(A) = log([combnations(n,k)]) + k * log(p*) + (n-k) * log(1-p*) = B, {Product becomes a sum, do calc here}
                exp(log(A)) = A {Exponentiate to get rid of log. }
        */
        double logProbablity = logCombination(steps, k) + k * log(pstar) + (steps - k) * log(1.0 - pstar);
        double probablity = exp(logProbablity);

        // node has k up movements, steps - k down movements
        double Stock = S * pow(u, k) * pow(d, steps - k);

        double payoff = (type == OptionType::Call)
            ? std::max(Stock - K, 0.0) // call payoff
            : std::max(K - Stock, 0.0); // put payoff

        price += probablity * payoff;
    }
    price *= discount;
    return price;
}