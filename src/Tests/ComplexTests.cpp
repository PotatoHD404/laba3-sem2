//
// Created by korna on 20.04.2021.
//

#include "gtest/gtest.h"
#include <iostream>
#include "../Complex.h"

using namespace std;

TEST(Complex, Multiply) {
    Complex num = Complex(2.0, 0.0);
    Complex num1 = Complex(-2.0, 0.0);
    EXPECT_FLOAT_EQ((num1 * num).real, -4.0);
    EXPECT_FLOAT_EQ((num1 * num).imaginary, 0.0);

    num = Complex(0.0, 2.0);
    num1 = Complex(0.0, 2.0);
    EXPECT_FLOAT_EQ((num1 * num).real, -4.0);
    EXPECT_FLOAT_EQ((num1 * num).imaginary, 0.0);

    num = Complex(4.0, 2.0);
    num1 = Complex(5.0, -3.0);
    EXPECT_FLOAT_EQ((num1 * num).real, 26);
    EXPECT_FLOAT_EQ((num1 * num).imaginary, -2);
    num1 = Complex(num);
    EXPECT_FLOAT_EQ(num.real, num1.real);
    EXPECT_FLOAT_EQ(num.imaginary, num1.imaginary);
    EXPECT_TRUE(num == num1);
}

TEST(Complex, Sum) {
    Complex num = Complex(4.0, 2.0);
    Complex num1 = Complex(5.0, -3.0);
    EXPECT_FLOAT_EQ((num1 + num).real, 9.0);
    EXPECT_FLOAT_EQ((num1 + num).imaginary, -1.0);
}

TEST(Complex, Compare) {
    Complex num = Complex(4.0, 2.0);
    EXPECT_TRUE(num > 0.0);
}