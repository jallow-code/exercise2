// ---------------------------------------------------------
// File: Integer.cpp
// Implementation of arbitrary-precision signed integers using
// base-100 digits stored in std::vector<DigitType>.
//
// Author: Abdoulie Jallow <Jallow.jku@gmail.com>
// Last Modification: 2025-04-23
//
// Provides normalization, comparison, arithmetic, and I/O
// for Integer class following rule-of-zero and common style.
// ---------------------------------------------------------

#include "Integer.h"
#include <vector>
#include <stdexcept>  // for std::invalid_argument
#include <algorithm>  // for std::max, std::reverse
#include <iomanip>    // for std::setw, std::setfill
#include <cmath>      // for std::abs
#include <limits>     // for numeric_limits

// ---------------------------------------------------------
// normalize()
// Remove leading zeros, ensure canonical zero form.
// Postconditions: no trailing zeros in digits; empty means 0.
// Effects: may clear digits and reset sign.
// ---------------------------------------------------------
void Integer::normalize()
{
  while (digits.size() > 1 && digits.back() == 0)
  {
    digits.pop_back();
  }

  if (digits.empty() || (digits.size() == 1 && digits[0] == 0))
  {
    digits.clear();  // canonical zero
    sign = false;    // zero is non-negative
  }

  if (digits.empty())
  {
    sign = false;    // enforce non-negative zero
  }
}

// ---------------------------------------------------------
// compareMagnitude(a,b)
// Compare |a| and |b|.
// Returns negative if |a|<|b|, zero if equal, positive if |a|>|b|.
// ---------------------------------------------------------
int Integer::compareMagnitude(const Integer &a,
                              const Integer &b)
{
  if (a.digits.size() < b.digits.size())
    return -1;
  if (a.digits.size() > b.digits.size())
    return 1;
  if (a.digits.empty())
    return 0;  // both zero

  for (int i = static_cast<int>(a.digits.size()) - 1; i >= 0; --i)
  {
    if (a.digits[i] < b.digits[i])
      return -1;
    if (a.digits[i] > b.digits[i])
      return 1;
  }
  return 0;
}

// ---------------------------------------------------------
// addMagnitude(a,b)
// Compute |a|+|b|, result.sign=false.
// ---------------------------------------------------------
Integer Integer::addMagnitude(const Integer &a,
                              const Integer &b)
{
  const auto &d1 = a.digits;
  const auto &d2 = b.digits;
  size_t n1 = d1.size(), n2 = d2.size();
  size_t m = std::max(n1, n2);

  std::vector<DigitType> res;
  res.reserve(m + 1);
  int carry = 0;

  for (size_t i = 0; i < m; ++i)
  {
    int sum = carry;
    if (i < n1) sum += d1[i];
    if (i < n2) sum += d2[i];
    res.push_back(static_cast<DigitType>(sum % BASE));
    carry = sum / BASE;
  }
  if (carry > 0)
    res.push_back(static_cast<DigitType>(carry));

  Integer result(false, std::move(res));
  result.normalize();
  return result;
}

// ---------------------------------------------------------
// subtractMagnitude(a,b)
// Compute |a|-|b|, assumes |a|>=|b|. result.sign=false.
// ---------------------------------------------------------
Integer Integer::subtractMagnitude(const Integer &a,
                                   const Integer &b)
{
  const auto &d1 = a.digits;
  const auto &d2 = b.digits;
  size_t n1 = d1.size(), n2 = d2.size();

  std::vector<DigitType> res;
  res.reserve(n1);
  int borrow = 0;

  for (size_t i = 0; i < n1; ++i)
  {
    int diff = d1[i] - borrow;
    if (i < n2) diff -= d2[i];
    if (diff < 0)
    {
      diff += BASE;
      borrow = 1;
    }
    else
    {
      borrow = 0;
    }
    res.push_back(static_cast<DigitType>(diff));
  }

  Integer result(false, std::move(res));
  result.normalize();
  return result;
}

// ---------------------------------------------------------
// Integer(i)
// Construct from built-in long long.
// ---------------------------------------------------------
Integer::Integer(long long i)
  : sign(i < 0)
{
  if (i == 0)
    return;

  unsigned long long v;
  if (i == std::numeric_limits<long long>::min())
  {
    v = static_cast<unsigned long long>(
          std::numeric_limits<long long>::max()) + 1;
  }
  else
  {
    v = std::abs(i);
  }

  while (v > 0)
  {
    digits.push_back(static_cast<DigitType>(v % BASE));
    v /= BASE;
  }
}

// ---------------------------------------------------------
// Integer(s,n,d)
// Construct from sign and C-array of digits (kept for compatibility).
// ---------------------------------------------------------
Integer::Integer(bool s, int n, const char *d)
  : sign(s)
{
  if (n <= 0 || d == nullptr)
  {
    sign = false;
    return;
  }

  int m = n;
  while (m > 1 && d[m-1] == 0)
    --m;

  if (m == 1 && d[0] == 0)
  {
    sign = false;
    return;
  }

  digits.reserve(m);
  for (int i = 0; i < m; ++i)
  {
    if (static_cast<unsigned char>(d[i]) >= BASE || d[i] < 0)
      throw std::invalid_argument(
        "Invalid digit in char* constructor");
    digits.push_back(static_cast<DigitType>(d[i]));
  }
  normalize();
}

