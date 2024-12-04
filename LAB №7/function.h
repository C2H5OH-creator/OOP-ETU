#ifndef FUNCTION_H
#define FUNCTION_H

#include "Polynom.h"
#include "Polynom.cpp"
//#include "TestPolynom.h"
#include "Array.h"
#include <QDebug>

template<typename T>
class Function : public Polynom<double> {
public:
    Function(unsigned precision, Array<long double> derivatives) : Polynom<double>(false) {
        std::cout << "precision: " << precision << std::endl;
        for (int i = 0; i < precision; i++) {
            this->GetCoeffs().GetArray().push_back(derivatives.GetArray()[i] / factorial(i));
            std::cout << "i: " << i << " "<<this->GetCoeffs().GetArray()[i] << std::endl;
        }
    }

    ~Function() = default;

    long double factorial(int t_n) {
        if (t_n == 0.0 || t_n == 1.0) return 1;
        long long result = 1.0;
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
            std::cout << "Array size "<<this->GetCoeffs().GetArray().size() << std::endl;
            if constexpr (std::is_same<T, Complex>::value) {
                result += this->GetCoeffs().GetArray()[i] * x.power(i);
            } else {
                result += this->GetCoeffs().GetArray()[i] * std::pow(x, i);
            }
        }
        return result;
    }
};

#endif // FUNCTION_H
