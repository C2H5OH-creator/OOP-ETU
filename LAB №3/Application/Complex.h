#pragma once

#include <cmath>
#include <iostream>
#include <string>

class Complex {
public:
    // Конструкторы
    Complex() : real(0), imaginary(0) {}
    Complex(double real, double imaginary) : real(real), imaginary(imaginary) {}

    // Геттеры
    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }

    // Сеттеры
    void setRealPart(double real) { real = real; }
    void setImaginaryPart(double imaginary) { imaginary = imaginary; }

    double Magnitude() const {
        return sqrt(real * real + imaginary * imaginary);
    }

    // Перегрузка оператора присваивания с добавлением (+=)
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imaginary += other.imaginary;
        return *this;
    }

    // Перегрузка оператора вычитания (-=)
    Complex& operator-=(const Complex& other) {
        real -= other.real;
        imaginary -= other.imaginary;
        return *this;
    }

    // Перегрузка оператора умножения (*=)
    Complex& operator*=(const Complex& other) {
        double newRealPart = real * other.real - imaginary * other.imaginary;
        double newImaginaryPart = real * other.imaginary + imaginary * other.real;
        real = newRealPart;
        imaginary = newImaginaryPart;
        return *this;
    }

    // Перегрузка оператора деления (/=)
    Complex& operator/=(const Complex& other) {
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        double newRealPart = (real * other.real + imaginary * other.imaginary) / denominator;
        double newImaginaryPart = (imaginary * other.real - real * other.imaginary) / denominator;
        real = newRealPart;
        imaginary = newImaginaryPart;
        return *this;
    }

    // Перегрузка оператора сложения (+)
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }

    // Перегрузка оператора вычитания (-)
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }

    // Перегрузка оператора умножения (*)
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imaginary * other.imaginary,
            real * other.imaginary + imaginary * other.real);
    }

    // Перегрузка оператора деления (/)
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        return Complex((real * other.real + imaginary * other.imaginary) / denominator,
            (imaginary * other.real - real * other.imaginary) / denominator);
    }

    Complex operator/(double value) const {
        if (value == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return Complex(real / value, imaginary / value);
    }

    // Перегрузка операторов сравнения (==)
    bool operator==(const Complex& other) const {
        return real == other.real && imaginary == other.imaginary;
    }

    // Перегрузка операторов неравенства (!=)
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    // Операторы сравнения
    friend bool operator>(const Complex& lhs, const Complex& rhs);
    friend bool operator<(const Complex& lhs, const Complex& rhs);

    // Перегрузка оператора вывода в поток (<<)
    friend std::ostream& operator<<(std::ostream& outputStream, const Complex& number) {
        if (number.imaginary >= 0)
            outputStream << number.real << " + " << number.imaginary << "i";
        else
            outputStream << number.real << " - " << -number.imaginary << "i";
        return outputStream;
    }

    // Перегрузка оператора ввода из потока (>>)
    friend std::istream& operator>>(std::istream& inputStream, Complex& number) {
        std::cout << "Введите действительную часть: ";
        inputStream >> number.real;
        std::cout << "Введите мнимую часть: ";
        inputStream >> number.imaginary;
        return inputStream;
    }

    std::string GetComplexString() const {
        if (imaginary >= 0)
            return std::to_string(real) + " + i" + std::to_string(imaginary);
        else
            return std::to_string(real) + " - i" + std::to_string(imaginary);
    }


private:
    double real;
    double imaginary;
};