// ---------------------------------------------------------
// Integer(s,d_vec)
// Construct from sign and digit vector.
// ---------------------------------------------------------
Integer::Integer(bool s, std::vector<DigitType> d_vec)
  : sign(s), digits(std::move(d_vec))
{
  for (auto dig : digits)
    if (dig >= BASE)
      throw std::invalid_argument(
        "Invalid digit in vector constructor");
  normalize();
}

// ---------------------------------------------------------
// operator<<
// Output decimal representation.
// ---------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const Integer &i)
{
  if (i.isZero())
  {
    os << "0";
    return os;
  }

  if (i.sign)
    os << "-";

  os << static_cast<int>(i.digits.back());
  for (int j = static_cast<int>(i.digits.size()) - 2; j >= 0; --j)
  {
    os << std::setw(2) << std::setfill('0')
       << static_cast<int>(i.digits[j]);
  }
  os << std::setfill(' ');
  return os;
}

// ---------------------------------------------------------
// operator- (unary)
// Negate integer; -0 yields 0.
// ---------------------------------------------------------
Integer Integer::operator-() const
{
  if (isZero())
    return *this;
  Integer r = *this;
  r.sign = !r.sign;
  return r;
}

// ---------------------------------------------------------
// operator+
// Addition with sign handling.
// ---------------------------------------------------------
Integer Integer::operator+(const Integer &rhs) const
{
  if (sign == rhs.sign)
  {
    Integer r = addMagnitude(*this, rhs);
    r.sign = sign;
    r.normalize();
    return r;
  }

  int cmp = compareMagnitude(*this, rhs);
  if (cmp == 0)
    return Integer();
  if (cmp > 0)
  {
    Integer r = subtractMagnitude(*this, rhs);
    r.sign = sign;
    r.normalize();
    return r;
  }
  Integer r = subtractMagnitude(rhs, *this);
  r.sign = rhs.sign;
  r.normalize();
  return r;
}

// ---------------------------------------------------------
// operator-
// Subtraction via addition of negation.
// ---------------------------------------------------------
Integer Integer::operator-(const Integer &rhs) const
{
  return *this + (-rhs);
}

// ---------------------------------------------------------
// operator*
// Multiplication (schoolbook) with sign.
// ---------------------------------------------------------
Integer Integer::operator*(const Integer &rhs) const
{
  if (isZero() || rhs.isZero())
    return Integer();

  bool rs = (sign != rhs.sign);
  size_t n1 = digits.size(), n2 = rhs.digits.size();
  std::vector<int> tmp(n1 + n2, 0);

  for (size_t i = 0; i < n1; ++i)
  {
    int carry = 0;
    for (size_t j = 0; j < n2; ++j)
    {
      long long v = tmp[i+j]
        + static_cast<long long>(digits[i]) * rhs.digits[j]
        + carry;
      tmp[i+j] = static_cast<int>(v % BASE);
      carry = static_cast<int>(v / BASE);
    }
    size_t pos = i + n2;
    while (carry)
    {
      long long v = tmp[pos] + carry;
      tmp[pos] = static_cast<int>(v % BASE);
      carry = static_cast<int>(v / BASE);
      ++pos;
    }
  }

  std::vector<DigitType> fd;
  size_t m = tmp.size();
  while (m > 1 && tmp[m-1] == 0)
    --m;
  if (m > 0)
  {
    fd.reserve(m);
    for (size_t k = 0; k < m; ++k)
      fd.push_back(static_cast<DigitType>(tmp[k]));
  }

  return Integer(rs, std::move(fd));
}

// ---------------------------------------------------------
// Comparison operators ==, !=, <, >, <=, >=
// ---------------------------------------------------------
bool Integer::operator==(const Integer &rhs) const
{
  if (isZero() && rhs.isZero())
    return true;
  if (sign != rhs.sign)
    return false;
  return digits == rhs.digits;
}

bool Integer::operator!=(const Integer &rhs) const
{ return !(*this == rhs); }

bool Integer::operator<(const Integer &rhs) const
{
  if (sign && !rhs.sign) return true;
  if (!sign && rhs.sign) return false;
  if (isZero() && rhs.isZero()) return false;
  int cmp = compareMagnitude(*this, rhs);
  return sign ? (cmp > 0) : (cmp < 0);
}

bool Integer::operator>(const Integer &rhs) const
{ return rhs < *this; }

bool Integer::operator<=(const Integer &rhs) const
{ return !(*this > rhs); }

bool Integer::operator>=(const Integer &rhs) const
{ return !(*this < rhs); }

// ---------------------------------------------------------
// isZero, isNegative, signum, abs
// ---------------------------------------------------------
bool Integer::isZero() const  { return digits.empty(); }
bool Integer::isNegative() const { return sign && !isZero(); }

int Integer::signum() const
{ return isZero() ? 0 : (sign ? -1 : 1); }

Integer Integer::abs() const
{ return sign ? -(*this) : *this; }