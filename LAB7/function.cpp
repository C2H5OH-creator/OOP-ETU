#include "function.h"

template<typename T>
Function<T>::Function(unsigned precision, Array<double> derivatives) {
    for (int i = 0; i < precision; i++) {
        this->GetCoeffs()->GetArray().push_back(derivatives.GetArray()[i] / factorial(i));
    }

}

template<typename T>
long long Function<T>::factorial(int t_n) {
    if (t_n == 0 || t_n == 1) return 1;
    long long result = 1;
    for (int i = 2; i <= t_n; ++i) {
        result *= i;
    }
    return result;
}

template<typename T>
T Function<T>::evaluate(T x) {
    T result;
    if constexpr (std::is_same<T, Complex>::value) { result = Complex(0.0,0.0); }
    else { result = 0; }

    // Используем std::pow или Complex::power в зависимости от типа T
    for (int i = 0; i < this->GetCoeffs()->GetArray().size(); ++i) {
        if constexpr (std::is_same<T, Complex>::value) {
            // Если тип T — Complex, используем Complex::power
            result += this->GetCoeffs()->GetArray()[i] * x.power(i);  // Используем power из Complex
        } else {
            // Для других типов используем стандартное std::pow
            result += this->GetCoeffs()->GetArray()[i] * std::pow(x, i);
        }
    }
    return result;
}
