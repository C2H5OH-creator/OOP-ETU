#ifndef SINUS_H
#define SINUS_H

#include "function.h"
//#include "function.cpp"
#include "Array.h"


template<typename T>
class Sinus : public Function<T>
{
public:
    Sinus(unsigned precision) : Function<T>(precision, generateDerivatives(precision)) {};
private:
    Array<double> generateDerivatives(int precision);

};

#endif // SINUS_H
