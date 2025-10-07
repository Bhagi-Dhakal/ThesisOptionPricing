#include "Option.hpp"

Option::Option(double S, double K, double r, double sigma, double T, double delta, OptionType type, double t)
    : S(S), K(K), r(r), sigma(sigma), T(T), delta(delta), type(type), t(t)
{
}


OptionType Option::getType() const {
    return type;
}
