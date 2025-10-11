#pragma once


// two types of option
enum class OptionType { Call, Put };

class Option {
protected:
    double r;     // Risk Free Intrest Rate
    double S;     // Current Stock Price
    double K;     // Strike Price of Stock
    double T;     // Time to maturity in years
    double sigma; // Volitolity of Stock 

    double delta; // Continous divident from Stock
    double t;     // Time of price of the 
    OptionType type; // The type of option call or put

public:
    // Init the Options with its parameters 
    Option(double S, double K, double r, double sigma, double T, double delta, OptionType type, double t = 0.0);
    virtual ~Option() = default; // way to destroy the object

    virtual double calculatePrice() const = 0; // Abstract method, we will have different ways to price this
    virtual OptionType getType() const; // returns the type of options

private:
    // Each Method to Calculate the Greeks. 
    virtual double calculateDelta() const = 0;
    virtual double calculateGamma() const = 0;
    virtual double calculateTheta() const = 0;
    virtual double calculateVega()  const = 0;
    virtual double calculateRho()   const = 0;
    virtual double calculatePsi()   const = 0;
};