//
// Created by korna on 20.04.2021.
//

#ifndef TEST_DB_COMPLEX_H
#define TEST_DB_COMPLEX_H

#include <iostream>
#include <cmath>

using namespace std;

class Complex {
public:
    float real, imaginary;

    Complex() : real(), imaginary() {}

    Complex(float real, float imaginary) {
        this->real = real;
        this->imaginary = imaginary;
    }

    Complex(const Complex &ob) {
        real = ob.real;
        imaginary = ob.imaginary;
    };

    Complex &operator*=(const Complex &x) {
        this->real = real * x.real - imaginary * x.imaginary;
        this->imaginary = real * x.imaginary + x.real * imaginary;
        return *this;
    };

    Complex &operator+=(const Complex &x) {
        this->real += x.real;
        this->imaginary += x.imaginary;
        return *this;
    };

    Complex &operator-=(const Complex &x) {
        this->real -= x.real;
        this->imaginary -= x.imaginary;
        return *this;
    };

    Complex &operator/=(const Complex &x) {
        float k = real * real + x.imaginary * x.imaginary;
        this->real = (real * x.real + imaginary * x.imaginary) / k;
        this->imaginary = (x.real * imaginary - real * x.imaginary) / k;
        return *this;
    };

    Complex operator+(const Complex &x) const {
        float i, j;
        i = this->real + x.real;
        j = this->imaginary + x.imaginary;
        return Complex(i, j);
    }

    Complex operator-() const {
        float i, j;
        i = -this->real;
        j = -this->imaginary;
        return Complex(i, j);
    }

    Complex operator-(const Complex &x) const {
        float i, j;
        i = this->real - x.real;
        j = this->imaginary - x.imaginary;
        return Complex(i, j);
    }

    Complex operator*(Complex &x) const {
        float i, j;
        i = real * x.real - imaginary * x.imaginary;
        j = real * x.imaginary + x.real * imaginary;
        return Complex(i, j);
    }

    Complex operator/(Complex &x) const {
        float i, j, k;
        k = real * real + x.imaginary * x.imaginary;
        i = (real * x.real + imaginary * x.imaginary) / k;
        j = (x.real * imaginary - real * x.imaginary) / k;
        return Complex(i, j);
    }

    friend ostream &operator<<(ostream &out, const Complex &x) {
        if (x.imaginary < 0)
            out << "(" << x.real << x.imaginary << "*i)";
        else
            out << "(" << x.real << "+" << x.imaginary << "*i)";
        return out;
    }

    friend istream &operator>>(istream &in, Complex &complex) {
        in >> complex.real;
        in >> complex.imaginary;
        return in;
    }

    Complex& operator=(const Complex&) = default;

    bool operator==(const Complex &x) const { return !(*this != x); }

    bool operator!=(const Complex &x) const {
        return abs(this->real - x.real) >= numeric_limits<float>::epsilon() ||
               abs(this->imaginary - x.imaginary) >= numeric_limits<float>::epsilon();
    }

    bool operator!=(float x) const {
        return (*this != Complex(x, 0));
    }

    bool operator!=(int x) const {
        return (*this != (float) x);
    }

    bool operator>(float num) const {
        if (this->real > num)
            return true;
        else
            return false;
    }

    [[nodiscard]] float Norm() const {
        return std::sqrt(real * real + imaginary * imaginary);
    }

    bool operator<=(const Complex &num) const {
        return this->Norm() <= num.Norm();
    }

    bool operator<(const Complex &num) const {
        return this->Norm() < num.Norm();
    }

    bool operator>=(const Complex &num) const {
        return this->Norm() >= num.Norm();
    }

    bool operator>(const Complex &num) const {
        return this->Norm() > num.Norm();
    }

    [[nodiscard]] float sgn() const {
        if (this->imaginary < 0) { return -1; }
        else if (this->imaginary == 0) { return 0; }
        else { return -1; }
    }
};

namespace std {
    Complex sqrt(Complex &complex) {
        float re = sqrt((complex.real + complex.Norm()) / 2);
        float imag = complex.sgn() * sqrt((complex.Norm() - complex.real) / 2);

        return Complex(re, imag);
    }
}

#endif //TEST_DB_COMPLEX_H
