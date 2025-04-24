#include <iostream>
#include "Integer.h"
#include "Rational.h"

using namespace std;

int main()
{
    std::cout << "--- Integer Tests ---" << std::endl;

    // Test Integer constructors and operations
    char d1[] = {45, 23, 1};
    char d2[] = {99, 66, 33, 0, 0};
    Integer i1(true, 3, d1);  // -12345 (digits reversed, sign true)
    Integer i2(false, 5, d2); // 33669900 (digits reversed, sign false)
    cout << "i1: " << i1 << ", i2: " << i2 << endl;

    Integer i3 = -i1; // Unary negation
    Integer i4 = i1 + i2; // Addition
    cout << "i3 (-i1): " << i3 << ", i4 (i1 + i2): " << i4 << endl;

    Integer i5 = i1 - i2; // Subtraction
    Integer i6 = i1 * i2; // Multiplication
    cout << "i5 (i1 - i2): " << i5 << ", i6 (i1 * i2): " << i6 << endl;

    std::cout << "\n--- Rational Tests ---" << std::endl;

    // Test Rational constructors and operations
    Rational r1(i1, i2); // Rational from Integer
    Rational r2(i4, i5); // Rational from Integer
    cout << "r1: " << r1 << ", r2: " << r2 << endl;

    Rational r3 = -r1; // Unary negation
    Rational r4 = r1 + r2; // Addition
    Rational r5 = r1 - r2; // Subtraction
    cout << "r3 (-r1): " << r3 << ", r4 (r1 + r2): " << r4 << ", r5 (r1 - r2): " << r5 << endl;

    Rational r6 = r1 * r2; // Multiplication
    Rational r7 = r1 / r2; // Division
    cout << "r6 (r1 * r2): " << r6 << ", r7 (r1 / r2): " << r7 << endl;

    std::cout << "\n--- Additional Tests for the Rational Class ---" << std::endl;

    // Test Rational additional scenarios
    Integer rn1(1LL), rd1(2LL);
    Integer rn2(3LL), rd2(4LL);
    Integer rn3(-1LL), rd3(3LL);
    Integer rn4(2LL), rd4(-5LL);

    Rational r_a(rn1, rd1);
    Rational r_b(rn2, rd2);
    Rational r_c(rn3, rd3);
    Rational r_d(rn4, rd4);
    Rational r_zero_num(Integer(0LL), rd1); // Zero numerator

    cout << "r_a: " << r_a << endl;
    cout << "r_b: " << r_b << endl;
    cout << "r_c: " << r_c << endl;
    cout << "r_d: " << r_d << endl;
    cout << "r_zero_num: " << r_zero_num << endl;

    // Test equality
    Integer n_two(2LL), d_four(4LL);
    Rational r_equiv(n_two, d_four); // Equivalent to 1/2
    cout << "r_a == 1/2: " << (r_a == Rational(1LL, 2LL)) << endl;
    cout << "r_a == 2/4: " << (r_a == r_equiv) << endl;

    // Test arithmetic
    cout << "-r_a: " << -r_a << endl;
    cout << "r_a + r_b: " << (r_a + r_b) << endl;
    cout << "r_a - r_b: " << (r_a - r_b) << endl;
    cout << "r_a * r_c: " << (r_a * r_c) << endl;
    cout << "r_a / r_b: " << (r_a / r_b) << endl;

    return 0;
}