#include<iostream>

// Prodotypes 
void printSummaryTable(double S, double K, double r, double sigma, double T,
    double delta, double t, int binomialSteps, int NumOfSims);

int main() {
    double r = .0386;
    double delta = 0.0;
    double sigma = .1675;
    double S = 660.0;
    double K = 600.0;
    double T = 1.0;
    double t = 0;
    int numOfBinomialSteps = 10000;
    int numOfSims = 10000;

    printSummaryTable(S, K, r, sigma, T, delta, t, numOfBinomialSteps, numOfSims);

    return 0;
}










