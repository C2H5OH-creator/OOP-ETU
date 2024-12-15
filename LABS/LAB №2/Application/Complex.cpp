#include "Complex.h"

// Конструкторы
Complex::Complex() : real(0), imaginary(0) {}

Complex::Complex(double real, double imaginary) : real(real), imaginary(imaginary) {}

// Геттеры
double Complex::getReal() const {
    return real;
}

double Complex::getImaginary() const {
    return imaginary;
}

// Сеттеры
void Complex::setRealPart(double real) {
    this->real = real;
}

void Complex::setImaginaryPart(double imaginary) {
    this->imaginary = imaginary;
}

// Методы
double Complex::Magnitude() const {
    return std::sqrt(real * real + imaginary * imaginary);
}

//Функция для получения числа в виде строки 
//(рудимент,нужна была для вывода до перегрузки оператора <<)
std::string Complex::GetComplexString() const {
    if (imaginary >= 0)
        return std::to_string(real) + " + i" + std::to_string(imaginary);
    else
        return std::to_string(real) + " - i" + std::to_string(-imaginary);
}

// Перегрузка операторов присваивания
Complex& Complex::operator+=(const Complex& other) {
    real += other.real;
    imaginary += other.imaginary;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) {
    real -= other.real;
    imaginary -= other.imaginary;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) {
    double newRealPart = real * other.real - imaginary * other.imaginary;
    double newImaginaryPart = real * other.imaginary + imaginary * other.real;
    real = newRealPart;
    imaginary = newImaginaryPart;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    double denominator = other.real * other.real + other.imaginary * other.imaginary;
    if (denominator == 0) {
        throw std::invalid_argument("Division by zero");
    }
    double newRealPart = (real * other.real + imaginary * other.imaginary) / denominator;
    double newImaginaryPart = (imaginary * other.real - real * other.imaginary) / denominator;
    real = newRealPart;
    imaginary = newImaginaryPart;
    return *this;
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imaginary + other.imaginary);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imaginary - other.imaginary);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(real * other.real - imaginary * other.imaginary,
        real * other.imaginary + imaginary * other.real);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real * other.real + other.imaginary * other.imaginary;
    if (denominator == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return Complex((real * other.real + imaginary * other.imaginary) / denominator,
        (imaginary * other.real - real * other.imaginary) / denominator);
}

Complex Complex::operator/(double value) const {
    if (value == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return Complex(real / value, imaginary / value);
}

// Перегрузка операторов сравнения
bool Complex::operator==(const Complex& other) const {
    return real == other.real && imaginary == other.imaginary;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

// Дружественные операторы сравнения
bool operator>(const Complex& lhs, const Complex& rhs) {
    return lhs.Magnitude() > rhs.Magnitude();
}

bool operator<(const Complex& lhs, const Complex& rhs) {
    return lhs.Magnitude() < rhs.Magnitude();
}

// Перегрузка оператора вывода в поток
std::ostream& operator<<(std::ostream& outputStream, const Complex& number) {
    if (number.imaginary >= 0)
        outputStream << number.real << " + " << number.imaginary << "i";
    else
        outputStream << number.real << " - " << -number.imaginary << "i";
    return outputStream;
}

// Перегрузка оператора ввода из потока
std::istream& operator>>(std::istream& inputStream, Complex& number) {
    std::cout << "Введите действительную часть: ";
    inputStream >> number.real;
    std::cout << "Введите мнимую часть: ";
    inputStream >> number.imaginary;
    return inputStream;
}