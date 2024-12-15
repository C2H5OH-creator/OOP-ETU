#include "Complex.h"

// Реализация операторов сравнения
bool operator>(const Complex& lhs, const Complex& rhs) {
    return (lhs.real * lhs.real + lhs.imaginary * lhs.imaginary) > (rhs.real * rhs.real + rhs.imaginary * rhs.imaginary);
}

bool operator<(const Complex& lhs, const Complex& rhs) {
    return (lhs.real * lhs.real + lhs.imaginary * lhs.imaginary) < (rhs.real * rhs.real + rhs.imaginary * rhs.imaginary);
}