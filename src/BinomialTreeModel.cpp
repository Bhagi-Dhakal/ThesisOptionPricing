#include "BinomialTreeModel.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>


BinomialTreeModel::BinomialTreeModel
(double S, double K, double r, double sigma, double T, double delta, OptionType type, int steps)
    : Option(S, K, r, sigma, T, delta, type, 0.0), steps(steps)
{
}

double BinomialTreeModel::logCombination(int n, int k) const {
    return std::lgamma(n + 1) - std::lgamma(k + 1) - std::lgamma(n - k + 1);
}

double BinomialTreeModel::calculatePrice() const {
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

double BinomialTreeModel::calculateDelta() const {
    // Using the First order Central Finite Difference Formula for Delta
    double dS = S * 0.005; // 0.5% of current Stock Price
    double upPrice = BinomialTreeModel(S + dS, K, r, sigma, T, delta, type, steps).calculatePrice();
    double downPrice = BinomialTreeModel(S - dS, K, r, sigma, T, delta, type, steps).calculatePrice();
    double optionDelta = (upPrice - downPrice) / (2 * dS);
    return optionDelta;
}

double BinomialTreeModel::calculateGamma() const {
    // Using the Second order Central Finite Difference Formula for Delta
    double dS = S * 0.005; // 0.5% of current Stock Price
    double upPrice = BinomialTreeModel(S + dS, K, r, sigma, T, delta, type, steps).calculatePrice();
    double currentPrice = calculatePrice();
    double downPrice = BinomialTreeModel(S - dS, K, r, sigma, T, delta, type, steps).calculatePrice();
    double optionGamma = (upPrice - 2 * currentPrice + downPrice) / (dS * dS);
    return optionGamma;
}

double BinomialTreeModel::calculateTheta() const {
    double dT = 1.0 / 365.0; // Change by 1 day
    double upPrice = BinomialTreeModel(S, K, r, sigma, T + dT, delta, type, steps).calculatePrice();
    double downPrice = BinomialTreeModel(S, K, r, sigma, T - dT, delta, type, steps).calculatePrice();
    double optionTheta = (upPrice - downPrice) / (2 * dT);
    return optionTheta;
}

double BinomialTreeModel::calculateVega() const {
    double dSigma = sigma * 0.005; // 0.5%  of current sigma
    double upPrice = BinomialTreeModel(S, K, r, sigma + dSigma, T, delta, type, steps).calculatePrice();
    double downPrice = BinomialTreeModel(S, K, r, sigma - dSigma, T, delta, type, steps).calculatePrice();
    double optionVega = (upPrice - downPrice) / (2 * dSigma);
    return optionVega;
}

double BinomialTreeModel::calculateRho() const {
    double dr = r * 0.005; // 0.5%  of current r
    double upPrice = BinomialTreeModel(S, K, r + dr, sigma, T, delta, type, steps).calculatePrice();
    double downPrice = BinomialTreeModel(S, K, r - dr, sigma, T, delta, type, steps).calculatePrice();
    double optionRho = (upPrice - downPrice) / (2 * dr);
    return optionRho;
}

double BinomialTreeModel::calculatePsi() const {
    double ddelta = delta * 0.005; // 0.5%  of current delta
    double upPrice = BinomialTreeModel(S, K, r, sigma, T, delta + ddelta, type, steps).calculatePrice();
    double downPrice = BinomialTreeModel(S, K, r, sigma, T, delta - ddelta, type, steps).calculatePrice();
    double optionPsi = (upPrice - downPrice) / (2 * ddelta);
    return optionPsi;
}


void BinomialTreeModel::printOptionSummary() const {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "----------------------------------------------\n";
    std::cout << "BINOMIAL TREE MODEL EUROPEAN OPTION SUMMARY\n";
    std::cout << "----------------------------------------------\n";
    std::cout << "Type: " << (type == OptionType::Call ? "Call" : "Put") << "\n";
    std::cout << "Spot Price (S): " << S << "\n";
    std::cout << "Strike Price (K): " << K << "\n";
    std::cout << "Risk-Free Rate (r): " << r << "\n";
    std::cout << "Volatility (sigma): " << sigma << "\n";
    std::cout << "Time to Maturity (T): " << T << "\n";
    std::cout << "Continous Dividend Yield (delta): " << delta << "\n";
    std::cout << "Number of time Steps (steps): " << steps << "\n";
    std::cout << "----------------------------------------------\n";
    std::cout << "OPTION VALUE & GREEKS\n";
    std::cout << "----------------------------------------------\n";
    std::cout << "Value: " << calculatePrice() << "\n";
    std::cout << "Delta: " << calculateDelta() << "\n";
    std::cout << "Gamma: " << calculateGamma() << "\n";
    std::cout << "Theta:  " << calculateTheta() << "\n";
    std::cout << "Vega: " << calculateVega() << "\n";
    std::cout << "Rho:   " << calculateRho() << "\n";
    std::cout << "Psi:   " << calculatePsi() << "\n";
    std::cout << "----------------------------------------\n";
}