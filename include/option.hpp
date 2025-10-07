#pragma once
#include <string>


// two types of option
enum class OptionType { call, put };

class Option {
private:
    double r;     // Risk Free Intrest Rate
    double S;     // Current Stock Price
    double K;     // Strike Price of Stock
    double T;     // Time to maturity in years
    double sigma; // Volitolity of Stock 

    double delta; // Continous divident from Stock
    double t;     // Time of price of the 

};