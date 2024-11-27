#ifndef FUNCTION_H
#define FUNCTION_H

#include "Polynom.h"
#include "Polynom.cpp"
#include "Array.h"


template <typename T>
class Function : public Polynom<double>
{
public:

    Function(unsigned precision, Array<double> derivatives);

    long long factorial(int t_n);

    T evaluate(T x);
};

#endif // FUNCTION_H
