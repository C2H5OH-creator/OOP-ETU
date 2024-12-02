#ifndef SINUS_H
#define SINUS_H

#include "function.h"
#include "Array.h"

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

#endif // SINUS_H
