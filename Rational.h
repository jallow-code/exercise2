// ---------------------------------------------------------
// File: Rational.h
// Arbitrary-precision rational number class using Integer (base 100).
//
// Author: Abdoulie Jallow <Jallow.jku@gmail.com>
// Last Modification: 2025-04-23
//
// Defines Rational with normalization, arithmetic, comparison, and
// I/O. Follows rule of zero; uses Integer for internal storage.
// ---------------------------------------------------------

#ifndef RATIONAL_H
#define RATIONAL_H

#include "Integer.h"
#include <iostream>

// ---------------------------------------------------------
// Class: Rational
// Represents a rational number n/d with arbitrary-precision
// numerator and denominator. Maintains normalized form
// (denominator > 0, gcd = 1) after each operation.
// ---------------------------------------------------------
class Rational
{
private:
    // Numerator (can be negative); default 0
    Integer num = Integer(0LL);

    // Denominator (always positive); default 1
    Integer den = Integer(1LL);

    // -------------------------------------------------------
    // normalize()
    // Ensures denominator > 0, reduces by GCD, adjusts sign.
    // Preconditions: den != 0.
    // Postconditions: gcd(num,den) == 1, den > 0.
    // Effects: may modify num and den.
    // -------------------------------------------------------
    void normalize();

public:
    // -------------------------------------------------------
    // Rational()
    // Default constructs 0/1.
    // -------------------------------------------------------
    Rational() = default;

    // -------------------------------------------------------
    // Rational(n_param,d_param)
    // Construct from numerator and denominator.
    // Preconditions: d_param != 0.
    // Postconditions: object normalized.
    // -------------------------------------------------------
    Rational(Integer n_param, Integer d_param);

    // -------------------------------------------------------
    // Rational(n_param)
    // Construct from Integer as n/1.
    // -------------------------------------------------------
    explicit Rational(Integer n_param);

    // -------------------------------------------------------
    // Rational(n)
    // Construct from built-in integer as n/1.
    // -------------------------------------------------------
    explicit Rational(long long n);

    // -------------------------------------------------------
    // operator<<
    // Output as "num/den" or "num" if den == 1.
    // Effects: writes to os.
    // -------------------------------------------------------
    friend std::ostream &operator<<(std::ostream &os,
                                    const Rational &r);

    // -------------------------------------------------------
    // operator- (unary)
    // Returns negated rational (-num/den).
    // -------------------------------------------------------
    Rational operator-() const;

    // -------------------------------------------------------
    // Arithmetic operators +, -, *, /
    // Input: two Rationals.
    // Preconditions: divisor != 0 for '/'.
    // Postconditions: result normalized.
    // -------------------------------------------------------
    Rational operator+(const Rational &r) const;
    Rational operator-(const Rational &r) const;
    Rational operator*(const Rational &r) const;
    Rational operator/(const Rational &r) const;

    // -------------------------------------------------------
    // Comparison operators ==, !=
    // Compare two rationals in normalized form.
    // -------------------------------------------------------
    bool operator==(const Rational &r) const;
    bool operator!=(const Rational &r) const;

    // -------------------------------------------------------
    // Accessors: numerator() and denominator()
    // -------------------------------------------------------
    const Integer &numerator() const;
    const Integer &denominator() const;
};

#endif // RATIONAL_H
