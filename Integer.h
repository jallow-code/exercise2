/***************************************************************************
 * File: Integer.h
 * Header file for the Integer class, representing arbitrary-precision
 * signed integers with basic arithmetic and comparison operations.
 *
 * Author: Abdoulie Jallow <Jallow.jku@gmail.com>
 * Last Modification: 2025-04-23
 **************************************************************************/



#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
#include <vector>
#include <string>

// ---------------------------------------------------------
// DigitType and BASE
// DigitType: holds a single base-100 digit (0..99).
// BASE: numeric base for each digit slot.
// ---------------------------------------------------------
using DigitType = unsigned char;  // 0..99
const int BASE = 100;             // base for each digit

// ---------------------------------------------------------
// Class: Integer
// Represents a signed arbitrary-precision integer. Digits are
// stored least-significant first in a vector of base-100 slots.
// Supports construction from built-in types, I/O, comparison,
// addition, subtraction, multiplication, and utility methods.
// ---------------------------------------------------------
class Integer
{
private:
  // sign == true indicates negative value; false indicates non-
  // negative (zero or positive).
  bool sign = false;

  // digits[i] holds the i-th base-100 digit; empty vector means 0.
  std::vector<DigitType> digits;

  // -------------------------------------------------------
  // normalize()
  // Input condition: none (internal use).
  // Output condition: no leading zero digits in `digits`;
  //   if value is zero, digits.empty() or digits == {0} and sign==false.
  // Effect: adjusts vector and sign to canonical form.
  // -------------------------------------------------------
  void normalize();

  // Static helpers for magnitude arithmetic (unsigned)
  // -------------------------------------------------------
  // addMagnitude(a,b)
  // Returns: |a| + |b| as a new Integer (sign==false).
  // Preconditions: a,digits and b.digits valid.
  // -------------------------------------------------------
  static Integer addMagnitude(const Integer &a, const Integer &b);

  // -------------------------------------------------------
  // subtractMagnitude(a,b)
  // Returns: |a| - |b|, requires |a| >= |b|.
  // Preconditions: compareMagnitude(a,b) >= 0.
  // -------------------------------------------------------
  static Integer subtractMagnitude(const Integer &a, const Integer &b);

  // -------------------------------------------------------
  // compareMagnitude(a,b)
  // Returns: negative if |a|<|b|, zero if |a|==|b|,
  //   positive if |a|>|b|.
  // -------------------------------------------------------
  static int compareMagnitude(const Integer &a,
                              const Integer &b);

public:
  // -------------------------------------------------------
  // Integer()
  // Default constructor: creates value 0.
  // -------------------------------------------------------
  Integer() = default;

  // -------------------------------------------------------
  // Integer(i)
  // Construct from built-in integer.
  // Input: any long long value.
  // Output: equivalent Integer value.
  // -------------------------------------------------------
  Integer(long long i);

  // -------------------------------------------------------
  // Integer(s,n,d)
  // Construct from sign s and C-array of n digits (base 100).
  // Input: d[0..n-1] each in 0..99.
  // Output: Integer value with given magnitude and sign.
  // -------------------------------------------------------
  Integer(bool s, int n, const char *d);

  // -------------------------------------------------------
  // Integer(s,d_vec)
  // Construct from sign s and digit vector.
  // Takes ownership of rvalue vector or copies lvalue.
  // -------------------------------------------------------
  Integer(bool s, std::vector<DigitType> d_vec);

  // -------------------------------------------------------
  // operator<<
  // Output integer in decimal to stream.
  // Preconditions: none.
  // Effects: writes textual representation to os.
  // -------------------------------------------------------
  friend std::ostream &operator<<(std::ostream &os,
                                  const Integer &i);

  // -------------------------------------------------------
  // operator- (unary)
  // Returns negated value.
  // -------------------------------------------------------
  Integer operator-() const;

  // -------------------------------------------------------
  // operator+,-,*
  // Arithmetic on Integer values.
  // Input: two Integer operands.
  // Output: result of addition, subtraction, multiplication.
  // -------------------------------------------------------
  Integer operator+(const Integer &i) const;
  Integer operator-(const Integer &i) const;
  Integer operator*(const Integer &i) const;

  // -------------------------------------------------------
  // Comparison operators
  // Compare Integer values.
  // -------------------------------------------------------
  bool operator==(const Integer &i) const;
  bool operator!=(const Integer &i) const;
  bool operator<(const Integer &i) const;
  bool operator>(const Integer &i) const;
  bool operator<=(const Integer &i) const;
  bool operator>=(const Integer &i) const;

  // -------------------------------------------------------
  // isZero(), isNegative()
  // Query properties.
  // -------------------------------------------------------
  bool isZero() const;
  bool isNegative() const;

  // -------------------------------------------------------
  // signum()
  // Returns -1, 0, or 1 depending on sign of value.
  // -------------------------------------------------------
  int signum() const;

  // -------------------------------------------------------
  // abs()
  // Returns absolute value.
  // -------------------------------------------------------
  Integer abs() const;
};

#endif // INTEGER_H
