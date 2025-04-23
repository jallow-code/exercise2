/***************************************************************************
 * Integer.h
 * Header file for the Integer class, representing arbitrary-precision
 * signed integers with basic arithmetic and comparison operations.
 *
 * Author: Abdoulie Jallow <Jallow.jku@gmail.com>
 * Last Modification: 23/04/2025
 *
 **************************************************************************/

 #ifndef INTEGER_H
 #define INTEGER_H
 
 #include <iostream>
 #include <vector>
 #include <string>
 
 /***************************************************************************
  * The Integer class represents signed arbitrary-precision integers.
  * It supports basic arithmetic operations, comparison, and helper methods
  * for working with integer values.
  **************************************************************************/
 class Integer {
 private:
     // Indicates the sign of the integer: false for non-negative, true for negative.
     bool sign = false;
 
     // Stores the digits of the integer in base 100, least significant digit first.
     std::vector<unsigned char> digits = {};
 
     /*************************************************************************
      * normalize()
      * Removes leading zeros and ensures the sign is correct for zero.
      *
      * Input condition: None.
      * Output condition: Representation is minimal with no leading zeros.
      *************************************************************************/
     void normalize();
 
     /*************************************************************************
      * Static helper functions for unsigned arithmetic operations.
      *************************************************************************/
 
     // Adds the magnitudes of two integers.
     static Integer addMagnitude(const Integer& a, const Integer& b);
 
     // Subtracts the magnitude of b from a (requires |a| >= |b|).
     static Integer subtractMagnitude(const Integer& a, const Integer& b);
 
     // Compares the magnitudes of two integers.
     static int compareMagnitude(const Integer& a, const Integer& b);
 
 public:
     /*************************************************************************
      * Constructors.
      *************************************************************************/
 
     // Default constructor creates an integer with value 0.
     Integer() = default;
 
     // Constructs an integer from a built-in integer.
     Integer(long long i);
 
     // Constructs an integer from a sign and a C-style array of digits.
     Integer(bool s, int n, const char* d);
 
     // Constructs an integer from a sign and a vector of digits.
     Integer(bool s, std::vector<unsigned char> d_vec);
 
     /*************************************************************************
      * Output operator.
      *************************************************************************/
 
     // Outputs the integer to an output stream.
     friend std::ostream& operator<<(std::ostream& os, const Integer& i);
 
     /*************************************************************************
      * Arithmetic operators.
      *************************************************************************/
 
     // Unary minus operator.
     Integer operator-() const;
 
     // Binary addition operator.
     Integer operator+(const Integer& i) const;
 
     // Binary subtraction operator.
     Integer operator-(const Integer& i) const;
 
     // Binary multiplication operator.
     Integer operator*(const Integer& i) const;
 
     /*************************************************************************
      * Comparison operators.
      *************************************************************************/
 
     bool operator==(const Integer& i) const;
     bool operator!=(const Integer& i) const;
     bool operator<(const Integer& i) const;
     bool operator>(const Integer& i) const;
     bool operator<=(const Integer& i) const;
     bool operator>=(const Integer& i) const;
 
     /*************************************************************************
      * Helper methods.
      *************************************************************************/
 
     // Checks if the integer is zero.
     bool isZero() const;
 
     // Checks if the integer is negative.
     bool isNegative() const;
 
     // Returns the sign of the integer (-1 for negative, 0 for zero, 1 for positive).
     int signum() const;
 
     // Returns the absolute value of the integer.
     Integer abs() const;
 };
 
 #endif // INTEGER_H
 