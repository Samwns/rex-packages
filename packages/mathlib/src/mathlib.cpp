#include "mathlib.hpp"
#include <cmath>
#include <stdexcept>

namespace mathlib {

double add(double a, double b) {
    return a + b;
}

double sub(double a, double b) {
    return a - b;
}

double mul(double a, double b) {
    return a * b;
}

double div(double a, double b) {
    if (std::fpclassify(b) == FP_ZERO) {
        throw std::invalid_argument("mathlib::div: division by zero");
    }
    return a / b;
}

double abs(double n) {
    return n < 0.0 ? -n : n;
}

} // namespace mathlib
