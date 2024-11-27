#include "sinus.h"

template<typename T>
Array<double> Sinus<T>::generateDerivatives(int precision) {
    Array<double> derivatives;

    for (int i = 0; i < precision; i++) {
        if (i % 4 == 0) {
            derivatives.GetArray().push_back(0);  // f(0) = 0
        } else if (i % 4 == 1) {
            derivatives.GetArray().push_back(1);  // f'(0) = 1
        } else if (i % 4 == 2) {
            derivatives.GetArray().push_back(0);  // f''(0) = 0
        } else if (i % 4 == 3) {
            derivatives.GetArray().push_back(-1); // f'''(0) = -1
        }
    }

    return derivatives;
}

// Явная специализация для конкретных типов, если требуется
template class Sinus<double>;
template class Sinus<Complex>;
