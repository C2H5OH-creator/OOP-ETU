#pragma once

#include <cmath>
#include <iostream>
#include <string>

class Complex {
public:
    Complex();
    Complex(double real, double imaginary);

    double getReal() const;
    double getImaginary() const;

    void setRealPart(double real);
    void setImaginaryPart(double imaginary);

    double Magnitude() const;
    std::string GetComplexString() const;

    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    Complex operator/(double value) const;

    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;

    friend bool operator>(const Complex& lhs, const Complex& rhs);
    friend bool operator<(const Complex& lhs, const Complex& rhs);
    friend std::ostream& operator<<(std::ostream& outputStream, const Complex& number);
    friend std::istream& operator>>(std::istream& inputStream, Complex& number);

private:
    double real;
    double imaginary;
};