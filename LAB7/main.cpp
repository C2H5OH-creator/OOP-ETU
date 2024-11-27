
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

/*
#include <iostream>
#include <cmath>
#include <vector>
#include <memory>
#include <type_traits>

class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }

    Complex power(int n) const {
        Complex result(1, 0);
        Complex base = *this;
        while (n > 0) {
            if (n % 2 == 1) {
                result = result * base;
            }
            base = base * base;
            n /= 2;
        }
        return result;
    }

    Complex operator*(double value) const {
        return Complex(real * value, imag * value);
    }

    // Перегрузка оператора умножения для умножения вещественного числа на комплексное число
    friend Complex operator*(double value, const Complex& complex) {
        return Complex(complex.real * value, complex.imag * value);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real;
        if (c.imag >= 0) os << "+";
        os << c.imag << "i";
        return os;
    }
};

template<typename T>
class Array {
public:
    std::vector<T>& GetArray() { return array; }
private:
    std::vector<T> array;
};

template<typename T>
class Polynom {
public:
    Array<T>& GetCoeffs() { return coeffs; }
private:
    Array<T> coeffs;
};

template<typename T>
class Function : public Polynom<double> {
public:
    Function(unsigned precision, Array<double> derivatives) {
        for (int i = 0; i < precision; i++) {
            this->GetCoeffs().GetArray().push_back(derivatives.GetArray()[i] / factorial(i));
        }
    }

    ~Function() = default;

    long long factorial(int t_n) {
        if (t_n == 0 || t_n == 1) return 1;
        long long result = 1;
        for (int i = 2; i <= t_n; ++i) {
            result *= i;
        }
        return result;
    }

    T evaluate(T x) {
        T result;
        if constexpr (std::is_same<T, Complex>::value) { result = Complex(0,0); }
        else { result = 0; }

        for (int i = 0; i < this->GetCoeffs().GetArray().size(); ++i) {
            if constexpr (std::is_same<T, Complex>::value) {
                result = result + this->GetCoeffs().GetArray()[i] * x.power(i);
            } else {
                result = result + this->GetCoeffs().GetArray()[i] * std::pow(x, i);
            }
        }
        return result;
    }
};

template<typename T>
class Sinus : public Function<T> {
public:
    Sinus(unsigned precision) : Function<T>(precision, generateDerivatives(precision)) {}

    Array<double> generateDerivatives(int precision) {
        Array<double> derivatives;

        for (int i = 0; i < precision; i++) {
            if (i % 4 == 0) {
                derivatives.GetArray().push_back(0);
            } else if (i % 4 == 1) {
                derivatives.GetArray().push_back(1);
            } else if (i % 4 == 2) {
                derivatives.GetArray().push_back(0);
            } else if (i % 4 == 3) {
                derivatives.GetArray().push_back(-1);
            }
        }

        return derivatives;
    }
};

int main() {
    int precision = 10;
    Complex z(1, 0); // Пример комплексного числа (1 + i)

    auto complexSinus = std::make_unique<Sinus<Complex>>(precision);
    Complex result = complexSinus->evaluate(z);

    std::cout << "sin(" << z << ") = " << result << std::endl;

    return 0;
}
*/
