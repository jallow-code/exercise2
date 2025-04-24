// ---------------------------------------------------------
// File: Rational.cpp
// Implementation of arbitrary-precision rational numbers
// using Integer (base-100 digits).
//
// Author: Abdoulie <Jallow.jku@gmail.com>
// Last Modification: 2025-04-23
//
// Implements normalization, constructors, I/O, arithmetic,
// comparison, and accessors for Rational class.
// ---------------------------------------------------------

#include "Rational.h"
#include <stdexcept> // for std::runtime_error
#include <cstdlib>   // for exit()

// ---------------------------------------------------------
// normalize()
// Ensures denominator > 0 and canonical zero form.
// Preconditions: den != 0.
// Postconditions: den > 0; if num == 0, den == 1.
// Effects: may modify num and den.
// ---------------------------------------------------------
void Rational::normalize()
{
    // Make denominator positive
    if (den.isNegative())
    {
        num = -num;
        den = -den;
    }

    // Canonical zero: 0/1
    if (num.isZero())
    {
        den = Integer(1LL);
    }
}

// ---------------------------------------------------------
// Rational(n_param, d_param)
// Construct from numerator and denominator.
// Preconditions: d_param != 0.
// Postconditions: object normalized.
// Effects: may abort on zero denominator.
// ---------------------------------------------------------
Rational::Rational(Integer n_param, Integer d_param)
    : num(std::move(n_param)), den(std::move(d_param))
{
    if (den.isZero())
    {
        std::cerr << "Error: Rational denominator cannot be zero." << std::endl;
        exit(EXIT_FAILURE);
    }
    normalize();
}

// ---------------------------------------------------------
// Rational(n_param)
// Construct from Integer as n/1.
// Postconditions: object normalized.
// ---------------------------------------------------------
Rational::Rational(Integer n_param)
    : num(std::move(n_param)), den(1LL)
{
    normalize();
}

// ---------------------------------------------------------
// Rational(n)
// Construct from built-in integer as n/1.
// Postconditions: object normalized.
// ---------------------------------------------------------
Rational::Rational(long long n)
    : num(n), den(1LL)
{
    normalize();
}

// ---------------------------------------------------------
// operator<<
// Output rational as "num/den" or "num" if den == 1.
// Effects: writes to stream.
// ---------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const Rational &r)
{
    os << r.num;
    if (r.den != Integer(1LL))
    {
        os << "/" << r.den;
    }
    return os;
}

// ---------------------------------------------------------
// operator- (unary)
// Returns negated rational (-num/den).
// Postconditions: result normalized.
// ---------------------------------------------------------
Rational Rational::operator-() const
{
    Rational result = *this;
    result.num = -result.num;
    result.normalize();
    return result;
}

// ---------------------------------------------------------
// operator+
// Adds two rationals: a/b + c/d = (ad + bc)/bd.
// Postconditions: result normalized.
// ---------------------------------------------------------
Rational Rational::operator+(const Rational &r) const
{
    Integer new_num = (num * r.den) + (den * r.num);
    Integer new_den = den * r.den;
    return Rational(std::move(new_num), std::move(new_den));
}

// ---------------------------------------------------------
// operator-
// Subtracts two rationals: a/b - c/d = (ad - bc)/bd.
// Postconditions: result normalized.
// ---------------------------------------------------------
Rational Rational::operator-(const Rational &r) const
{
    Integer new_num = (num * r.den) - (den * r.num);
    Integer new_den = den * r.den;
    return Rational(std::move(new_num), std::move(new_den));
}

// ---------------------------------------------------------
// operator*
// Multiplies: a/b * c/d = (ac)/(bd).
// Postconditions: result normalized.
// ---------------------------------------------------------
Rational Rational::operator*(const Rational &r) const
{
    Integer new_num = num * r.num;
    Integer new_den = den * r.den;
    return Rational(std::move(new_num), std::move(new_den));
}

// ---------------------------------------------------------
// operator/
// Divides: (a/b) / (c/d) = (ad)/(bc).
// Preconditions: r.num != 0.
// Postconditions: result normalized.
// Effects: may abort on division by zero.
// ---------------------------------------------------------
Rational Rational::operator/(const Rational &r) const
{
    if (r.num.isZero())
    {
        std::cerr << "Error: Division by zero rational number." << std::endl;
        exit(EXIT_FAILURE);
    }
    Integer new_num = num * r.den;
    Integer new_den = den * r.num;
    return Rational(std::move(new_num), std::move(new_den));
}

// ---------------------------------------------------------
// operator==
// Compares two rationals: a/b == c/d <=> ad == bc.
// ---------------------------------------------------------
bool Rational::operator==(const Rational &r) const
{
    return (num * r.den) == (den * r.num);
}

// ---------------------------------------------------------
// operator!=
// Logical negation of ==.
// ---------------------------------------------------------
bool Rational::operator!=(const Rational &r) const
{
    return !(*this == r);
}

// ---------------------------------------------------------
// numerator()
// Returns numerator.
// ---------------------------------------------------------
const Integer &Rational::numerator() const { return num; }

// ---------------------------------------------------------
// denominator()
// Returns denominator.
// ---------------------------------------------------------
const Integer &Rational::denominator() const { return den; }