#include<iostream>
#include <iomanip> 
#include "BlackScholes.hpp"
#include "BinomialTreeModel.hpp"
#include "MonteCarloSim.hpp"


void printSummaryTable(double S, double K, double r, double sigma, double T,
    double delta, double t, int binomialSteps, int NumOfSims) {

    BlackScholes BSFP(S, K, r, sigma, T, delta, OptionType::Put, t);
    BlackScholes BSFC(S, K, r, sigma, T, delta, OptionType::Call, t);

    BinomialTreeModel BTMP(S, K, r, sigma, T, delta, OptionType::Put, binomialSteps);
    BinomialTreeModel BTMC(S, K, r, sigma, T, delta, OptionType::Call, binomialSteps);

    MonteCarloSim MCSP(S, K, r, sigma, T, delta, OptionType::Put, NumOfSims);
    MonteCarloSim MCSC(S, K, r, sigma, T, delta, OptionType::Call, NumOfSims);

    const int labelWidth = 15;
    const int colWidth = 15;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\n" << std::string(100, '=') << "\n";
    std::cout << std::setw(60) << std::right << "OPTION SUMMARY TABLE\n";
    std::cout << std::string(100, '=') << "\n\n";

    // Header row
    std::cout << std::setw(labelWidth) << std::left << " "
        << std::setw(colWidth * 2) << "Black-Scholes Formula"
        << std::setw(colWidth * 2) << "Binomial Tree Model"
        << std::setw(colWidth * 2) << "Monte Carlo Simulation"
        << "\n";

    std::cout << std::setw(labelWidth) << " "
        << std::setw(colWidth) << "Put"
        << std::setw(colWidth) << "Call"
        << std::setw(colWidth) << "Put"
        << std::setw(colWidth) << "Call"
        << std::setw(colWidth) << "Put"
        << std::setw(colWidth) << "Call"
        << "\n";

    std::cout << std::string(100, '-') << "\n";

    auto printRow = [&](const std::string& label,
        double bsfp, double bsfc,
        double btmp, double btmc,
        double mcsp, double mcsc) {
            std::cout << std::setw(labelWidth) << std::left << label
                << std::setw(colWidth) << bsfp
                << std::setw(colWidth) << bsfc
                << std::setw(colWidth) << btmp
                << std::setw(colWidth) << btmc
                << std::setw(colWidth) << mcsp
                << std::setw(colWidth) << mcsc
                << "\n";
        };

    printRow("Price",
        BSFP.calculatePrice(), BSFC.calculatePrice(),
        BTMP.calculatePrice(), BTMC.calculatePrice(),
        MCSP.calculatePrice(), MCSC.calculatePrice());

    printRow("Delta",
        BSFP.calculateDelta(), BSFC.calculateDelta(),
        BTMP.calculateDelta(), BTMC.calculateDelta(),
        MCSP.calculateDelta(), MCSC.calculateDelta());

    printRow("Gamma",
        BSFP.calculateGamma(), BSFC.calculateGamma(),
        BTMP.calculateGamma(), BTMC.calculateGamma(),
        MCSP.calculateGamma(), MCSC.calculateGamma());

    printRow("Theta",
        BSFP.calculateTheta(), BSFC.calculateTheta(),
        BTMP.calculateTheta(), BTMC.calculateTheta(),
        MCSP.calculateTheta(), MCSC.calculateTheta());

    printRow("Vega",
        BSFP.calculateVega(), BSFC.calculateVega(),
        BTMP.calculateVega(), BTMC.calculateVega(),
        MCSP.calculateVega(), MCSC.calculateVega());

    printRow("Rho",
        BSFP.calculateRho(), BSFC.calculateRho(),
        BTMP.calculateRho(), BTMC.calculateRho(),
        MCSP.calculateRho(), MCSC.calculateRho());

    printRow("Psi",
        BSFP.calculatePsi(), BSFC.calculatePsi(),
        BTMP.calculatePsi(), BTMC.calculatePsi(),
        MCSP.calculatePsi(), MCSC.calculatePsi());

    std::cout << std::string(100, '=') << "\n\n";
}