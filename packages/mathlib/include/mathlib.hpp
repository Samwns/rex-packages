#ifndef MATHLIB_HPP
#define MATHLIB_HPP

namespace mathlib {

/// Returns the sum of two numbers
double add(double a, double b);

/// Returns the difference of two numbers
double sub(double a, double b);

/// Returns the product of two numbers
double mul(double a, double b);

/// Returns the quotient of two numbers
/// @throws std::invalid_argument on division by zero
double div(double a, double b);

/// Returns the absolute value of a number
double abs(double n);

} // namespace mathlib

#endif // MATHLIB_HPP
