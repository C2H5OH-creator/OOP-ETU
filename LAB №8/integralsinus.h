#ifndef INTEGRAL_SINUS_H
#define INTEGRAL_SINUS_H

#include "function.h"
#include "Array.h"

template<typename T>
class IntegralSinus : public Function<T> {
public:
    IntegralSinus(unsigned precision)
        : Function<T>(precision, generateIntegrals(precision)) {}

    Array<long double> generateIntegrals(int precision) {
        Array<long double> integrals;

        // Расчет коэффициентов для ряда интегрального синуса
        for (int i = 0; i < precision; ++i) {
            if (i % 2 == 0) {
                integrals.GetArray().push_back(0); // Члены ряда с четными степенями отсутствуют
            } else {
                long double coefficient = std::pow(-1, (i - 1) / 2) / i;
                integrals.GetArray().push_back(coefficient);
            }
        }

        return integrals;
    }
};

#endif // INTEGRAL_SINUS_H
