#ifndef TESTPOLYNOM_H
#define TESTPOLYNOM_H
#include "Array.h"
template<typename T>
class Polynom {
public:
    Array<T>& GetCoeffs() { return coeffs; }
private:
    Array<T> coeffs;
};
#endif // TESTPOLYNOM_H
